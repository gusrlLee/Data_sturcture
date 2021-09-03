#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
  element stack[MAX_STACK_SIZE];
  int top;
} StackType;
//error function
void error(char *string)
{
  fprintf(stderr,"%s",string);
  exit(1);
}
// init function
void init(StackType *s)
{
  s->top = -1;
}
//공백상태 검출
int is_empty(StackType *s)
{
  return (s->top == -1);
}
//포화상태 검출
int is_full(StackType *s)
{
  return (s->top == MAX_STACK_SIZE-1);
}
//insert function
void push(StackType *s, element item)
{
  if(is_full(s)){
    error("FULL!!\n");
  }
  else {
    s->stack[++(s->top)] = item;
  }
}
//delete function
int pop(StackType *s)
{
  if(is_empty(s))
    error("EMPTY!\n");
  else
    return s->stack[(s->top)--];
}
//peek function
int peek(StackType *s)
{
  if(is_empty(s))
    error("EMPTY!\n");
  else return s->stack[s->top];
}
//test
int main()
{
  StackType s;
  init(&s);
  push(&s,1);
  push(&s,2);
  push(&s,3);
  printf("%d\n", pop(&s));
  printf("%d\n", pop(&s));
  printf("%d\n", pop(&s));
  
  printf("%d\n", is_empty(&s));
}