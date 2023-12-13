import java.util.*;

public class Cache {
    private int blockSize;
    private Vector<byte[]> pages; // you may use: private byte[][] = null;
    private int victim;

    private class Entry {
		public static final int INVALID = -1;
		public boolean reference;
		public boolean dirty;
		public int frame;

		public Entry( ) {
	    	reference = false;
	    	dirty = false;
	    	frame = INVALID;
		}
    }
    private Entry[] pageTable = null;

    private int nextVictim( ) {
		// implement by yourself
		int curr = victim;
		boolean dirtyCheck = false;
		boolean refCheck = false;

		while(true){
			curr++;
			if(curr >= pageTable.length){
				curr = 0;
			}
			//if !curr reference and !curr dirty or dirtyCheck
			if(!pageTable[curr].reference && (!pageTable[curr].dirty || dirtyCheck)){
				return curr;
			}
			//full cycle
			if(curr == victim){
				//if cycle is completed then need to allow overwriting and start removing
				if(dirtyCheck){ 
					refCheck = true;
				}
				dirtyCheck = !dirtyCheck;
			}
			if(refCheck){
				pageTable[curr].reference = false;
			}
		}
    }

	private int findInvalid(){
		for(int i = 0;i < pageTable.length;i++){
			if(pageTable[i].frame == -1){
				//invalid found. return position
				return i;
			}
		}
		//invalid not found. return -1
		return -1;
	}

    private void writeBack( int victimEntry ) {
        if ( pageTable[victimEntry].frame != Entry.INVALID && pageTable[victimEntry].dirty == true ) {
			SysLib.rawwrite(pageTable[victimEntry].frame, pages.elementAt(victimEntry));
	    	pageTable[victimEntry].dirty = false;
		}
    }

    public Cache( int blockSize, int cacheBlocks ) {
		// instantiate pages
		// instantiate and initialize pageTable
		this.blockSize = blockSize;
		victim = 0;
		pages = new Vector<byte[]>();
		pageTable = new Entry[cacheBlocks];
		for(int i = 0;i < cacheBlocks;i++){
			byte[] block = new byte[blockSize];
			pages.add(block);
			pageTable[i] = new Entry();
		}
    }

    public synchronized boolean read( int blockId, byte buffer[] ) {
		if ( blockId < 0 ) {
	    	SysLib.cerr( "threadOS: a wrong blockId for cread\n" );
	    	return false;
		}

		// locate a valid page
		for ( int i = 0; i < pageTable.length; i++ ) {
	    	if ( pageTable[i].frame == blockId ) {
			// cache hit!!
			// copy pages[i] to buffer
			byte[] block = pages.elementAt(i);
			System.arraycopy(block, 0, buffer, 0, blockSize);
			pageTable[i].reference = true;
			return true;
	    	}
		}
        // find an invalid page. if no invalid page is found, all pages are full. seek for a victim
		int victimEntry = findInvalid();
		//no Invalid page is found
		if(victimEntry == -1){
			victimEntry = nextVictim();
		}

		if(pageTable[victimEntry].dirty){
			//write back dirty copy
			writeBack(victimEntry);
		}
		// read a requested block from disk
		SysLib.rawread(blockId, buffer);
		// cache it. copy pages[victimEntry] to buffer
		byte[] block = new byte[blockSize];
		System.arraycopy(buffer, 0, block, 0, blockSize);
		pages.set(victimEntry, block);
		pageTable[victimEntry].frame = blockId;
        pageTable[victimEntry].reference = true;
		return true;
    }

    public synchronized boolean write( int blockId, byte buffer[] ) {
		if ( blockId < 0 ) {
	    	SysLib.cerr( "threadOS: a wrong blockId for cwrite\n" );
	    	return false;
		}

		// locate a valid page
		for ( int i = 0; i < pageTable.length; i++ ) {
	    	if ( pageTable[i].frame == blockId ) {
				// cache hit. copy buffer to pages[i]
				byte[] block = new byte[blockSize];
				System.arraycopy(buffer, 0, block, 0, blockSize);
				pages.set(i, block);
				pageTable[i].reference = true;
            	pageTable[i].dirty = true;
				return true;
	    	}
		}

		int victimEntry = findInvalid();
		//if no invalid page
		if(victimEntry == -1){
			victimEntry = nextVictim();
		}
		//if valid page
		if(pageTable[victimEntry].dirty){
			//write back a dirty copy
			writeBack(victimEntry);
		}
		// cache it but not write through. copy buffer to pages[victimEntry]
		SysLib.rawwrite(blockId, buffer);
		byte[] block = new byte[blockSize];
		System.arraycopy(buffer, 0, block, 0, blockSize);
		pages.set(victimEntry, block);
		
		pageTable[victimEntry].frame = blockId;
        pageTable[victimEntry].reference = true;
        pageTable[victimEntry].dirty = true;
		return true;
    }

    public synchronized void sync( ) {
		for ( int i = 0; i < pageTable.length; i++ )
	    	writeBack( i );
		SysLib.sync( );
    }

    public synchronized void flush( ) {
		for ( int i = 0; i < pageTable.length; i++ ) {
	    	writeBack( i );
	    	pageTable[i].reference = false;
	    	pageTable[i].frame = Entry.INVALID;
		}
		SysLib.sync( );
    }
}
