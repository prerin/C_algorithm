//
//  binary_tree.c
//  
//
//  Created by 川上隼 on 2021/12/05.
//

#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//二分木のノードの定義
typedef struct node {
  char *label;
  struct node *left;
  struct node *right;
} Node;

//二分木を生成する関数
Node *create_tree(char *label, Node *left, Node *right) {
    Node *root = (Node*)malloc(sizeof(Node));
    root->label = label;
    root->left = left;
    root->right = right;
    return root;
}

//先行順の深さ優先探索
void preorder(Node *n) {
    if (n == NULL) return;
    printf("%s ", n->label);
    preorder(n->left);
    preorder(n->right);
}

//中間順の深さ優先探索
void inorder(Node *n) {
    if (n == NULL) return;
    inorder(n->left);
    printf("%s ", n->label);
    inorder(n->right);
}

//後行順の深さ優先探索
void postorder(Node *n) {
    if (n == NULL) return;
    postorder(n->left);
    postorder(n->right);
    printf("%s ", n->label);
}

//二分木を表示する関数
void display(Node *n) {
    if (n == NULL) return;
    printf("%s(", n->label);
    if (n->left == NULL && n->right == NULL) {
        printf("null,null)");
        return;
    } else if (n->left == NULL) {
        printf("null");
    }
    display(n->left);
    if (n->right == NULL) {
        printf("null)");
        return;
    }
    printf(",");
    display(n->right);
    printf(")");
}

//二分木の高さを返す関数
int height(Node *n) {
    if(n == NULL) {
        return 0;
    }
    int l = height(n->left);
    int r = height(n->right);
    return (l >= r) ? (l + 1) : (r + 1);
}

//二分木を削除する関数
void delete_tree(Node *n) {
    if (n == NULL) return;
    delete_tree(n->left);
    delete_tree(n->right);
    free(n);
}

//与えられた二分木を作り、それぞれの探索をする関数
int main(void) {
  // Build a binary tree
    Node *d = create_tree("D", NULL, NULL);
    Node *i = create_tree("I", NULL, NULL);
    Node *h = create_tree("H", NULL, NULL);
    Node *g = create_tree("G", NULL, NULL);
    Node *e = create_tree("E", NULL, i);
    Node *f = create_tree("F", h, g);
    Node *b = create_tree("B", f, NULL);
    Node *c = create_tree("C", d, e);
    Node *a = create_tree("A", c, b);

    printf("preorder: ");
    preorder(a);
    printf("\n");

    printf("inorder: ");
    inorder(a);
    printf("\n");

    printf("postorder: ");
    postorder(a);
    printf("\n");

    display(a);
    printf("\n");
    
    printf("height: %d\n", height(a));

    delete_tree(a);

    return EXIT_SUCCESS;
}
