public class FileSystem {
    private SuperBlock superblock;
    private Directory directory;
    private FileTable filetable;

    public FileSystem( int diskBlocks ) {
        // create superblock, and format disk with 64 inodes in default
        superblock = new SuperBlock( diskBlocks );
    
        // create directory, and register "/" in directory entry 0
        directory = new Directory( superblock.inodeBlocks );
    
        // file table is created, and store directory in the file table
        filetable = new FileTable( directory );
    
        // directory reconstruction
        FileTableEntry dirEnt = open( "/", "r" );
        int dirSize = fsize( dirEnt );
        if ( dirSize > 0 ) {
            byte[] dirData = new byte[dirSize];
            read( dirEnt, dirData );
            directory.bytes2directory( dirData );
        }
        close( dirEnt );
    }

    void sync( ) {
        // directory synchronizatioin
        FileTableEntry dirEnt = open( "/", "w" );
        byte[] dirData = directory.directory2bytes( );
        write( dirEnt, dirData );
        close( dirEnt );
    
        // superblock synchronization
        superblock.sync( );
    }

    boolean format( int files ) {
        // wait until all filetable entries are destructed
        while ( filetable.fempty( ) == false )
            ;
    
        // format superblock, initialize inodes, and create a free list
        superblock.format( files );
    
        // create directory, and register "/" in directory entry 0
        directory = new Directory( superblock.inodeBlocks );
    
        // file table is created, and store directory in the file table
        filetable = new FileTable( directory );
    
        return true;
    }

    FileTableEntry open( String filename, String mode ) {
        // filetable entry is allocated
        FileTableEntry entry;
        if(!filename.equals("/")){
            short buff = directory.namei(filename);
            if(buff == -1 && mode.equals("r")){
                return null;
            }
            if(buff < 0){
                directory.ialloc(filename);
            }
            entry = filetable.falloc(filename, mode);
            if(mode.equals("w")){
                deallocAllBlocks(entry);
            }
            else{
                if(mode.equals("a")){
                    entry.seekPtr = entry.inode.length;
                }
                else{
                    if(mode.equals('r')){
                        return entry;
                    }
                    if(mode.equals("w+")){
                        return entry;
                    }
                }
            }
        }
        return null;
    }

    boolean close( FileTableEntry ftEnt ) {
        // filetable entry is freed
        synchronized ( ftEnt ) {
            // need to decrement count; also: changing > 1 to > 0 below
            ftEnt.count--;
            if ( ftEnt.count > 0 ) // my children or parent are(is) using it
                return true;
        }
        return filetable.ffree( ftEnt );
    }
	
	

    int fsize( FileTableEntry ftEnt ) {
        Inode buff = ftEnt.inode;
        if(ftEnt == null || buff == null){
            return -1;
        }
        return buff.length;
    }


    int read( FileTableEntry ftEnt, byte[] buffer ) {
        if ( ftEnt.mode == "w" || ftEnt.mode == "a" )
            return -1;
    
        int offset   = 0;              // buffer offset
        int left     = buffer.length;  // the remaining data of this buffer
        int curr, sPtr, right, block;
        Inode in;

        synchronized ( ftEnt ) {
			// repeat reading until no more data  or reaching EOF
            byte[] data = new byte[Disk.blockSize];
            curr = 0;
            sPtr = ftEnt.seekPtr;
            offset = sPtr % Disk.blockSize;
 
            while(curr < left){
                block = in.findTargetBlock(offset, sPtr);
                right = Math.min((Disk.blockSize - offset), (left - curr));
                if(block == -1){
                    return -1;
                }
                if(block < 0 || block >= superblock.totalblocks){
                    break;
                }
                if(offset == 0){
                    data = new byte[Disk.blockSize];
                }
                SysLib.rawread(block, data);
                System.arraycopy(data, offset, buffer, curr, right);
                curr += right;
                sPtr += right;
            }
            seek(ftEnt, curr, SEEK_CUR);
        }
        return curr;
    }

