#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_CHAR_PER_LINE 1000
#define MAX_NAME 256
void warning(char *);
void error(char *);

#define FALSE 0
#define TRUE 1
//value setting
typedef struct {
  char a[MAX_CHAR_PER_LINE];
} element;
typedef struct ListNode {
  element data;
  struct ListNode *link;
} ListNode;
typedef struct {
  ListNode *head;
  int length;
} LinkedListType;

//init function
void init(LinkedListType *list)
{
  if(list == NULL) return;
  list->length = 0;
  list->head=NULL;
}
//insert_node function
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
  if(*phead == NULL){
    new_node->link = NULL;
    *phead = new_node;
  }
  else if(p == NULL){
    new_node->link = *phead;
    *phead = new_node;
  }
  else{
    new_node->link = p->link;
    p->link = new_node;
  }
}
//remove_node fucntion
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
  if( p == NULL)
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
//add function
void add(LinkedListType *list, int position, element data)
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
element get_entry(LinkedListType *list, int pos)
{
  ListNode *p;
  if(pos >= list->length) error("OVER!\n");
  p = get_node_at(list, pos);
  return p->data;
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
void clear(LinkedListType *list)
{ 
  for(int i=0; i<list->length; i++)
    delete(list, i);
}
void Display(LinkedListType *buffer)
{
  ListNode *temp_node;
  temp_node = buffer->head;

  printf("********************\n");
  for(int i=0; i<buffer->length; i++){
    printf("%s",temp_node->data.a);
    temp_node = temp_node->link;
  }
  printf("********************\n");
}
void warning(char *message)
{
  fprintf(stderr,"%s\n", message);
}
void error(char *message)
{
  fprintf(stderr,"%s\n", message);
  exit(1);
}
void help()
{
  printf("********************\n");
  printf("i: insert\n");
  printf("d: delete\n");
  printf("r: read_file\n");
  printf("w: write_file\n");
  printf("q: quit\n");
  printf("********************\n");
}
void read_file(LinkedListType *buffer)
{
  char fname[MAX_NAME];
  FILE *fd;
  element p;
  if( !is_empty(buffer)){
    clear(buffer);
  }
  init(buffer);

  printf("FILE NAME: ");
  scanf("%s", fname);
  if((fd = fopen(fname,"r")) == NULL){
    warning("CANNOT OPEN FILE!\n");
    return;
  }
  while(fgets(p.a, MAX_CHAR_PER_LINE, fd)){
    add_last(buffer, p);
  }
  fclose(fd);
  Display(buffer);
}
void write_file(LinkedListType *buffer)
{
  char fname[MAX_NAME];
  FILE *fd;
  element p;

  printf("FILE NAME: ");
  scanf("%s", fname);
  if((fd = fopen(fname,"w")) == NULL){
    warning("CANNOT OPEN FILE!\n");
    return;
  }
  for(int i=0; i<get_length(buffer); i++){
    p = get_entry(buffer, i);
    fputs(p.a, fd);
  }
  fclose(fd);
  Display(buffer);
}
void delete_Line(LinkedListType *buffer)
{
  int position;
  if(is_empty(buffer)){
    printf("CANNOT DELETE LINE!\n");
  }
  else {
    printf("CHOICE LINE:\n");
    scanf("%d",&position);
    delete(buffer,position);
  }
  Display(buffer);
}
void insert_Line(LinkedListType *buffer)
{
  int position;
  char line[MAX_CHAR_PER_LINE];
  element p;
  
  printf("ENTER INSERT_POSITION: \n");
  scanf("%d", &position);

  printf("ENTER CONTENTS: \n");
  fflush(stdin);
  fgets(line, MAX_CHAR_PER_LINE, stdin);
  strcpy(p.a, line);
  add(buffer, position, p);
  Display(buffer);
}
void do_command(LinkedListType *buffer, char command)
{
  switch (command)
  {
  case 'd':
    delete_Line(buffer);
    break;
  case 'i':
    insert_Line(buffer);
    break;
  case 'r':
    read_file(buffer);
    break;
  case 'q':
    break;
  }
}
void main()
{
  char command;
  LinkedListType buffer;

  init(&buffer);
  do{
    help();
    command = getchar();
    do_command(&buffer, command);
    fflush(stdin);
  }while(command != 'q');

}

