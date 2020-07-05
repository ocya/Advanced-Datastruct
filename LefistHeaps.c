#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* macro definition */
#define Insert( X, H ) ( H = Insert1( ( X ), H ) )
#define DeleteMin( H ) ( H = DeleteMin1( H ) )
 
typedef int ElementType;

typedef struct TreeNode *PriorityQueue;
struct TreeNode{
    ElementType Element;
    PriorityQueue Left;
    PriorityQueue Right;
    int Npl;/* null path length */
};

int main( int argc, const char *argv[]){

    return 0;
}

/* Ensure the H1 has smaller root */
PriorityQueue Merge( PriorityQueue H1, PriorityQueue H2){
    if( H1 == NULL ) 
        return H2;
    if( H2 == NULL )
        return H1;
    if( H1->Element < H2->Element )
        return Merge1( H1, H2 );
    else
        return Merge1( H2, H1 );
}

PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2 ){
    if( H1->Left == NULL )/* Single node */
        H1->Left = H2; /*  H1->Right is already NULL, H1->Npl is already 0 */
    else{
        H1->Right = Merge( H1->Right, H2 );
        if( H1->Left->Npl < H1->Right->Npl )
            SwapChildren( H1 );
        
        H1->Npl = H1->Right->Npl + 1;
    }

    return H1;
}

void SwapChildren( PriorityQueue H ){
    PriorityQueue Tmp = H->Left;
    H->Left = H->Right;
    H->Right = Tmp;
}

PriorityQueue Insert1( ElementType X , PriorityQueue H ){
    PriorityQueue NewNode = (PriorityQueue)malloc(sizeof(struct TreeNode));
    NewNode->Element = X;
    NewNode->Left = NewNode->Right = NULL;
    NewNode->Npl = 0;
    H = Merge( NewNode , H );
    return H;
}

PriorityQueue DeleteMin1( PriorityQueue H ){
    if( H == NULL )
        return H;
    PriorityQueue LeftHeap,RightHeap;
    LeftHeap = H->Left;
    RightHeap = H->Right;
    free( H );
    return Merge( LeftHeap, RightHeap );
    
}