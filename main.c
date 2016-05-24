//
//  main.c
//  bitree
//
//  Created by   chenzzh on 16/5/22.
//  Copyright © 2016年 chenzezhong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct binary_tree)

struct binary_tree
{
    char data;
    struct binary_tree *lson;
    struct binary_tree *rson;
};

struct binary_tree *Creatbitree();
void Preorder(struct binary_tree *root);//先序遍历
void Inorder(struct binary_tree *root);//中序遍历
void Postorder(struct binary_tree *root);//后序遍历
struct binary_tree *Exchange(struct binary_tree *root);
int Height(struct binary_tree *root);


int main()
{
    int n,h=0;
    struct binary_tree *root;
    root=NULL;
    do {
        printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("              1.     create bitree               \n");
        printf("              2.     Preorder                    \n");
        printf("              3.     Inorder                     \n");
        printf("              4.     Postorder                   \n");
        printf("              5.     Exchange                    \n");
        printf("              6.     Height                      \n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("please input your choice(1--6):");
        scanf("%d",&n);
        switch(n)
        {
            case 1 : root=Creatbitree();break;
            case 2 : Preorder(root);break;
            case 3 : Inorder(root);break;
            case 4 : Postorder(root);break;
            case 5 : root=Exchange(root);break;
            case 6 : h=Height(root);printf("∂˛≤Ê ˜µƒ∏ﬂ∂»Œ™%d\n",h);break;
            default:printf("—°‘Ò¥ÌŒÛ£¨÷ÿ–¬—° \n");
        }
    }while(1);
    return 0;
}


struct binary_tree *Creatbitree()
{
    char ch;
    struct binary_tree *T;
    scanf("%c",&ch);
    if(ch=='#')T=NULL;
    else{
        T = (struct binary_tree *)malloc(LEN);
        T->data = ch;
        T->lson = Creatbitree();
        T->rson = Creatbitree();
    }
    return T;
}


void Preorder(struct binary_tree *root)
{
    if (root!=NULL)
    {
        printf("%c ",root->data);
        Preorder(root->lson);
        Preorder(root->rson);
    }
    else return;
}


void Inorder(struct binary_tree *root)
{
    int i=0;
    struct binary_tree *p,*a[100];
    p=root;
    while (i!=0 || p!=NULL)
    {
        while (p!=NULL)
        {
            i++;
            a[i]=p;
            p=p->lson;
        }
        if (i!=0)
        {
            p=a[i];
            i--;
            printf("%c ",p->data);
            p=p->rson;
        }
    }
}


void Postorder(struct binary_tree *root)
{
    struct binary_tree *p,*a[100];
    int i=0,b[100];
    p=root; a[0]=NULL;
    while (i!=0 || p!=NULL)
    {
        while (p!=NULL)
        {
            if (b[i]==2) break;
            i++;
            a[i]=p;
            b[i]=0;
            p=p->lson;
        }
        if (i!=0)
        {
            if (p==NULL)
            { b[i]++; p=a[i];}
            if (b[i]==2)
            {
                printf("%c ",p->data);
                b[i]=0;  i--;
                p=a[i]; b[i]++;
            }
            if (i==0) {p=NULL; break; }
            if (b[i]==1) p=p->rson;
        }
    }
}


struct binary_tree *Exchange(struct binary_tree *root)
{
    struct binary_tree *p;
    if (root==NULL) return root;
    p=root->lson;
    root->lson=root->rson;
    root->rson=p;
    Exchange(root->lson);
    Exchange(root->rson);
    return root;
}


int Height(struct binary_tree *root)
{
    int maxh=0,h1,h2;
    if (root!=NULL)
    {
        h1=Height(root->lson);
        h2=Height(root->rson);
        maxh=h1>h2?h1+1:h2+1;
    }
    return maxh;
}

