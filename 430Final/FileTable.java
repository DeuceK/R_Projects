
public class FileTable {
// File Structure Table

    private Vector<FileTableEntry> table;// the entity of File Structure Table
    private Directory dir;         // the root directory
    
    public FileTable ( Directory directory ) {// a default constructor
	table = new Vector<FileTableEntry>( );// instantiate a file table
	dir = directory;                      // instantiate the root directory
    }

	// you implement
	public synchronized FileTableEntry falloc( String fname, String mode ) {
		short num = -1;
		Inode buff = null;
		
		while(true){
			num = fname.equals("/") ? 0 : dir.namei(fname);
			if(num >= 0){
				buff = new Inode(num);
				//mode r
				if(mode.compareTo("r") == 0){
					if(buff.flag > 0){
						try{
							wait();
						}
						catch(InterruptedException e){}
					}
					break;
				}
				else{
					//mode w
					if(mode.compareTo("w") == 0){
						if(buff.flag > 0){
							try{
								wait();
							}
							catch(InterruptedException e){}
						}
						buff.flag = 1;
						break;
					}
					else{
						//mode a
						if(mode.compareTo("a") == 0){
							if(buff.flag > 0){
								try{
									wait();
								}
								catch(InterruptedException e){}
							}
							buff.flag = 1;
							break;
						}
						else{
							//mode w+
							if(mode.compareTo("w+") == 0){
								if(buff.flag > 0){
									try{
										wait();
									}
									catch(InterruptedException e){}
								}
								buff.flag = 1;
								break;
							}
							else{
								throw new IllegalArgumentException();
							}
						}
					}
				}
			}
		}
		buff.count++;
		buff.toDisk(num);
		FileTableEntry e = new FileTableEntry(buff, num, mode);
		if(mode.equals("a")){
			e.seekPtr = buff.length;
		}
		table.addElement(e);
		return e;
	}

    public synchronized boolean ffree( FileTableEntry e ) {
	// receive a file table entry
	// free the file table entry corresponding to this index
	if ( table.removeElement( e ) == true ) { // find this file table entry
	    e.inode.count--;       // this entry no longer points to this inode
	    switch( e.inode.flag ) {
	    case 1: e.inode.flag = 0; break;
	    case 2: e.inode.flag = 0; break;
	    case 4: e.inode.flag = 3; break;
	    case 5: e.inode.flag = 3; break;
	    }
	    e.inode.toDisk( e.iNumber );     // reflect this inode to disk
	    e = null;                        // this file table entry is erased.
	    notify( );
	    return true;
	} else
	    return false;
    }

    public synchronized boolean fempty( ) {
	return table.isEmpty( );             // return if table is empty
    }                                        // called before a format
}
}
