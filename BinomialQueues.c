#include <stdlib.h>
#include <stdbool.h>

#define MaxTrees 30 /* 比特位数 */
#define Capacity ( ( 1<<MaxTrees ) - 1 ) /* 队列所能容纳的元素的数量 */
#define Infinity 65535

typedef int ElementType;

typedef struct BinNode *Position;
typedef struct Collection *BinQueue;
typedef struct BinNode *BinTree;

struct BinNode{
    ElementType Element;
    Position LeftChild;
    Position NextSibling;
};

struct Collection{
    int CurrentSize; /* 集合中当前总的元素个数 */
    BinTree TheTrees[ MaxTrees ]; /*  */
};

int main( int argc, const char *argv[] ){

    return 0;
}

/* Return the result of merging equal-sized T1 and T2 */
BinTree CombineTrees( BinTree T1, BinTree T2 ){
    if( T1->Element < T2->Element )
        return CombineTrees( T2, T1 );
    T2->NextSibling = T1->LeftChild;
    T1->LeftChild = T2;
    return T1;
}

BinQueue Merge( BinQueue H1, BinQueue H2){
    BinTree T1, T2, Carry = NULL;
    int i,j;

    if( H1->CurrentSize + H2->CurrentSize > Capacity ) return NULL;

    H1->CurrentSize += H2->CurrentSize;
    for( i = 0 , j = 1 ; j <= H1->CurrentSize ; i++ , j *= 2 ){
        T1 = H1->TheTrees[i]; T2 = H2->TheTrees[i];
        switch( 4*!!Carry + 2*!!T2 + !!T1 ){
            case 0:/* 000 */
            case 1:/* 001 */ break;
            case 2:/* 010 */H1->TheTrees[i] = T2;H2->TheTrees[i] = NULL;break;
            case 3:/* 011 */Carry = CombineTrees( T1, T2 ); H1->TheTrees[i] = H2->TheTrees[i] = NULL ; break;
            case 4:/* 100 */H1->TheTrees[i] = Carry; Carry = NULL; break;
            case 5:/* 101 */Carry = CombineTrees( T2, Carry ); H2->TheTrees[i] = NULL ; break;
            case 6:/* 110 */Carry = CombineTrees( T1, Carry ); H1->TheTrees[i] = NULL ; break;
            case 7:/* 111 */H1->TheTrees[i] = Carry ; Carry = CombineTrees( T1, T2 ); H2->TheTrees[i] = NULL ; break;
         }
    }
    return H1;
}

ElementType DeleteMin( BinQueue H){
    BinQueue DeletedQueue;
    Position DeletedTree, OldRoot;
    ElementType MinItem = Infinity; /* The minium item to be returned */
    int i, j, MinTree;/* MinTree is the index of the tree with the minium item */
    if( IsEmpty( H ) ) return -Infinity;

    for( i = 0, j = 1 ; j < H->CurrentSize ; i++, j *= 2) /* Find the minium item and the index */
        if( H->TheTrees[i]->Element < MinItem ){
            MinItem = H->TheTrees[i]->Element;
            MinTree = i;
        }
    
    DeletedTree = H->TheTrees[MinTree];
    H->TheTrees[MinTree] = NULL; /* Remove the MinTree  from the H */
    OldRoot = DeletedTree;
    DeletedTree = DeletedTree->LeftChild; free( OldRoot ); /* Remove the root */
    DeletedQueue = Initialize();
    DeletedQueue->CurrentSize = ( 1<<MinTree ) - 1 ;
    for( j = MinTree - 1 ; j >= 0 ; j--){
        DeletedQueue->TheTrees[j] = DeletedTree;
        DeletedTree = DeletedTree->NextSibling;
        DeletedQueue->TheTrees[j]->NextSibling = NULL;
    }
    H->CurrentSize -= ( DeletedQueue->CurrentSize + 1 );
    H = Merge( H, DeletedQueue );
    return MinItem;
}

BinQueue Initialize( void ){
    BinQueue H = (BinQueue)malloc(sizeof(struct Collection));
    H->CurrentSize = 0;
    for( int i=0 ; i<MaxTrees ; i++)
        H->TheTrees[i] = NULL;
    
    return H;
}

bool IsEmpty( BinQueue H ){
    int i,j;
    bool ret = false;
    for( i = 0 , j = 1 ; j <= H->CurrentSize ; i++ , j *= 2)
        if( H->TheTrees[i] != NULL ){
            ret = true;
            break;
        }
    
    return ret;
}