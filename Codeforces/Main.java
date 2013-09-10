import java.util.*;

public class Main{
	public static void main( String [] args ){
		Solver problem = new Solver();
		problem.solve();
	}
}

class Solver{
	Scanner in = new Scanner( System.in );
	List< Integer > lucky = new ArrayList< Integer >(); 
	public Solver(){
		for( int i = 1 ; i < 1001 ; i++ )
			if( is_lucky( i ) ) lucky.add( i );
	}
	boolean is_lucky( int n ){
		String str = n + "";
		for( int i = 0 ; i < str.length() ; i++ ){
			if( str.charAt( i ) != '4' && str.charAt( i ) != '7' )
				return false;
		}
		return true;
	}
	boolean is_almost( int n ){
		for( Integer divisor : lucky ) 
			if( n % divisor == 0 ) 	return true;
		return false;
	}
	public void solve(){
		int test = in.nextInt();
		if( is_almost( test ) )
			System.out.println("YES");
		else
			System.out.println("NO");
	}
}

