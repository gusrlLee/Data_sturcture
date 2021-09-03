#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef int element;
typedef struct {
  element item;
  struct StackNode *link;
} StackNode;
typedef struct {
  StackNode *top;
} LinkedStackType;

//init function
void init(LinkedStackType *s)
{
  s->top = NULL;
}
//공백상태 검출
int is_empty(LinkedStackType *s)
{
  return (s->top == NULL);
}
void push(LinkedStackType *s, element item)
{
  StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
  if(new_node == NULL){
    fprintf(stderr, "%s", "ERROR!!\n");
    exit(1);
  }
  else{
    new_node->item = item;
    new_node->link = s->top;
    s->top = new_node;
  }
}
element pop(LinkedStackType *s)
{
  if(is_empty(s)){
    fprintf(stderr, "%s", "ERROR!!\n");
    exit(1);
  }
  else {
    StackNode *temp = s->top;
    element item = temp->item;
    s->top = temp->link;
    free(temp);
    return item;  
  }
}
element peek(LinkedStackType *s)
{
  if(is_empty(s)){
    fprintf(stderr, "%s", "ERROR!!\n");
    exit(1);
  }
  else return s->top->item;
}
int main()
{
  LinkedStackType s;
  init(&s);
  push(&s,1);
  push(&s,2);
  push(&s,3);
  printf("%d\n",pop(&s));
  printf("%d\n",pop(&s));
  printf("%d\n",pop(&s));
  printf("%d\n",is_empty(&s));
}