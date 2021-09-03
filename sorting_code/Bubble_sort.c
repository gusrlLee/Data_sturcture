// 버블 정렬
// 인접한 2개의 레코드를 비교하여 크기가 순서대로 되어 있지 않으면 
// 서로 교환하는 비교-교환 과정을 반복하는 정렬
// 시간 복잡도 == O(n^2)
#include<stdio.h>
#include<stdlib.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t)) // 교환 매크로
#define MAX_SIZE 100
int list[MAX_SIZE];
int n;
void bubble_sort(int list[], int n)
{
  int temp, i ,j; // 변수 선언 
  for(i=n-1; i>0; i--){ // 반복 설정
    for(j=0; j<i; j++){
      if(list[j]>list[j+1]) SWAP(list[j], list[j+1], temp);
    }
  }
}
int main()
{
  n=MAX_SIZE;
  for(int i=0; i<n; i++)
    list[i] = rand() % n;
  bubble_sort(list, n);
  for(int i=0; i<n; i++) printf("%d\n", list[i]);
  return 0;
}
