#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;
//스택이 비었는지 확인
int is_empty()
{
  return (top == -1);
}
//포화 상태 검출
int is_full()
{
  return (top == MAX_STACK_SIZE-1);
}
//insert function
void push(element item)
{
  if(is_full()){
    fprintf(stderr, "%s","STACK IS FULL!!\n");
    exit(1);
  }
  else 
    stack[++top] = item;
}
//delete function
element pop()
{
  if(is_empty()){
    fprintf(stderr, "%s","NOTHING!!\n");
    exit(1);
  }
  else
    return stack[top--]; 
}
//peek function
element peek()
{
  if(is_empty()){
    fprintf(stderr, "%s","NOTHING\n");
    exit(1);
  }
  else
    return stack[top];
}
//test
int main()
{
  push(1);
  push(2);
  push(3);
  printf("%d\n",pop());
  printf("%d\n",pop());
  printf("%d\n",pop());
  printf("%d\n",is_empty());
}