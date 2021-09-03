#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<limits.h>

#define FALSE 0
#define TRUE 1
// List setting
typedef int element;
typedef struct ListNode{
  element data;
  struct ListNode *link;
} ListNode;
typedef struct {
  ListNode *head;
  int length;
} LinkedListType;
// error function
void error(char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(1);
}
//insert_node function
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
  if(*phead == NULL){//head노드가 없을 때
    new_node->link = NULL;
    *phead = new_node;
  }
  else if(p == NULL){//선행 노드가 없을 때 
    new_node->link = *phead;
    *phead = new_node;
  }
  else{//그 외
    new_node->link = p->link;
    p->link = new_node;
  }
}
//remove_node fucntion
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
  if( p == NULL)//선행 노드가 없을 때
    *phead = (*phead)->link;
  else
    p->link = removed->link;
  free(removed);
}
//리스트 안에서 pos위치의 노드를 반환
ListNode *get_node_at(LinkedListType *list, int pos)
{
  ListNode *temp = list->head;
  if(pos < 0) return NULL;
  for(int i=0; i<pos; i++){
    temp = temp->link;
  }
  return temp;
}
//list data count
int get_length(LinkedListType *list)
{
  return list->length;
}
//주어진 위치에 데이터를 삽입
void add(LinkedListType *list, int position, int data)
{
  ListNode *p;
  if((position>=0) && (position<=list->length)){
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if(node == NULL) error("CANNOT!!\n");
    node->data = data;
    p = get_node_at(list, position-1);
    insert_node(&(list->head), p, node);
    list->length++;
  }
}
//insert last_data
void add_last(LinkedListType *list, element data)
{
  add(list, get_length(list), data);
}
//insert first_data
void add_first(LinkedListType *list, element data)
{
  add(list, 0, data);
}
//empty function
int is_empty(LinkedListType *list)
{
  if(list->head == NULL) return TRUE;
  else return FALSE;
}
//delete function
void delete(LinkedListType *list, int pos)
{
  if(!is_empty(list) && (pos>=0) && (pos<list->length)){
    ListNode *p = get_node_at(list, pos-1);
    ListNode *removed = get_node_at(list, pos);
    remove_node(&(list->head), p, removed);
    list->length--;
  }
}
element get_entry(LinkedListType *list, int pos)
{
  ListNode *p;
  if(pos >= list->length) error("OVER!\n");
  p = get_node_at(list, pos);
  return p->data;
}
//clear list
void clear(LinkedListType *list)
{ 
  for(int i=0; i<list->length; i++)
    delete(list, i);
}
//display list
void display(LinkedListType *list)
{
  ListNode *node = list->head;
  printf("(");
  for(int i=0; i<list->length; i++){
    printf("%d->", node->data);
    node = node->link;
  }
  printf(")\n");
}
//search function
int is_in_list(LinkedListType *list, element item)
{
  ListNode *p;
  p = list->head;
  while(p != NULL){
    if(p->data == item)
      break;
    p = p->link;
  }
  if(p == NULL) return FALSE;
  else return TRUE;
}
void init(LinkedListType *list)
{
  if(list == NULL) return;
  list->length = 0;
  list->head=NULL;
}
//test program
int main()
{
  LinkedListType list1;

  init(&list1);
  add(&list1, 0, 20);
  add_last(&list1, 30);
  add_first(&list1, 10);
  add_last(&list1, 40);
  display(&list1);

  delete(&list1, 3);
  display(&list1);

  delete(&list1, 0);
  display(&list1);

  printf("%s\n", is_in_list(&list1, 20)==TRUE ? "success" : "failure");
  printf("%d\n", get_entry(&list1, 0));
}