    int write( FileTableEntry ftEnt, byte[] buffer ) {
        // at this point, ftEnt is only the one to modify the inode
        if ( ftEnt.mode == "r" )
            return -1;
    
        int offset   = 0;              // buffer offset
        int left     = buffer.length;  // the remaining data of this buffer
        int curr, sPtr, right, block;
        Inode in;
        byte[] data;
        short bl;
        synchronized ( ftEnt ) {    
            data = new byte[Disk.blockSize];
            curr = 0;
            sPtr = ftEnt.mode.equals("a") ? seek(ftEnt, 0, SEEK_END) : ftEnt.seekPtr;//ftEnt.seekPtr;
            in.flag = 1;
            offset = sPtr % Disk.blockSize;
 
            while(curr < left){
                offset = sPtr % Disk.blockSize;
                right = Math.min((Disk.blockSize - offset), (left - curr));
                bl = in.findTargetBlock(offset, sPtr);

                if(bl == -1){
                    short buff = (short) superblock.nextFreeBlock();
                    if(buff == -1){
                        in.flag = 0;
                        break;
                    }
                    if(in.setTargetBlock(sPtr, bl) == false){
                        if(in.setIndexBlock(block) == false){
                            in.flag = 0;
                            break;
                        }
                        if(in.setTargetBlock(sPtr, bl) == false){
                            in.flag = 0;
                            break;
                        }
                    }
                }
                if(bl >= superblock.totalBlocks){
                    in.flag = 0;
                    break;
                }
                if(offset == 0){
                    data = new byte[Disk.blockSize];
                }
                SysLib.rawread(bl, data);
                System.arraycopy(buffer, curr, data, offset, right);
                SysLib.rawwrite(bl, data);
                curr += right;
                sPtr += right;
            }
            if(sPtr > in.length){
                in.length = sPtr;
            }
            seek(ftEnt, curr, SEEK_CUR);
            if(in.flag == 0){
                in.flag = 1;
            }
            in.toDisk(ftEnt.iNumber);
        }
        return curr;
    }

    private boolean deallocAllBlocks( FileTableEntry ftEnt ) {
        Inode buff;
        byte[] data;
        int curr;
        buff.count = 0;
        buff.length = 0;
        buff.flag = -1;

        //FTE empty
        if(ftEnt == null){
            return false;
        }
        if((buff = ftEnt.inode) == null){
            return false;
        }
        //inode isn't empty
        if(buff.count > 1){
            return false;
        }

        for(int i = 0;i < buff.length;i++){
            curr = buff.findTargetBlock(i, i);
            if(curr == -1){
                continue;
            }
            if(superblock.returnBlock(curr)){
                if(buff.setTargetBlock(curr, (short) -1) == false){
                    return false;
                }
            }
        }
        //is valid
        if(buff.indirect != -1){
            superblock.returnBlock(buff.indirect);
        }
        for(int i = 0;i < buff.direct.length;i++){
            buff.direct[i] = -1;
        }
        buff.toDisk(ftEnt.iNumber);
        return true;
    }

	
	
	
    boolean delete( String filename ) {
        FileTableEntry ftEnt = open( filename, "w" );
        short iNumber = ftEnt.iNumber;
        return close( ftEnt ) && directory.ifree( iNumber );
    }

    private final int SEEK_SET = 0;
    private final int SEEK_CUR = 1;
    private final int SEEK_END = 2;

    int seek( FileTableEntry ftEnt, int offset, int whence ) {
        synchronized ( ftEnt ) {
            /*
            System.out.println( "seek: offset=" + offset +
                    " fsize=" + fsize( ftEnt ) +
                    " seekptr=" + ftEnt.seekPtr +
                    " whence=" + whence );
            */
            if(whence < 1){
                ftEnt.seekPtr = offset;
            }
            else{
                if(whence == 1){
                    ftEnt.seekPtr += offset;
                }
                else{
                    if(whence == 2){
                        ftEnt.seekPtr = (ftEnt.inode.length + offset);
                    }
                    else{
                        ftEnt.seekPtr = ftEnt.inode.length;
                    }
                    if(ftEnt.seekPtr > ftEnt.inode.length){
                        ftEnt.seekPtr = ftEnt.inode.length;
                    }
                    if(ftEnt.seekPtr < 0){
                        ftEnt.seekPtr = 0;
                    }
                }
            }
            return ftEnt.seekPtr;
            
			
		}

    }
}
