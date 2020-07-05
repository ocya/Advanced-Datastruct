#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Infinity 65535
#define NegInfiity -65536

typedef int  ElementType;
typedef enum ColorType{ Red , Black } ColorType;

/* Top-Down Red Black Trees*/
typedef struct RedBlackNode *RedBlackTree;
struct RedBlackNode{
    ElementType Element;
    RedBlackTree Left,Right;
    ColorType Color;
};
typedef RedBlackTree Position;
Position NullNode = NULL;

int main(int argc, const char *argv[]){

    return 0;
}

/* Initialization proceddure */
RedBlackTree Initialize( void ){
    RedBlackTree T;

    if(NullNode == NULL){
        NullNode = (Position)malloc(sizeof(struct RedBlackNode));
        NullNode->Left = NullNode->Right = NullNode;
        NullNode->Color = Black;
        NullNode->Element = Infinity;
    }

    /* Create the header node */
    T = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
    T->Element = NegInfiity;
    T->Left = T->Right = NullNode;
    T->Color = Black;
    /* T is root sentinel store the key NegInfinity and the right pointer to the real root */
    return T;
}

Position Rotate( ElementType Item , Position Parent){
    if( Item < Parent->Element)
        return Parent->Left = Item < Parent->Left->Element ?
            SingleRotateWithLeft( Parent->Left ) : SingleRotateWithRight( Parent->Left );
    else
        return Parent->Right = Item < Parent->Right->Element ?
            SingleRotateWithLeft( Parent->Right ): SingleRotateWithRight( Parent->Right );
}

static Position X,P,GP,GGP;

/* When we see a node X that has two red children  */
/* We make X red and the two children black */
/* This will induce a red black violation only if X's parent P is also red */
/*
在函数的返回类型前加上static，就是静态函数。其特性如下：

静态函数只能在声明它的文件中可见，其他文件不能引用该函数
不同的文件可以使用相同名字的静态函数，互不影响
*/
static void HandleReorient( ElementType Item, RedBlackTree T){
    
    X->Color = Red;/* Do the color filp */
    X->Left->Color = Black;
    X->Right->Color = Black;

    if( P->Color == Red ){/* Have to rotate */
        GP->Color = Red;
        if( ( Item < GP->Element ) != ( Item < P->Element ))
            P = Rotate( Item , GP );
        X = Rotate( Item , GGP );
        X->Color = Black;
    }

    T->Right->Color = Black;/* Make the root black */
}

RedBlackTree Insert( ElementType Item, RedBlackTree T){
    X = P = GP = T;
    NullNode->Element = Item;
    while( X->Element != Item ){/* Descend down the tree */
        GGP = GP; GP = P; P = X;
        if( Item < X->Element )
            X = X->Left;
        else
            X = X->Right;
        if( X->Left->Color == Red && X->Right->Color == Red)
            HandleReorient( Item , T );        
    }

    if( X != NullNode ) return NullNode; /* Duplicate */
    X = (Position)malloc(sizeof(struct RedBlackNode));
    X->Element = Item;
    X->Left = X->Right = NullNode;

    if( Item < P->Element)
        P->Left = X;
    else
        P->Right = X;
    HandleReorient( Item , T );/* Color red; maybe rotate */

    return T;
}

Position SingleRotateWithLeft( Position X){
    Position Y = X->Left;
    X->Left = Y->Right;
    Y->Right = X;
    return Y;
}

Position SingleRotateWithRight( Position X){
    Position Y = X->Right;
    X->Right = Y->Left;
    Y->Left = X;
    return Y;
}
