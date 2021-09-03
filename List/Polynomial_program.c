#include<stdio.h>
#include<stdlib.h>
//ListNode setting
typedef struct ListNode{
  int coef;
  int expon;
  struct ListNode *link;  
} ListNode;
//Header Node setting
typedef struct ListHeader{
  int length;
  ListNode *head;
  ListNode *tail;
} ListHeader;
//error function
void error(char *message)
{
  fprintf(stderr,"%s\n",message);
  exit(1);
}
// init function
void init(ListHeader *plist)
{
  plist->length = 0;
  plist->head = plist->tail = NULL;
}
//insert function 
void insert_node_last(ListHeader *plist, int coef, int expon)
{
  ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
  if(temp == NULL) error("MEMORY ERROR!\n");
  temp->coef = coef;
  temp->expon = expon;
  temp->link = NULL;
  if(plist->tail == NULL){//Node가 존재하지 않을 때
    plist->head = plist->tail = temp;
  }
  else {
    plist->tail->link = temp;
    plist->tail = temp;
  }
  plist->length++;
}
//poly_add fucntion
void poly_add(ListHeader *plist1, ListHeader *plist2, ListHeader *plist3)
{
  ListNode *a = plist1->head;
  ListNode *b = plist2->head;
  int sum=0;
  while (a && b){
    if(a->expon == b->expon){
      sum = a->coef+b->coef;
      if(sum != 0) insert_node_last(plist3, sum,a->expon);
      a=a->link; b=b->link;
    }
    else if(a->expon > b->expon){
      insert_node_last(plist3, a->coef, a->expon);
      a=a->link;
    }
    else {
      insert_node_last(plist3, b->coef, b->expon);
      b=b->link;
    }
  }
    for(; a != NULL; a=a->link)
      insert_node_last(plist3, a->coef, a->expon);
    for(; b != NULL; b=b->link)
      insert_node_last(plist3, b->coef, b->expon);
}
//Display function
void Display(ListHeader *plist)
{
  ListNode *p = plist->head;
  for(;p;p=p->link){
    printf("%d %d\n", p->coef, p->expon);
  }
}
//test program
void main()
{
  ListHeader list1, list2, list3;
  //list init
  init(&list1);
  init(&list2);
  init(&list3);
  //create list1
  insert_node_last(&list1, 3, 12);
  insert_node_last(&list1, 2, 8);
  insert_node_last(&list1, 1, 0);
  //create list2
  insert_node_last(&list2, 8, 12);
  insert_node_last(&list2, -3, 10);
  insert_node_last(&list2, 10, 6);
  //create list3
  poly_add(&list1, &list2, &list3);

  Display(&list3);
}