//원형 큐 구현
#include<stdio.h>
#include<stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
  element queue[MAX_QUEUE_SIZE];
  int rear,front;
} QueueType;
//에러 출력 
void error(char *message)
{
  fprintf(stderr, "%s", message);
  exit(1);
}
//init function
void init(QueueType *q)
{
  //front와 rear을 같게 만들어 큐에 아무것도 존재하지 않게 표현
  q->front = q->rear = 0;
}
//empty function
int is_empty(QueueType *q)
{
  return (q->front == q->rear);
}
//full function
int is_full(QueueType *q)
{
  return ((q->rear+1) % MAX_QUEUE_SIZE == q->front);
}
//insert function
void enqueue(QueueType *q, element item)
{
    if( is_full(q) ) error("FULL!\n");
  q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
  q->queue[q->rear] = item;
}
element dequeue(QueueType *q)
{
    if(is_empty(q)) error("CANNOT!!\n");
  q->front = (q->front+1) % MAX_QUEUE_SIZE;
  return q->queue[q->front];
}
element peek(QueueType *q)
{
  if(is_empty(q)) error("CANNOT PEEK!!\n");
  return q->queue[(q->front+1) % MAX_QUEUE_SIZE];
}
//test program
void main()
{
  QueueType q;
  init(&q);
  printf("front = %d rear = %d\n",q.front, q.rear);
  enqueue(&q, 1);
  enqueue(&q, 2);
  enqueue(&q, 3);
  printf("dequeue() = %d\n", dequeue(&q));
  printf("dequeue() = %d\n", dequeue(&q));
  printf("dequeue() = %d\n", dequeue(&q));
  printf("front = %d rear = %d\n",q.front, q.rear);
}