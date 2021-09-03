// 퀵 정렬
// 평균적으로 매우 빠른 수행 속도를 자랑하고 분할정복 방법에 근거한다.
// 합병정렬과 비슷하게 전체 리스트를 2개의 부분 리스트로 분할하고,
// 각각의 부분 리스트를 다시 퀵정렬 하는 전형적인 분할 정복 방법을 사용
// 시간 복잡도 == O(n*log2(n))
#include<stdio.h>
#include<stdlib.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t)) // 교환 매크로
#define MAX_SIZE 100
int list[MAX_SIZE];
int n;

int partition(int list[], int left, int right)
{
  int pivot, temp;
  int low, high; // 변수 설정

  low = left;
  high = right+1;
  pivot = list[left]; // 초기 값 설정
 
  do{
    do{
      low++;
    }while(low <= right && list[low]<pivot); // pivot과 비교 
    do{
      high--;
    }while(high >= left && list[high]>pivot); // pivot과 비교 
    if(low<high) SWAP(list[low], list[high], temp); // 교환.
  }while(low<high);

  SWAP(list[left], list[high], temp);
  return high;
}
void quick_sort(int list[], int left, int right)
{
  if(left<right){
    int q=partition(list,left,right);
    quick_sort(list, left, q-1);
    quick_sort(list, q+1, right);
  }
}
int main()
{
  n=MAX_SIZE;
  for(int i=0; i<n; i++)
    list[i] = rand() % n;
  quick_sort(list, 0, MAX_SIZE-1);
  for(int i=0; i<n; i++) printf("%d\n", list[i]);
  return 0;
}