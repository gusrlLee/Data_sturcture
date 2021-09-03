/*Link(연결) List 배열 리스트보다 구현이 복잡하지만
메모리 제한이 없다는 장점이 있다.*/
#include<stdio.h>
#include<stdlib.h>
typedef int element;
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
//insert function
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
  if(*phead == NULL){//head가 NULL일 경우
    new_node->link = NULL;
    *phead = new_node;
  }
  else if(p == NULL){//P(선행노드)가 NULL일 경우
    new_node->link = *phead;
    *phead = new_node; 
  }
  else{//둘다 NULL이 아닐 경우
    new_node->link = p->link;
    p->link = new_node;
  }
}
//remove node function
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
  if(p == NULL)//선행 노드가 없다면.
    *phead = (*phead)->link;
  else//그 외
    p->link = removed->link;
  free(removed);
}
//LinkList print function
void display(ListNode *head)
{
  ListNode *p=head;
  while(p != NULL){
    printf("%d->",p->data);
    p=p->link;
  }
  printf("\n");
}
//search function
ListNode *search(ListNode *head, int x)
{
  ListNode *p;
  p=head;
  while(p != NULL){
    if(p->data == x) return p;
    p=p->link;
  }
  return p;// 탐색실패시 NULL 반환
}
//두개의 리스트를 하나로 만드는 함수
ListNode *concat(ListNode *head1, ListNode *head2)
{
  ListNode *p;
  if(head1 == NULL) return head2;
  else if(head2 == NULL) return head1;
  else{
    p=head1;
    while(p->link != NULL)
      p = p->link;
    p->link = head2;
    return head1;
  }
}
//리스트를 역순으로 만드는 함수
ListNode *reverse(ListNode *head)
{
  ListNode *p, *q, *r;
  p=head;
  q=NULL;
  while(p != NULL){
    r=q;      // r은 역순으로 된 노드, r은 q, q는 p를 차례대로 따라간다.
    q=p;
    p=p->link;
    q->link=r;// q의 링크 방향을 바꾼다.
  }
  return q;   // 반환
}
//create Node function
ListNode *create_node(element data, ListNode *link)
{
  ListNode *new_node;
  new_node = (ListNode *)malloc(sizeof(ListNode));
  if(new_node == NULL) error("ERROR!\n");
  new_node->data = data;
  new_node->link = link;
  return (new_node);
}
//test program
int main()
{
  ListNode *list1=NULL, *list2=NULL;
  ListNode *p;
  //create list1
  insert_node(&list1, NULL, create_node(10,NULL));
  insert_node(&list1, NULL, create_node(20,NULL)); 
  insert_node(&list1, NULL, create_node(30,NULL));
  display(list1);
  //remove
  remove_node(&list1, NULL, list1);
  display(list1);
  //create list2
  insert_node(&list2, NULL, create_node(60,NULL));
  insert_node(&list2, NULL, create_node(70,NULL));
  insert_node(&list2, NULL, create_node(80,NULL));
  //list adds
  list1 = concat(list1,list2);
  display(list1);
  list1 = reverse(list1);
  display(list1);
  //search
  p=search(list1, 20);
  printf("success!!=%d\n",p->data);  
}

