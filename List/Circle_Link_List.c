#include<stdio.h>
#include<stdlib.h>
typedef int element;
// Node setting
typedef struct ListNode{
  element data;
  struct ListNode *link;
}ListNode;
//오류 처리 함수
void error(char *message)
{
  fprintf(stderr,"%s\n",message);
  exit(1);
}
//Create_ListNode function
ListNode *create_node(element data, ListNode *link)
{
  ListNode *new_node;
  new_node = (ListNode *)malloc(sizeof(ListNode));
  if(new_node == NULL)
    error("NULL!!\n");
  new_node->data = data;
  new_node->link = link;
  return (new_node);
}
//Display LinkList function
void display(ListNode *head)
{
  ListNode *p;
  if(head == NULL) return;

  p=head;
  do{
    printf("%d->",p->data);
    p=p->link;
  } while(p != head);
}
//insert_first_function
void insert_first(ListNode **phead, ListNode *new_node)
{
  if(*phead == NULL){
    *phead = new_node;
    new_node->link = new_node;
  }  
  else{
    new_node->link=(*phead)->link;
    (*phead)->link = new_node;
  }
}
//insert_last_function
void insert_last(ListNode **phead, ListNode *new_node)
{
  if(*phead == NULL){
    *phead = new_node;
    new_node->link = new_node;
  }
  else{
    new_node->link = (*phead)->link;
    (*phead)->link = new_node;
    *phead = new_node;
  }
}
//get_length function
int get_length(ListNode *head)
{
  ListNode *p;
  int length=0;
  if(head == NULL)
    return length;
  else {
    p=head;
    do {
      length++;
      p=p->link;
    }while(p != head);
    return length;
  }
}
//test program
int main()
{
  ListNode *list1=NULL;
  int len;
  // list1 = 30->20->10
  insert_first(&list1, create_node(10,NULL));
  insert_first(&list1, create_node(20,NULL));
  insert_first(&list1, create_node(30,NULL));
  insert_last(&list1, create_node(40,NULL));
  display(list1);
  len = get_length(list1);
  printf("list1 length = %d\n",len);
}

