#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 100
typedef struct {
  int id;
  int arrival_time;
  int service_time;
} element;
typedef struct {
  element queue[MAX_QUEUE_SIZE];
  int front, rear;
} QueueType;
QueueType queue;

void error(char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(1);
}
//init function
void init(QueueType *q)
{
  q->front = q->rear = 0;
}
//is_empty function
int is_empty(QueueType *q)
{
  return (q->front == q->rear);
}
//full function
int is_full(QueueType *q)
{
  return ((q->rear+1) % MAX_QUEUE_SIZE == q->front);
}
//add func
void enqueue(QueueType *q, element item)
{
  if(is_full(q)) error("FULL! CANNOT!\n");
  else{
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
  }
}
element dequeue(QueueType *q)
{
  element temp;
  if(is_empty(q)) error("CANNOT!\n");
  else{
    temp = q->queue[q->front];
  }
}
element peek(QueueType *q)
{
  if(is_empty(q)) error("CANNOT!\n");
  else {
    return q->queue[(q->front+1) % MAX_QUEUE_SIZE];
  }
}
double random()
{
  return rand()/(double)RAND_MAX;
}
//변수 선언
int duration = 10; // 시물레이션 시간
double arrival_prob = 0.7; //하나의 시간 단위에 도착하는 평균 고객 수
int max_serv_time = 5; //하나의 고객에 대한 최대 서비스 시간
int clock;

//시뮬레이션 결과
int customers; // 전체 고객수
int served_customers; // 서비스 받은 고객 수
int waited_time; // 고객들이 기다린 시간
// 랜덤 숫자를 생성하여 
// 고객이 도착했는지 도착하지 않았는지를 판단
int is_customer_arrived()
{
  if(random() <arrival_prob)
    return TRUE;
  else return FALSE;
}
// 새로 도착한 고객을 큐에 삽입
void insert_customer(int arrival_time)
{
  element customer;

  customer.id = customers++;
  customer.arrival_time = arrival_time;
  customer.service_time = (int)(max_serv_time*random()) + 1;
  enqueue(&queue, customer);
  printf("customer_num: %d arrived: %d service_time: %d\n",
    customer.id, customer.arrival_time, customer.service_time);
}
//큐에서 기다리는 고객을 꺼내어 고객의 서비스 시간을 반환한다.
int remove_customer()
{
  element customer;
  int service_time = 0;

  if(is_empty(&queue)) return 0;
  customer = dequeue(&queue);
  service_time = customer.service_time-1;
  served_customers++;
  waited_time += clock - customer.arrival_time;
  printf("customer_name: %d service_start: %d wait_time: %d\n", 
    customer.id, clock, clock-customer.arrival_time);
  return service_time;
}
//printf
void print_start()
{
  printf("finished_customers_num: %d\n",served_customers);
  printf("all_wait_time: %d\n", waited_time);
  printf("wait_time of 1: %d\n", (double)waited_time / served_customers);
  printf("not_finished_customers_num: %d\n", customers-served_customers);
}
void main()
{
  int service_time =0;
  clock = 0;

  while(clock < duration){
    clock++;
    printf("now time: %d\n", clock);
    if(is_customer_arrived()){
      insert_customer(clock);
    }
    if(service_time>0)
      service_time--;
    else{
      service_time = remove_customer();
    }
  }
  print_start();
}
