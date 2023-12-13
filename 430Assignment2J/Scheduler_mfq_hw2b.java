import java.util.*; // Scheduler_mfq.java

public class Scheduler extends Thread
{   @SuppressWarnings({"unchecked","rawtypes"})
    //private Vector<TCB>[] queue = new Vector[3];
    private Vector queue0;
	private Vector queue1;
	private Vector queue2;
	private int timeSlice;
    private static final int DEFAULT_TIME_SLICE = 1000;

    // New data added to the original algorithm 
    private boolean[] tids; // Indicate which ids have been used
    private static final int DEFAULT_MAX_THREADS = 10000;

    // A new feature added to the original algorithm 
    // Allocate an ID array, each element indicating if that id has been used
    private int nextId = 0;

    private void initTid( int maxThreads ) {
	tids = new boolean[maxThreads];
	for ( int i = 0; i < maxThreads; i++ )
	    tids[i] = false;
    }

    // A new feature added to the original algorithm 
    // Search an available thread ID and provide a new thread with this ID
    private int getNewTid( ) {
	for ( int i = 0; i < tids.length; i++ ) {
	    int tentative = ( nextId + i ) % tids.length;
	    if ( tids[tentative] == false ) {
		tids[tentative] = true;
		nextId = ( tentative + 1 ) % tids.length;
		return tentative;
	    }
	}
	return -1;
    }

    // A new feature added to the original algorithm 
    // Return the thread ID and set the corresponding tids element to be unused
    private boolean returnTid( int tid ) {
	if ( tid >= 0 && tid < tids.length && tids[tid] == true ) {
	    tids[tid] = false;
	    return true;
	}
	return false;
    }

    // A new feature added to the original algorithm 
    // Retrieve the current thread's TCB from the queue
    public TCB getMyTcb( ) {
	Thread myThread = Thread.currentThread( ); // Get my thread object
	//Queue Zero
	synchronized( queue0 ) {
		for ( int i = 0; i < queue0.size( ); i++ ) {
		    TCB tcb=(TCB) queue0.elementAt( i );
		    Thread thread = tcb.getThread( );
		    if ( thread == myThread ) // if this is my TCB, return it
			return tcb;
			}
	}
	//Queue One
	synchronized( queue1 ) {
		for ( int i = 0; i < queue1.size( ); i++ ) {
		    TCB tcb=(TCB) queue1.elementAt( i );
		    Thread thread = tcb.getThread( );
		    if ( thread == myThread ) // if this is my TCB, return it
			return tcb;
			}
	}
	//Queue Two
	synchronized( queue2 ) {
		for ( int i = 0; i < queue2.size( ); i++ ) {
		    TCB tcb=(TCB) queue2.elementAt( i );
		    Thread thread = tcb.getThread( );
		    if ( thread == myThread ) // if this is my TCB, return it
			return tcb;
			}
	}
	return null;
    }

    // A new feature added to the original algorithm 
    // Return the maximal number of threads to be spawned in the system
    public int getMaxThreads( ) {
	return tids.length;
    }

    public Scheduler( ) {
	timeSlice = DEFAULT_TIME_SLICE;
	initTid( DEFAULT_MAX_THREADS );
	queue0 = new Vector();
	queue1 = new Vector();
	queue2 = new Vector();
    }

    public Scheduler( int quantum ) {
	timeSlice = quantum;
	initTid( DEFAULT_MAX_THREADS );
	queue0 = new Vector();
	queue1 = new Vector();
	queue2 = new Vector();
    }

    // A new feature added to the original algorithm 
    // A constructor to receive the max number of threads to be spawned
    public Scheduler( int quantum, int maxThreads ) {
	timeSlice = quantum;
	initTid( maxThreads );
	queue0 = new Vector();
	queue1 = new Vector();
	queue2 = new Vector();
    }

