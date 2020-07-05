#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Insert( X, H ) ( H = Insert1( (X), H ) )
#define DeleteMin( H ) ( H = DeleteMin1( H ) )

typedef int ElementType;

typedef struct TreeNode *PriorityQueue;
struct TreeNode{
    ElementType Element;
    PriorityQueue Left,Right;
};

int main( int argc, const char *argv[]){

    return 0;
}

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

PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2){
    if( H2->Right == NULL )
        H1->Left = H2;
    else{
        H1 = SwapChildren( H1 );
        H1->Left = Merge( H1->Left , H2 );
    }
    return H1;
}

PriorityQueue SwapChildren( PriorityQueue H){
    PriorityQueue Tmp = H->Right;
    H->Right = H->Left;
    H->Left = Tmp;
}

PriorityQueue Insert1( ElementType X, PriorityQueue H ){
    PriorityQueue SingleNode = (PriorityQueue)malloc(sizeof(struct TreeNode));
    SingleNode->Left = SingleNode->Right = NULL;
    SingleNode->Element = X;
    return Merge( SingleNode, H );
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