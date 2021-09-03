// 삽입 정렬
// 정렬되어 있는 리스트에 새로운 레코드를 올바른 위치로 삽입 하는 과정 반복
// 정렬된 리스트와 정렬되지 않은 리스트로 나누어 사용
// 시간 복잡도 == O(n^2)
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
int list[MAX_SIZE];
int n;
void insertion_sort(int list[], int n)
{
  int key, i ,j;
  for(i=1; i<n; i++){
    key = list[i]; // 그 list값을 저장
    for(j=i-1; j>=0 && list[j]>key; j--) list[j+1] = list[j];
    // 반복하면서 그 key의 값보다 작은 값을 탐색
    list[j+1] = key; // 그 자리에 key값을 대입.
  }
}
int main()
{
  n=MAX_SIZE;
  for(int i=0; i<n; i++)
    list[i] = rand() % n;
  insertion_sort(list, n);
  for(int i=0; i<n; i++) printf("%d\n", list[i]);
  return 0;
}
