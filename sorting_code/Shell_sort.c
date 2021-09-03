// 쉘 정렬
// list를 일정한 기준에 따라 분류하여 연속적이지 않은 여러개의 부분 list로 만들고
// 각 부분 리스트를 삽입 정렬을 이용해 정렬.
// 시간 복잡도 == O(n^1.5) (삽입, 합병, 버블정렬보다 효율이 좋음)
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
int list[MAX_SIZE];
int n;
void inc_insertion_sort(int list[], int first, int last, int gap)
{
  int i,j,key; // 삽입 정렬.
  for(i=first+gap; i<=last; i+=gap){
    key=list[i];
    for(j=i-gap; j>=first && key<list[j]; j=j-gap) list[j+gap] = list[j];
    list[j+gap] = key;
  }
}
void shell_sort(int list[], int n)
{
  int i, gap;
  for(gap=n/2; gap>0; gap=gap/2){
    if((gap%2) == 0) gap++; // gap setting
    for(i=0; i<gap; i++)
      inc_insertion_sort(list, i, n-1, gap); // 주어진 간격으로 각 list들을 정렬 해준다.
  }
}
int main()
{
  n=MAX_SIZE;
  for(int i=0; i<n; i++)
    list[i] = rand() % n;
  shell_sort(list, n);
  for(int i=0; i<n; i++) printf("%d\n", list[i]);
  return 0;
}
