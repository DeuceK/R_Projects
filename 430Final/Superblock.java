
public class Superblock {
    private final int defaultInodeBlocks = 64;
    public int totalBlocks;
    public int inodeBlocks;
    public int freeList;
	
	// you implement
	public SuperBlock( int diskSize ) {
		// read the superblock from disk
		byte[] superBlock = new byte[Disk.blockSize];
		SysLib.rawread(0, superBlock);
		this.totalBlocks = SysLib.bytes2int(superBlock, 0);
		this.inodeBlocks = SysLib.bytes2int(superBlock, 4);
		this.freeList = SysLib.bytes2int(superBlock, 8);

		//if information all checks out
		if(this.totalBlocks == diskSize && this.inodeBlocks > 0 && this.freeList > 3){
			return 0;
		}
		//doesn't check out
		else{
			totalBlocks = diskSize;
			format(defaultInodeBlocks);
		}
	}
	
	//  helper function
	void sync( ) {
		byte[] superBlock = new byte[Disk.blockSize];
		SysLib.int2bytes( totalBlocks, superBlock, 0 );
		SysLib.int2bytes( inodeBlocks, superBlock, 4 );
		SysLib.int2bytes( freeList, superBlock, 8 );
		SysLib.rawwrite( 0, superBlock );
		SysLib.cerr( "Superblock synchronized\n" );
    }

    void format( ) {
		// default format with 64 inodes
		format( defaultInodeBlocks );
    }
	
	// you implement
	 void format( int files ) {
		// initialize the superblock
		if (files > (diskSize - 1 - files % 16)){
		}
		else{
			freeList = 1;
			int buff = 0;
			byte[] buffer = new byte[Disk.blockSize];
			SysLib.rawread(0, buffer);
			inodeBlocks = files;
			totalBlocks = SysLib.bytes2int(buffer, 0);

			for(short i = 1;i < totalBlocks;i++){
				if(i == (totalBlocks - 1)){
					SysLib.short2bytes((short)-1, buffer, 0);
				}
				else{
					SysLib.short2bytes((short)(i + 1), buffer, 0);
				}
				SysLib.rawwrite(i, buffer);
			}
			
			for(short i = 0;i < files;i++){
				buff = new Inode().toDisk(i);
			}
			freeList += (buff * files) / Disk.blockSize + ((buff * files) % Disk.blockSize > 0 ? 1 : 0);
			sync();
		}

	 }
	
	// you implement
	public int getFreeBlock( ) {
		// get a new free block from the freelist
		short nextFreeBlock;
		byte[] block;

		//if freeList empty or no more empty spots return -1
		if(freeList < 0 || freeList > totalBlocks){
			return -1;
		}
		//create new empty block and grab free block from freeList
		nextFreeBlock = (short) freeList;
		block = new byte[Disk.blockSize];
		SysLib.rawread(freeList, block);
		SysLib.int2bytes(0, block, 0);
		SysLib.rawwrite(freeList, block);
		freeList = SysLib.bytes2int(block, 0);
		return nextFreeBlock;
	}
	
	// you implement
	public boolean returnBlock( int oldBlockNumber ) {
		// return this former block
		//if OBN is empty or less than out total block count
		if(oldBlockNumber < 0 || oldBlockNumber > totalBlocks){
			return false;
		}
		byte[] curr = new byte[Disk.blockSize];
		SysLib.short2bytes((short)freeList, curr, 0);
		SysLib.rawwrite(block, curr);
		freeList = block;
		return true;
	}
	
}
