#include<stdio.h>
#include<stdlib.h>

typedef char ElementType;

typedef struct SplayNode *PtroSplayNode;
struct SplayNode{
    ElementType Element;
    PtroSplayNode Left,Right;
};
typedef PtroSplayNode SplayTree;
typedef struct SplayNode *Position;

/* 静态全局变量，当有多个源文件时，将全局变量的作用域限制在当前源文件中 */
/* 若没有 static 关键字修饰，则该全局变量的作用域为整个工程 */
static Position NullNode = NULL;


int main(int argc,const char *argv[]){

    return 0;
}

SplayTree Initialize(void){
    if(NullNode == NULL){
        NullNode = (Position)malloc(sizeof(struct SplayNode));
        NullNode->Left = NullNode->Right = NullNode;
    }
    return NullNode;
}
/*Top-Down splay procedure,*/
/*not requiring Item to be in the tree*/
/*X should be current root of splay tree  */
/*对节点进行访问后，调整树*/
SplayTree Splay(ElementType Item,Position X){
    static struct SplayNode Header;
    Position LeftTreeMax,RightTreeMin;
    Header.Left = Header.Right = NullNode;
    LeftTreeMax = RightTreeMin = &Header;
    NullNode->Element = Item;

    while( Item != X->Element ){
        if( Item < X->Element ){
            /* if(Item > X->Left->Element) , case zig-zag rotation   */
            /* just take the simplified top-down zig-zag  */
            /* look at the link operation  */
            if( Item < X->Left->Element)    
                X = SingleRotateWithLeft( X );
            if( X->Left == NullNode )
                break;
            /* Link right */
            RightTreeMin->Left = X;
            RightTreeMin = X;
            X = X->Left;
        }else{
            /* zag-zig rotation is similar to zig-zag case */
            if( Item > X->Right->Element)
                X = SingleRotateWithRight( X );
            if( X->Right == NullNode)
                break;
            /* Link left */
            LeftTreeMax->Right = X;
            LeftTreeMax = X;
            X = X->Right;
        }/* while Item != X->Element */       
    }
    /* Reassemble */
    LeftTreeMax->Right = X->Left;
    RightTreeMin->Left= X->Right;
    X->Left = Header.Right;
    X->Right = Header.Left;
    
    return X;
}

SplayTree Insert(ElementType Item , SplayTree T){
    Position NewNode = (Position)malloc(sizeof(struct SplayNode));
    NewNode->Element = Item;
    if( T== NullNode){
        NewNode->Left = NewNode->Right = NullNode;
        T = NewNode;
    }else{
        T = Splay( Item, T );
        if( Item < T->Element){
            NewNode->Left = T->Left;
            NewNode->Right = T;
            T->Left = NullNode;
            T = NewNode;
        }else if( Item > T->Element){
            NewNode->Right = T->Right;
            NewNode->Left = T;
            T->Right = NullNode;
            T = NewNode;
        }else 
            return T; /* The Item is already in the SplayTree */
    }
    return T;
}

SplayTree Remove(ElementType Item, SplayTree T ){
    Position NewTree;
    if( T != NullNode ){
        T = Splay( Item ,T );
        if( Item == T->Element ){
            if( T->Left == NullNode )
                NewTree = T->Right;
            else {
                NewTree = T->Left;
                NewTree = Splay( Item , NewTree);/* All elements in left subtree is smaller than Item , the NewTree's root is T's LeftChild  */
                NewTree->Right = T->Right;      /* The NewTree's right subtree is empty */
            }
            free(T);
            T = NewTree;  
        }
    }
    return T;
}


/*Zig operation*/
Position SingleRotateWithLeft( Position X ){
    Position Y = X->Left;
    X->Left = Y->Right;
    Y->Right = X;
    return Y;
}

Position SingleRotateWithRight( Position X ){
    Position Y = X->Right;
    X->Right = Y->Left;
    Y->Left = X;
    return Y;
}
