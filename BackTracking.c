#include <stdlib.h>
#include <stdbool.h>

/* The Turnpike Reconstruction Problem  */


bool Reconstruct( DistType X[], DistSet D, int N, int left,int right ){
    /* Assume that: X[1]...X[left-1] and X[right+1]...X[N] are solved */
    bool Found  = false;
    if( IsEmpty( D ) )
        return true; /* solved */
    DMax = FindMax( D );
    /* option 1: X[right] = DMax */
    /* Check if | DMax - X[i] | exist in D is true for all X[i]'s that have been solved  */
    OK = Check( DMax, N, left, right ); /* pruning */
    if( OK ){ /* add X[right] and update D */
        X[right] = DMax;
        for( i = 1 ; i < left ; i++) Delete( | X[right] - X[i] |, D ); 
        for( i = right + 1 ; i <= N ; i++) Delete( | X[right] - X[i] | , D );
        Found = Reconstruct( X, D, N, left, right-1 );
        if( !Found ){ /* if does not work, undo */
            for( i = 1 ; i < left ; i++ ) Insert( | X[right] - X[i|, D );
            for( i = right + 1 ; i <= N ; i++ ) Insert( | X[right] - X[i] |, D );
        }
    }
    /* finish checking option1 */
    
    if( !Found ){/* if option 1 does not work */
        /* option 2: X[left] = X[N] - DMax */
        OK = Check( X[N] - DMax, N, left, right );
        if( ok ){
            X[left] = X[N] - DMax;
            for( i = 1 ; i < left ; i++) Delete( | X[left] - X[i] |, D ); 
            for( i = right + 1 ; i <= N ; i++) Delete( | X[left] - X[i] | , D );
            Found = Reconstruct( X, D, N, left+1, right );
            if( !Found ){ /* if does not work, undo */
                for( i = 1 ; i < left ; i++ ) Insert( | X[left] - X[i|, D );
                for( i = right + 1 ; i <= N ; i++ ) Insert( | X[left] - X[i] |, D );
            }            
        }

    }

    return Found;
}

/* A Template */
bool Backtracking( int i ){
    bool Found = false;
    if( i > N )
        return true; /* solved with ( X1,...,Xn )*/
    for( each Xi 属于 Si ){
        /* Check if satisfies the restriction R */
        OK = Check( ( X1,..,Xi) , R ); /* pruning */
        if( OK ){
            Count Xi in;
            Found = Backtracking( i + 1 );
            if( !Found )
                Undo( i ); /* Recover to ( X1,...,Xi-1 ) */
        }

        if( Found ) break;
    }

    return Found;
}