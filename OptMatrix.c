/* r contains number of columns for each of the N  matrices */
/* r[0] is the number of rows in matrix 1 */
/* Minimum number of multiplications is left in M[1][N] */
/* M and LastChange are indexed starting at 1, instead of 0 */
void OptMatrix( const long r[], int N, TwoDimArray M, TwoDimArray LastChange){
    int i,j,K,L; 
    long ThisM;

    for( i = 1 ; i <= N ; i++ ) M[i][j] = 0;
    for( K = 1 ; K < N ; K++) /* K = j - i  */
        for( i = 1 ; i <= N - K ; i++ ){
            j = i + K ; M[i][j] = Infinity;
            for( L = i ; L < j ; L++ ){
                ThisM = M[i][L] + M[L+1]M[j] + r[i-1] * r[L] * r[j];
                if( ThisM < M[i][j] ){
                    ThisM = M[i][j];
                    LastChange = L ;
                }
                    
            }
        }
}