    private void schedulerSleep( ) {
	try {
	    //If statements to check which queue should be slept
		if(queue0.isEmpty() == false){
			Thread.sleep(timeSlice / 2);
		}
		else{
			if(queue1.isEmpty() == false){
				Thread.sleep(timeSlice);
			}
			else{
					Thread.sleep(timeSlice * 2);
			}
		}
	} catch ( InterruptedException e ) {
	}
    }

    // A modified addThread of the original algorithm
    public TCB addThread( Thread t ) {
	TCB parentTcb = getMyTcb( ); // get my TCB and find my TID
	int pid = ( parentTcb != null ) ? parentTcb.getTid( ) : -1;
	int tid = getNewTid( ); // get a new TID
	if ( tid == -1)
	    return null;
	TCB tcb = new TCB( t, tid, pid ); // create a new TCB
	queue0.add( tcb );
	return tcb;
    }

    // A new feature added to the original algorithm
    // Removing the TCB of a terminating thread
    public boolean deleteThread( ) {
	TCB tcb = getMyTcb( ); 
	if ( tcb!= null ) {
	    this.interrupt( );
	    return tcb.setTerminated( );
	} else
	    return false;
    }

    public void sleepThread( int milliseconds ) {
	try {
	    sleep( milliseconds );
	} catch ( InterruptedException e ) { }
    }
    

    // A modified run of the original algorithm
	public void run( ){
    Thread current = null;
    while ( true ){
        try {
			//if everything empty then continue
            if (queue0.isEmpty() && queue1.isEmpty() && queue2.isEmpty()){
                    continue;
			}

			//if just queue 0 is empty
            if(queue0.isEmpty() == false){
                //next thread
                TCB currentTCB = (TCB) queue0.firstElement( );
                if ( currentTCB.getTerminated( ) == true ){
                        queue0.remove( currentTCB );
                        returnTid( currentTCB.getTid( ) );
                        continue;
                }
                current = currentTCB.getThread( );
                if ( current != null ){
                        if ( current.isAlive( ) ){
                                current.resume();
						}
                        else{
                                current.start( );
                        }
                }
                schedulerSleep( );
				//send to end
                synchronized ( queue0 ) {
                        if ( current != null && current.isAlive( ) ){
                                current.suspend();
						}
                        queue0.remove( currentTCB );
                        queue1.add( currentTCB );
                }
            }

            else{ 
				if (queue1.isEmpty() == false){
                	//next thread
                	TCB currentTCB = (TCB) queue1.firstElement( );
                	if ( currentTCB.getTerminated( ) == true ) {
                        	queue1.remove( currentTCB );
                        	returnTid( currentTCB.getTid( ) );
                        	continue;
                	}
                	current = currentTCB.getThread( );
                	if ( current != null ){
                        	if ( current.isAlive( ) ){
                                	current.resume();
							}
                        	else{
                                	current.start( );
                        	}
                	}
                	schedulerSleep( );

					//send to end
                	synchronized ( queue1 ) {
                        	if ( current != null && current.isAlive( ) )
                                	current.suspend();
                        	queue1.remove( currentTCB );
                        	queue2.add( currentTCB );
                	}
            	}

            	else{
                	//Go onto next thread
                	TCB currentTCB = (TCB) queue2.firstElement( );
                	if ( currentTCB.getTerminated( ) == true ){
                        	queue2.remove( currentTCB );
                        	returnTid( currentTCB.getTid( ) );
                        	continue;
                	}
                	current = currentTCB.getThread( );
                	if ( current != null ){
                        	if ( current.isAlive( ) ){
                                	current.resume();
							}
                        	else {
                            	    current.start( );
                        	}
                	}
                	schedulerSleep( );

                	synchronized ( queue2 ) {
                    	    if ( current != null && current.isAlive( ) ){
                        	        current.suspend();
							}
                        	queue2.remove( currentTCB );
                        	queue2.add( currentTCB );
                	}
            	}
        	}
		}
        catch ( NullPointerException e3 ){};
    }
	}
}
