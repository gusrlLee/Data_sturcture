#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0 

#define ARRIVAL 1
#define ORDER 2
#define LEAVE 3
// 상태선언 변수 설정.
int free_seats=10;
double profit=0.0;

#define MAX_ELEMENT 100
typedef struct {
  int type; // kind of event.
  int key; // time 
  int number; //customer.
} element;
typedef struct {
  element heap[MAX_ELEMENT];
  int heap_size;
} HeapType; // heap tree setting

void init(HeapType *h)
{
  h->heap_size = 0;
}
// tree가 비었는 지 확인하는 함수
int is_empty(HeapType *h)
{
  if(h->heap_size == 0)
    return TRUE; // 비었으면 1을 return
  else return FALSE; // 아니면 0을 return 
}
//insert function
void insert_min_heap(HeapType *h, element item)
{
  int i;
  i = ++(h->heap_size); // heap_size 증가

  // 트리를 거슬러 올라가면서 부모 노드와 비교
  while((i != 1) && (item.key < h->heap[i/2].key)){
    h->heap[i] = h->heap[i/2];
    i /= 2;
    //int 형식이기 때문에 /2만 해주어도 됨.
  }
  h->heap[i] = item; // 대입
}
//delete_function
element delete_min_heap(HeapType *h)
{
  int parent, child; // 부모 노드와 자식 노드 설정
  element item, temp; // 구조체 설정

  item = h->heap[1];
  temp = h->heap[(h->heap_size)--];
  parent = 1;
  child = 2; // 초기 setting.
  while(child <= h->heap_size){
    // 현재 노드의 자식노드중 더 작은 자식 노드를 찾는다.
    if((child < h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
      child++;
    if(temp.key <= h->heap[child].key) break; // 찾으면 반복문을 멈춘다.
    h->heap[parent] = h->heap[child]; // 못찾는 다면 부모노드와 자식노드를 
    parent = child; // 다시 setting
    child *= 2; // 자리 위치 변환
  }
  h->heap[parent] = temp; // 자리 최종 선언
  return item; // return 
}
int random(int n)
{
  return (int)(n*rand()/(double)RAND_MAX);
} // 난수 설정
int is_seat_available(int number)
{
  printf("%d. arrived customer!\n", number);
  if(free_seats >= number){
    free_seats -= number;
    return TRUE;
  }
  else {
    printf("customer is gone\n");
    return FALSE;
  }
}
void order(int scoops) // 주문을 받으면 순익을 나타내는 변수를 증가
{
  printf("Ice cream's oreder: %d\n", scoops);
  profit += 0.35 * scoops;
}
void leave(int number) // 고객이 떠나면 빈자리 수를 증가. 
{
  printf("leaved human: %d\n", number);
  free_seats += number;
}
void process_event(HeapType *heap, element e)
{ // 이벤트를 처리한다.
  int i=0;
  element new_event;

  printf("now time: = %d\n", e.key);
  switch(e.type){ 
    case ARRIVAL: // 자리가 가능하면 주문 이벤트를 만든다.
      if(is_seat_available(e.number)){
        new_event.type = ORDER;
        new_event.key = e.key + 1 + random(4);
        new_event.number=e.number;
        insert_min_heap(heap, new_event);
      }
      break;
    case ORDER: // 사람 수만큼 주문을 받는다.
      for(i=0; i<e.number; i++){
        order(1+random(3));
      }
      new_event.type=LEAVE; // 주문이 완료 되었으므로 매장을 떠나는 이벤트 설정
      new_event.key = e.key + 1 + random(10);
      new_event.number=e.number;
      insert_min_heap(heap, new_event);
      break;
    case LEAVE: // 고객이 떠나면 매장을 떠나게 설정
      leave(e.number);
      break;
  }
}
int main()
{
  element event;
  HeapType heap;
  unsigned int t = 0;
  init(&heap);
  while(t<5) {
    t+=random(6);
    event.type = ARRIVAL;
    event.key = t;
    event.number = 1+random(4);
    insert_min_heap(&heap,event);
  }
  while(!is_empty(&heap)){
    event = delete_min_heap(&heap);
    process_event(&heap, event);
  }
  printf("%d!!\n",profit);
}
