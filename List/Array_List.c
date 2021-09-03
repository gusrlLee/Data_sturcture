/*배열 리스트는 크기가 고정된 배열로 그 크기만큼 만들어진 상자들의 
집합과 같다. 하지만 배열의 크기보다 적은 데이터를 저장하게 된다면 
저장공간을 낭비하게 된다. 또 삽입과 삭제 시에 상당한 오버헤드가 발생한다.
이것이 배열리스트의 단점이지만 연결리스트에 비해 구현하기가 쉽고 효율적
이기 때문에 아직도 사용되고 있는 중이다.*/

#include<stdio.h>
#include<stdlib.h>

#define MAX_LIST_SIZE 100 // 배열 최대 사이즈 선언

typedef int element;
typedef struct {//구조체 선언
  element list[MAX_LIST_SIZE];
  int length;
}ArrayListType;

//오류 처리 함수
void error(char *message)
{
  fprintf(stderr,"%s\n",message);
  exit(1);
}
//리스트 초기화 함수
void init(ArrayListType *L)
{
  L->length = 0;
}
//리스트가 비어 있으면 1을 반환 그렇지 않으면 0을 반환
int is_empty(ArrayListType *L)
{
  return L->length == 0;
}
//리스트가 가득 차 있으면 1을 반환 그렇지 않으면 0을 반환
int is_full(ArrayListType *L)
{
  return L->length == MAX_LIST_SIZE;
}
//List printf()
void display(ArrayListType *L)
{
  for(int i=0; i<L->length; i++)
    printf("%d\n",L->list[i]);
}
//insert function
void add(ArrayListType *L, int position, element item)
{
  if(!is_full(L) && (position>=0) && (position<=L->length)){
    for(int i=L->length-1; i>=position; i--)
      L->list[i+1] = L->list[i];
    L->list[position] = item;
    L->length++;
  }
}
//delete function
element delete(ArrayListType *L, int position)
{
  element item;
  if(position<0 || position>=L->length)//조건에 안맞는 입력이면 에러출력
    error("ERROR!\n");
  item = L->list[position]; //값의 손실을 막기 위해 임시 저장
  for(int i=position; i<=L->length-1; i++)
    L->list[i] = L->list[i+1];
  L->length--;
  return item; //삭제
}
//clear List function
void clear(ArrayListType *L)
{
  if(is_empty(L)) error("already empty!\n");
  else{
    for(int i=0; i<L->length; i++)
      L->list[i] = 0;
    L->length = 0;
  }
  printf("clear!\n");
}
//replace A to B function
int replace(ArrayListType *L, int position, int item)
{ 
  int temp;
  if(position<0 || position>=L->length)//조건에 안맞는 입력이면 에러출력
    error("ERROR!\n");
  temp = L->list[position];
  L->list[position] = item;
  return temp;
}
//get array position value function
int get_entry(ArrayListType *L, int position)
{
  return L->list[position];
}
//get array_length function
int get_length(ArrayListType *L)
{
  return L->length;
}
//ADT test program
int main(void)
{
  ArrayListType list1;
  ArrayListType *plist;

  printf("Display list1!\n");
  init(&list1);
  add(&list1, 0, 10);
  add(&list1, 0, 20);
  add(&list1, 0, 30);
  printf("%d %d\n", get_entry(&list1, 2), get_length(&list1));
  display(&list1);
  replace(&list1, 1, 40);
  display(&list1);
  clear(&list1);
  display(&list1);

  printf("Display plist!\n");
  plist = (ArrayListType *)malloc(sizeof(ArrayListType));
  init(plist);
  add(plist, 0, 10);
  add(plist, 0, 30);
  add(plist, 0, 20);
  
  display(plist);
  free(plist);
}



