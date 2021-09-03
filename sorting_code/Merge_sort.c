// 합병 정렬
// 하나의 리스트를 두 개의 균등한 크기로 분할하고 분할된 부분 리스트를 
// 정렬한 다음, 두 개의 정렬된 부분 리스트를 합하여 전체가 정렬된 리스트가 되게 
// 하는 방법이다.
// 시간 복잡도 == O(n*log2(n))
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
int list[MAX_SIZE];
int sorted[MAX_SIZE]; // 정렬된 배열을 저장하기 위해서 추가적인 배열 선언
int n;
void merge(int list[], int left, int mid, int right)
{
  int i,j,k,l;
  i=left; j=mid+1; k=left;
  // 분할 정렬된 list의 합병 
  while(i<=mid && j<=right){
    if(list[i]<=list[j])
      sorted[k++] = list[i++];
    else 
      sorted[k++] = list[j++];
  }
  if(i>mid) // 남아있는 값들을 일괄 복사
    for(l=j; l<=right; l++)
      sorted[k++] = list[l];
  else 
    for(l=i; l<=mid; l++)
      sorted[k++] = list[l];
  for(l=left; l<=right; l++) // 배열 sorted의 리스트를 배열list로 재복사.
    list[l] = sorted[l];   
}
void merge_sort(int list[], int left, int right)
{
  int mid;
  if(left<right){
    mid = (left+right)/2; // 게속해서 리스트를 분할 해준다.
    merge_sort(list, left, mid); 
    merge_sort(list, mid+1, right); // 분할 해줌
    merge(list, left, mid, right); // 마지막 정렬된 리스트 합병.
  }
}
int main()
{
  n=MAX_SIZE;
  for(int i=0; i<n; i++)
    list[i] = rand() % n;
  merge_sort(list, 0, MAX_SIZE-1);
  for(int i=0; i<n; i++) printf("%d\n", list[i]);
  return 0;
}