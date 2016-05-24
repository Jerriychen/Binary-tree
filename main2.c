//
//  main.c
//  bitree2
//
//  Created by   chenzzh on 16/5/24.
//  Copyright © 2016年 chenzezhong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
/*
 二叉树操作(包含二叉树创建、销毁、计算深度、结点数目、先序遍历、中序遍历、后序遍历、二叉树线索化遍历)
 时间：2015-1-2 22:21
 说明：二叉树操作(包含二叉树创建、销毁、计算深度、结点数目、先序遍历、中序遍历、后序遍历、二叉树线索化遍历)
 */


/*声明一个枚举类型来表示指针域状态，Link=0表示指向左右孩子，Thread=1表示指向前驱或者后继*/
typedef enum{Link=0,Thread=1}PointerTag;

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
    PointerTag LTag,RTag;//定义标志位
}BiTNode,*BiTree;

/*
 函数名称：CreateBinaryTree(BiTree *T)
 说明：创建二叉树，以输入'#'作为空指针标志，按先序遍历的顺序输入二叉树中各个结点
 */
void CreateBinaryTree(BiTree *T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(BiTree)malloc(sizeof(BiTNode));
        
        if(!(*T))//容错判断，申请内存空间失败时返回
            return;
        
        (*T)->data=ch;
        
        CreateBinaryTree(&((*T)->lchild));
        if((*T)->lchild)//当存在左孩子时将标志位定义为Link
            //if(((*T)->lchild)!=NULL)
            (*T)->LTag=Link;
        
        CreateBinaryTree(&((*T)->rchild));//当存在右孩子时将标志位定义为Link
        if((*T)->rchild)
            (*T)->RTag=Link;
    }
}

/*先序遍历二叉树*/
void PreOrderTraverse(BiTree T)
{
    if(!T)
        return;
    else
    {
        printf("%c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

/*中序遍历二叉树*/
void InOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    else
    {
        InOrderTraverse(T->lchild);
        printf("%c",T->data);
        InOrderTraverse(T->rchild);
    }
}

/*后序遍历二叉树*/
void PostOrderTraverse(BiTree T)
{
    if(!T)
        return;
    else
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c",T->data);
    }
}
/*计算二叉树深度*/
int BinaryDepth(BiTree T)
{
    int ldepth,rdepth;
    
    if(!T)
        return 0;
    else
    {
        ldepth=BinaryDepth(T->lchild);
        rdepth=BinaryDepth(T->rchild);
        return (ldepth>rdepth?ldepth+1:rdepth+1);
    }
}

/*计算结点数量*/
int NodeCount(BiTree T)
{
    if(!T)
        return 0;
    else
        return (NodeCount(T->lchild)+NodeCount(T->rchild)+1);
}
/*销毁一个二叉树*/
void DestoryBinaryTree(BiTree *T)
{
    if(*T)
    {
        if((*T)->lchild)
            DestoryBinaryTree(&((*T)->lchild));
        if((*T)->rchild)
            DestoryBinaryTree(&((*T)->rchild));
        free(*T);
        *T=NULL;
    }
}

/*********线索化二叉树操作*********/

BiTree pre; /* 全局变量,始终指向刚刚访问过的结点 */
/*中序线索化*/
void InThreading(BiTree T)
{
    if(T)
    {
        InThreading(T->lchild);
        /*当没有左孩子时前驱线索*/
        if(!T->lchild)
        {
            T->LTag=Thread;
            T->lchild=pre;
        }
        /*当没有右孩子时后继线索*/
        if(!pre->rchild)
        {
            pre->RTag=Thread;
            pre->rchild=T;
        }
        
        pre=T;/* 保持pre指向前驱 */
        InThreading(T->rchild);
    }
}
/*中序遍历二叉树T，并将其线索化，head为头指针
 在线索二叉树中头结点lchild左孩子指向二叉树的根结点，
 rchild右孩子指向中序遍历时访问的最后一个结点；
 二叉树的中序遍历序列中第一个结点的lchild指针和最后一个孩子的rchild指向头结点
 */
void InOrderThreading(BiTree *head,BiTree T)
{
    *head=(BiTree)malloc(sizeof(BiTNode));
    if(!*head)/*如果创建失败*/
        return;
    /*初始化头结点*/
    (*head)->LTag=Link;
    (*head)->RTag=Thread;
    (*head)->rchild=*head;/*头指针回指*/
    
    if(!T)/*对传入第2个参数进行合法性检测，并采取相应处理,当T为空时*/
    {
        (*head)->lchild=(*head);
    }
    else
    {
        (*head)->lchild=T;//当T为非空时头结点指向二叉树的根结点T
        pre=(*head);
        
        InThreading(T);
        
        /*对最后一个结点线索化*/
        pre->RTag=Thread;
        pre->rchild=*head;
        (*head)->rchild=pre;/*头结点指向中序遍历最后一个结点*/
    }
}

/*中序遍历一棵二叉线索树T(T为头结点)*/
void InOrderTraverseThreadTree(BiTree T)
{
    BiTree p;
    p=T->lchild;
    
    while(p!=T)/*当还未遍历迭代完整棵二叉树，空树或遍历结束时p=T*/
    {
        while(p->LTag==Link)
        {
            p=p->lchild;
        }
        
        printf("%c ",p->data);
        
        while((p->rchild!=T)&&(p->RTag==Thread))
        {
            p=p->rchild;
            printf("%c ",p->data);	
        }
        p=p->rchild;		
    }
    
    
}

int main(int argc, char *argv[]) 
{
    
    BiTree T,H;
    printf("请创建一棵二叉树(如:'ABDH##I##EJ###CF##G##')\n");
    CreateBinaryTree(&T);
    
    printf("\n二叉树的深度为:%d,结点数目为:%d\n",BinaryDepth(T),NodeCount(T));
    
    printf("\n先序遍历的结果是:\n");
    PreOrderTraverse(T);
    
    printf("\n中序遍历的结果是:\n");
    InOrderTraverse(T);
    
    printf("\n后序遍历的结果是:\n");
    PostOrderTraverse(T);
    
    printf("\n对二叉树进行中序线索化\n");
    InOrderThreading(&H,T);
    printf("\n中序遍历线索二叉树的结果是:\n");
    InOrderTraverseThreadTree(H);
    
    printf("\n摧毁一棵二叉树\n");
    DestoryBinaryTree(&T);
    printf("\n二叉树的深度为:%d,结点数目为:%d\n",BinaryDepth(T),NodeCount(T));
    return 0;
}
