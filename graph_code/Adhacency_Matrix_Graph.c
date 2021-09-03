// 인접 행렬로 표현된 그래프에 대한 너비, 깊이 우선 탐색 프로그램 
// 깊이 우선 탐색의 개념, 너비 우선 탐색 공부가 더필요.
#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 100
#define TRUE 1
#define FALSE 0
// QUEUE SETTING
typedef struct QueueType {
  int queue[MAX_QUEUE_SIZE];
  int front, rear;
} QueueType; // 원형 큐로 설정. 

// GRAPH SETTING
typedef struct GraphType{
  int n;
  int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;
int visited[MAX_VERTICES]={0};
int count=0;
// 배열 큐 함수들 -------------------------------------------------------------------------
void error(char *message) // 에러 출력
{
  fprintf(stderr,"%s\n", message);
  exit(1);
}
void init(QueueType *q) // 큐 초기화
{
  q->front = q->rear = 0;
}
int is_empty(QueueType *q) // 큐의 상태 확인
{
  return (q->front == q->rear);
}
int is_full(QueueType *q) // 큐의 상태 확인
{
  return (q->front == (q->rear+1)%MAX_QUEUE_SIZE);
}
void enqueue(QueueType *q, int item) // 큐에 데이터 삽입
{
  if(is_full(q)) error("FULL QUEUE!!\n");
  q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
  q->queue[q->rear] = item;
}
int dequeue(QueueType *q) // 큐에 데이터 추출
{
  if(is_empty(q)) error("QUEUE EMPTY!!\n");
  q->front = (q->front+1)%MAX_QUEUE_SIZE;
  return q->queue[q->front];
}
int peek(QueueType *q) // peek함수
{
  if(is_empty(q)) printf("NOTHING!\n");
  return q->queue[(q->front+1)%MAX_QUEUE_SIZE];
}
// 그래프 함수들 --------------------------------------------------------------------------
void graph_init(GraphType *g) // 그래프 초기화 
{
  int r,c;
  g->n = 0; // 정점을 0개로 초기화
  for(r=0; r<MAX_VERTICES; r++){
    for(c=0; c<MAX_VERTICES; c++){
      g->adj_mat[r][c] = 0; // 0으로 각 행렬 초기화
    }
  }
}
void insert_vertex(GraphType *g, int v) // 정점 삽입
{
  if(((g->n)+1) > MAX_VERTICES){ // 정해진 범위가 초과하면 error출력
    fprintf(stderr, "SIZE_OVERFLOW!\n");
    return;
  }
  g->n++; // 정점을 오름차순으로 생성.
}
void insert_edge(GraphType *g, int start, int end) // 간선 삽입
{
  if(start >= g->n || end >= g->n){ // 정해진 정점이 벗어나면 
    fprintf(stderr, "SIZE_OVERFLOW!\n"); // 에러출력
    return;    
  }
  g->adj_mat[start][end] = 1; // 간선 설정
  g->adj_mat[end][start] = 1; // 간선 설정
  // 무방향 그래프이기 때문에 양쪽 방향성으로 설정
}
//인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType *g, int v)
{ 
  int w;
  visited[v] = TRUE; // 정점 v의 방문 표시 
  printf("%d ",v); // 방문한 정점 출력
  for(w=0; w<g->n; w++){ // 인접 정접 탐색
    if(g->adj_mat[v][w] && !visited[w]){
      dfs_mat(g, w); // 정접 w에서 재귀함수를 호출해 DFS 새로 시작.
    }  
  }
}
// 인접 행렬로 표현된 그래프에 대한 너비 우선 탐색
void bfs_mat(GraphType *g, int v)
{
  int w;
  QueueType q; // 큐 설정
  init(&q); // 큐 초기화
  visited[v] = TRUE; // 정점 v에 방문 표시 
  printf("%d ", v); // 방문한 정점 출력 
  enqueue(&q, v); // 시작 정점을 큐에 저장
  while(!is_empty(&q)){ // 큐가 비어질때 까지
    v = dequeue(&q); // 큐에서 정점 추출
    for(w=0; w<g->n; w++){ // 인접 정접 탐색
      if(g->adj_mat[v][w] && !visited[w]){ 
        visited[w] = TRUE; // 방문 표시 
        printf("%d ",w); // 정점 출력
        enqueue(&q, w); // 방문한 정점을 큐에 저장
      }
    }
  }
}
void find_connected_component(GraphType *g)
{
  int i;
  count = 0;
  for(i=0; i<g->n; i++){
    if(!visited[i]){
      count++;
      dfs_mat(g, i);
    }
  }
}
int main()
{
  GraphType g;

  graph_init(&g);
  //인접 리스트 생성
  for(int i=0; i<4; i++)
    insert_vertex(&g, i); // 정점 생성
    
   insert_edge(&g, 0, 1); // 간선 설정
   insert_edge(&g, 1, 0);
   insert_edge(&g, 0, 3);
   insert_edge(&g, 3, 0);
   insert_edge(&g, 1, 2);
   insert_edge(&g, 2, 1);
   insert_edge(&g, 1, 3);
   insert_edge(&g, 3, 1);
   insert_edge(&g, 2, 3);
   insert_edge(&g, 3, 2);

  bfs_mat(&g, 0);
  printf("\n");
  find_connected_component(&g);
  for(int i=0; i<g.n; i++){
    printf("%d->", visited[i]);
  }
  printf("\n");
  dfs_mat(&g, 0);
}