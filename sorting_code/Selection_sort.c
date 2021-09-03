// 선택 정렬: 배열에서 최소값을 발견한 다음,
// 그 값을 첫 번째 값과 교환한다.
// 다음 첫 번째 요소를 제외한 나머지 요소들 중에서 가장 작은 값을 선택
// 그 값을 두번째 요소와 교환, 이 절차를 반복
// 시간 복잡도 = O(n^2)
#include<stdio.h>
#include<stdlib.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t)) // 교환 매크로
#define MAX_SIZE 10000
int list[MAX_SIZE];
int n;

void selection_sort(int list[], int n)
{
  int least, temp;
  for(int i=0; i<n-1; i++){
    least = i;
    for(int j=i+1; j<n; j++)
      if(list[j] < list[least]) least = j;
    SWAP(list[i], list[least], temp);
    
  }
}
int main()
{
  n=MAX_SIZE;
  for(int i=0; i<n; i++)
    list[i] = rand() % n;
  selection_sort(list, n);
  for(int i=0; i<n; i++) printf("%d\n", list[i]);
  return 0;
}