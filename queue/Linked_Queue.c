#include<stdio.h>
#include<stdlib.h>
//queue setting
typedef int element;
typedef struct {
  element item;
  struct QueueNode *link;
} QueueNode;
typedef struct {
  QueueNode *front, *rear;
} QueueType;
//error function
void error(char *message)
{
  fprintf(stderr, "%s", message);
  exit(1);
}
void init(QueueType *q)
{
  q->front = q->rear = NULL; //queue초기화
}
int is_empty(QueueType *q)
{
  return (q->front == NULL);
}
void enqueue(QueueType *q, element item)
{
  QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
  if(temp == NULL)
    error("CANNOT!!\n");
  else {
    temp->item = item; // 데이터 저장
    temp->link = NULL; // 링크 필드를 NULL로 설정
      if(is_empty(q)){   // 큐가 공백이면
        q->front = temp;
        q->rear = temp;
      }
      else {
        q->rear->link = temp; // 큐가 공백이 아니면
        q->rear = temp; // 순서가 중요.
      }
  }
}
element dequeue(QueueType *q)
{
  QueueNode *temp = q->front; //FIFO 방식으로 인해 front가 나온다.
  element item;
  if(is_empty(q)) // 공백상태
    error("NOT HERE!\n");
  else { 
    item = temp->item; // 데이터를 꺼낸다.
    q->front = q->front->link; // front를 다음 노드를 가리키도록 한다.
    if(q->front == NULL) // 공백 상태
      q->rear = NULL;
    free(temp); // 노드 메모리 해제
    return item; // 데이터 반환
  }
}
element peek(QueueType *q)
{
  if(is_empty(q))
    error("queue is NOT\n");
  else {
    return q->front->item;
  }
}
//test funtion
int main()
{
  QueueType q;
  init(&q);
  enqueue(&q, 1);
  enqueue(&q, 2);
  enqueue(&q, 3);
  printf("%d\n",dequeue(&q));
  printf("%d\n",dequeue(&q));
  printf("%d\n",dequeue(&q));
  printf("%d\n",dequeue(&q));
}