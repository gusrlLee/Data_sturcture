#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 100
#define MAX_STRING 100
typedef struct {
  int student_no;
  char name[MAX_STRING];
  char address[MAX_STRING];
} element;
element stack[MAX_STACK_SIZE];
int top = -1;
//공백 상태 검출
int is_empty()
{
  return (top == -1);
}
//포화 상태 검출
int is_full()
{
  return (top == MAX_STACK_SIZE - 1);
}
//push function
void push(element item)
{
  if(is_full()){
    fprintf(stderr, "%s","FULL!!\n");
    exit(1);
  }
  else 
    stack[++top] = item;
}
//pop function
element pop()
{
  if(is_empty()){
    fprintf(stderr, "%s","EMPTY!!\n");
    exit(1);
  }
  else return stack[top--];
}
//peek fucntion
element peek()
{
  if(is_empty()){
    fprintf(stderr, "%s","EMPTY!!\n");
    exit(1);
  }
  else return stack[top];
}
//test
int main()
{
  element ie, oe;
  strcpy(ie.name, "HongGilDong");
  strcpy(ie.address, "Seoul");
  ie.student_no = 20053001;
  push(ie);
  oe = pop();
  printf("name: %s\n",oe.name);
  printf("address: %s\n",oe.address);
  printf("student_number: %d\n",oe.student_no);
}