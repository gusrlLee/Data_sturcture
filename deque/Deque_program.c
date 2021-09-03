#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int element;
typedef struct DlistNode{
  element data;
  struct DlistNode *llink;
  struct DlistNode *rlink;
} DlistNode;
typedef struct DequeType {
  DlistNode *head;
  DlistNode *tail;
} DequeType;
//error function
void error(char *message)
{
  fprintf(stderr, "%s", message);
  exit(1);
}
//init()
void init(DequeType *dq)
{
  dq->head = dq->tail = NULL;
}
//insert function
DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink)
{
  DlistNode *node = (DlistNode *)malloc(sizeof(DlistNode));
  if(node == NULL) error("ERROR!\n");
  node->llink = llink;
  node->data = item;
  node->rlink = rlink;
  return node;
}
int is_empty(DequeType *dq)
{
  if(dq->head == NULL) return TRUE;
  else return FALSE;
}
void add_rear(DequeType *dq, element item)
{
  DlistNode *new_node = create_node(dq->tail, item, NULL); //메모리 할당
  if(is_empty(dq))
    dq->head = new_node;// 비어있으면 head에 선언
  else  
    dq->tail->rlink = new_node; // 아니면 tail이 가리키는 노드의 rlink에 대입.
  dq->tail = new_node; // 그리고 tail을 수정
}
void add_front(DequeType *dq, element item)
{//위와 동일
  DlistNode *new_node = create_node(NULL, item, dq->head);
  if(is_empty(dq))
    dq->tail = new_node;
  else 
    dq->head->llink = new_node;
  dq->head = new_node;
}
//delete function
element delete_front(DequeType *dq)
{
  element item; // 반환될 데이터
  DlistNode *removed_node; // 삭제될 노드 설정
  if(is_empty(dq)) error("ERROR!\n"); //에러
  else {
    removed_node = dq->head; // 삭제할 노드 선언
    item = removed_node->data; // 반환 될 데이터 임시저장
    dq->head = dq->head->rlink; // 포인터 변경
    free(removed_node);
    if(dq->head == NULL)
      dq->tail = NULL;
    else
      dq->head->llink = NULL; // 연결된 노드가 사라졌으므로 llink를 NULL로 설정
  }
  return item;
}
element delete_rear(DequeType *dq)
{//위와 동일
  element item;
  DlistNode *removed_node;
  if(is_empty(dq)) error("ERROR!\n");
  else {
    removed_node = dq->tail;
    item = removed_node->data;
    dq->tail = dq->tail->llink;
    free(removed_node);
    if(dq->head == NULL)
      dq->tail = NULL;
    else
      dq->head->rlink = NULL;
  }
  return item;
}
//display
void display(DequeType *dq)
{
  DlistNode *p;
  printf("(");
  for(p=dq->head; p!=NULL; p=p->rlink){
    printf("%d->",p->data);
  }
  printf(")\n");
}
//test program
int main()
{
  DequeType deque;

  init(&deque);
  add_front(&deque, 10);
  add_front(&deque, 20);
  add_rear(&deque, 30);
  display(&deque);

  delete_front(&deque);
  delete_rear(&deque);
  display(&deque);
}