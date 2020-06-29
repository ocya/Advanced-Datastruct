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
        NullNode = malloc(sizeof(struct SplayNode));
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