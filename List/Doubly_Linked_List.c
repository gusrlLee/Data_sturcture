#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
//ListNode setting
typedef int element;
typedef struct DlistNode {
  element data;
  struct DlistNode *left_link;
  struct DlistNode *right_link;
} DlistNode;
//init function
void init(DlistNode *phead)
{
  phead->left_link = phead;
  phead->right_link = phead;
}
//Display list function
void display(DlistNode *phead)
{
  DlistNode *p;
  for(p=phead->right_link; p != phead; p=p->right_link){
    printf("<---- | %x | %d | %x | ---->\n",p->left_link, p->data, p->right_link);
  }
  printf("\n");
}
//insert Node function
void dinsert_node(DlistNode *before, DlistNode *new_node)
{
  new_node->left_link = before;
  new_node->right_link = before->right_link;
  before->right_link->left_link = new_node;
  before->right_link = new_node;
}
//remove Node function
void dremove_node(DlistNode *phead_node, DlistNode *removed)
{
  if(removed == phead_node) return;
  removed->left_link->right_link = removed->right_link;
  removed->right_link->left_link = removed->left_link;
  free(removed);
}
//test program
void main()
{
  DlistNode head_node;
  DlistNode *p[10];
  init(&head_node);
  for(int i=0; i<5; i++){
    p[i] = (DlistNode *)malloc(sizeof(DlistNode));
    p[i]->data = i;
    //insert right of headNode
    dinsert_node(&head_node, p[i]);
  }
  dremove_node(&head_node,p[4]);
  display(&head_node);
}


