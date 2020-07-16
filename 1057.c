#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Size 100000

int main( int argc, const char *argv[] ){

    char Data[Size+1];
    int sum = 0;
    int cnt0,cnt1;
    int Length;
    cnt0 = cnt1 = 0;

    gets( Data ); /* 字符串中有 ' ' （空格）字符， 用gets函数整体读入 */
    Length = strlen( Data );

    for( int i = 0 ; i < Length ; i++ ){
        if( Data[i] >= 'a' && Data[i] <= 'z' )
            sum += Data[i] - 'a' + 1;
        else if( Data[i] >= 'A' && Data[i] <= 'Z' )
            sum += Data[i] - 'A' + 1;       
    }

    while( sum != 0 ){ /* 位操作，最低位 ‘与1’  */
        if(  sum & 1  )
            cnt1++;
        else
            cnt0++;
        sum = sum >> 1; /* sum 左移一位 */
    }
    
    printf( "%d %d",cnt0, cnt1 );

    return 0;
}
