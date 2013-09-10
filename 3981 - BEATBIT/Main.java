import java.util.*;

public class Main{
	static int MAXN = 10001;
	Scanner In = new Scanner( System.in );
	Solver problem = new Solver();
	static public void main ( String [] args ){
		Main prob = new Main();
		prob.solve();
	}

	public void solve(){
		int test = In.nextInt();
		while( ( test -- ) != 0 ){
			int set = In.nextInt();
			for( int i = 0 ; i < set ; i++ ){
				problem.read();
				System.out.println( problem.solve() );
			}
			if( test != 0 )	System.out.println();
		}
	}
	class Node{
		public Integer [] nextBit = new Integer[ 2 ];
		public Integer idNode;
		public boolean isEnd;
		public int retVal;
		public Node( int tipo , Integer  id ){ 
			idNode = id;
			retVal = tipo;
			isEnd = tipo != -1;
		}	
		public void print(){
			System.out.println("---------");
			System.out.println( nextBit[ 0 ] + " " + nextBit[ 1 ] );
			System.out.println( idNode );
			System.out.println( isEnd + " " + retVal );
			System.out.println("---------");
		}
				
	}

	class Assemble{
		public HashMap< Integer , Integer > next = new HashMap< Integer , Integer >();
		public HashMap< Integer , Integer > compress = new HashMap< Integer , Integer >();
		public ArrayList< Integer > ids = new ArrayList< Integer >();
		public Node [] dag = new Node[ MAXN ];
		public ArrayList< Node > nodes = new ArrayList < Node >();
		public Integer firstInst;
		public Assemble(){}

		public void clear(){
			next.clear();
			nodes.clear();
			ids.clear();
			firstInst = null;
		}
		
		public void read(){
			int needUpdate = 0;
			int prevEdge = 0;
			clear();
			while( In.hasNext() ){
				String lbl = In.next() , to = "-1" ;
				if( lbl.charAt( 0 ) == 'E' ) break;
				String op = In.next();
				if( op.charAt( 0 ) != 'R' ) to = In.next();
				Integer fromId = Integer.parseInt( lbl ), toId = Integer.parseInt( to ) ; 
				if( firstInst == null ) firstInst = fromId;
				//System.out.println( fromId + " " + op + " " + toId );
				if( prevEdge == 1 ){
					Node holder = nodes.get( nodes.size() - 1 );
					holder.nextBit[ 0 ] = fromId;
				}

				ids.add( fromId );
				switch( op.charAt( 0 ) ){
					case 'J' :
						next.put( fromId , toId );
						prevEdge = 0;
						break;
					case 'R' :
						next.put( fromId , fromId );
						nodes.add( new Node( op.charAt( 3 ) - '0' , fromId )  );
						prevEdge = 1;
						break;
					case 'B' :
						next.put( fromId , fromId );
						Node holder = new Node( -1 , fromId );
						holder.nextBit[ 1 ] = toId; 
						holder.nextBit[ 0 ] = fromId;
						nodes.add( holder );
						prevEdge = 1;
						break;
				}
			}
			nodeCompression();
		}

		Integer find( Integer id ){
			if( next.get( id ).compareTo( id ) == 0 ) return id;
			next.put( id , find( next.get( id ) ) );
			return next.get( id );
		}

		public void nodeCompression(){
			compress.clear();
			for( int i = ids.size() - 1 ; i >= 0 ; i--  ){
				find( ids.get( i ) );	
				//System.out.println( ids.get( i ) + " " + next.get( ids.get( i ) ) );
			}
			for( int i = 0 ; i < nodes.size() ; i++ ){
				Node holder = nodes.get( i );
				compress.put( holder.idNode , Integer.valueOf( i ) );
				if( holder.isEnd ) continue;
				//System.out.println( holder.idNode + " " + holder.nextBit[ 0 ] + " " + holder.nextBit[ 1 ] );
				holder.nextBit[ 0 ] = next.get( holder.nextBit[ 0 ] );
				holder.nextBit[ 1 ] = next.get( holder.nextBit[ 1 ] );
			}
			for( int i = 0 ; i < nodes.size() ; i++ ){
				Node holder = nodes.get( i );
				dag[ i ] = holder;
				holder.idNode = compress.get( holder.idNode );
				if( !holder.isEnd )	
				for( int j = 0 ; j < 2 ; j++ )
					holder.nextBit[ j ] = compress.get( holder.nextBit[ j ] );
				//holder.print();
			}
			firstInst = nodes.get( 0 ).idNode;
		}
		public boolean checkEnd( Integer idNode , int value ){
			Node node = dag[ idNode ];
			if( node.retVal > -1 )	return value == node.retVal;
			boolean zero = checkEnd( node.nextBit[ 0 ] , value );
			boolean one = checkEnd( node.nextBit[ 1 ] , value );
			int retZero = dag[ node.nextBit[ 0 ] ].retVal;
			int retOne = dag[ node.nextBit[ 1 ] ].retVal;
			if( retZero == retOne ) 
				node.retVal = retZero;
			else					
				node.retVal = -2;
			return zero && one;
		}
	}

	class Solver{
		Assemble tInst = new Assemble() , dInst = new Assemble();
		int stackLen;
		public void read(){
			stackLen = In.nextInt();
			tInst.read();
			dInst.read();
		}
		
		int sameAns( Integer idA , Integer idB ){
			//System.out.println( idA + " " + idB );
			Node a = tInst.dag[ idA ] , b = dInst.dag[ idB ];
			if( a.retVal > -1 && b.retVal > -1  )	return a.retVal == b.retVal ? 1 : 0;
			if( a.retVal > -1 ) return dInst.checkEnd( idB , a.retVal ) ? 1 : 0 ;
			if( b.retVal > -1 ) return tInst.checkEnd( idA , b.retVal ) ? 1 : 0 ;
			
			for( int i = 0 ; i < 2 ; i++ )
				if( sameAns( a.nextBit[ i ] , b.nextBit[ i ] ) == 0 ) return 0;
			return 1;
		}

		public int solve(){
			return sameAns( tInst.firstInst , dInst.firstInst );
		}
	}
}
