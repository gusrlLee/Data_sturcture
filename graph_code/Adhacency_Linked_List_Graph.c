// 인접 리스트로 표현된 그래프에 대한 너비 우선 탐색 전체 프로그램
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0
#define element int

// QUEUE_SETTING
typedef struct QueueNode {
  element data;
  struct QueueNode *link;
} QueueNode; // Linked_List 구현 
typedef struct QueueType {
  QueueNode *front, *rear;
} QueueType; // Link 설정
//Graph_SETTING
typedef struct GraphNode{
  int vertex;
  struct GraphNode *link;
} GraphNode; // 링크 그래프 셋팅
typedef struct GraphType{
  int n;
  GraphNode *adj_list[MAX_VERTICES];
} GraphType; // 그래프 이어주는 셋팅
int visited[MAX_VERTICES];
int count=0;
// Queue_function=============================================================================
void error(char *message) // 에러 출력. 
{
  fprintf(stderr,"%s\n", message);
  exit(1);
}
void init(QueueType *q) // 큐 셋팅 초기화 
{
  q->front = q->rear = NULL; // front와 rear에 NULL을 삽입 시키므로 초기화.
}
int is_empty(QueueType *q) // 공백 상태 검출 함수
{
  return (q->front == NULL); 
  // front 가 가리키는 것이 없다면 
  // 공백 상태를 return 
}
void enqueue(QueueType *q, element item) 
{
  QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode)); // 새로운 node 동적 할당
  if(new_node == NULL) error("CANNOT MAKE NODE!!\n"); 
  // 생성에 실패 한다면 error출력
  else{
    new_node->data = item; // 노드에 data삽입
    new_node->link = NULL; // New_node의 링크에 NULL을 삽입
    if(is_empty(q)) { // 큐가 비어있다면 
      q->front = new_node; 
      q->rear = new_node; 
      // front, rear이 new_node를 가리키게 해서 큐의 첫번째 데이터로 삽입
    }
    else{ // 그렇지 않다면 
      q->rear->link = new_node; // rear가 가리키는 노드의 link에 new_node를 삽입 
      q->rear = new_node; // rear 재설정
    }  
  }
}
element dequeue(QueueType *q)
{
  QueueNode *temp = q->front; // front의 노드 설정
  int item; // return 해줄 데이터 공간 설정
  if(is_empty(q)) error("EMPTY QUEUE"); // 큐가 비어있으면
  // dequeue할 데이터가 없으므로 error출력
  else {
    item = temp->data; // data 임시 저장 
    q->front = q->front->link; // front의 링크를 다음 node로 설정
    if(q->front == NULL) // 만약 마지막 데이터 였다면 
      q->rear = NULL; // queue를 비게 설정
    free(temp); // 데이터 공간 반환
    return item; // 반환. 
  }
}
element peek(QueueType *q)
{
  if(is_empty(q)) error("QUEUE NOTHING!\n"); // queue가 비어있다면 error출력
  else return q->front->data; // front가 가리키는 데이터를 return 한다. 
}
// Graph_function=============================================================================
void graph_init(GraphType *g)
{
  int v; // v 설정
  g->n = 0; // 그래프의 정접 초기화.
  for(v=0; v<MAX_VERTICES; v++){
    g->adj_list[v] = NULL; // List들을 NULL을 대입해 초기화 한다.
  }
}
void insert_vertex(GraphType *g, int v)
{
  if(((g->n)+1) > MAX_VERTICES){ // +1을 대입을 했을 때 정해진 정점 개수를 초과 하면 
  // error출력
    fprintf(stderr, "SIZE_OVERFLOW!\n");
    return;
  }
  g->n++;
}
// 간선 삽입.
void insert_edge(GraphType *g, int u, int v)
{ 
  GraphNode *node; // 그래프 노드의 선언
  if(u >= g->n || v >= g->n){
    fprintf(stderr, "SIZE_OVERFLOW!\n");
    return;    
  } // 그래프의 정점개수를 넘어가면 에러 출력 
  node = (GraphNode *)malloc(sizeof(GraphNode)); // 데이터 동적 할당.
  node->vertex = v; // 노드의 정점에다가 대입
  node->link = g->adj_list[u]; // node의 link에 그래프 리스트를 대입 
  g->adj_list[u] = node; // 리스트에 노드를 대입 시킴으로 연결.
}
// 인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_list(GraphType *g, int v) 
{
  GraphNode *w; // 노드 설정
  visited[v] = count; // 정점 v의 방문 표시 
  printf("%d ", v); // 정점 v의 방문 출력
  for(w=g->adj_list[v]; w; w=w->link) // 인접 정점 탐색 
    if(!visited[w->vertex])
      dfs_list(g,w); // 정점 w->vertex 에서 DFS에서 새로 시작.
}
void bfs_list(GraphType *g, int v)
{
  GraphNode *w; // 그래프노드 포인터 설정
  QueueType q; // 큐 선언
  init(&q); // 큐 초기화 
  visited[v] = TRUE; // 들어온 정점을 방문 상태 변경
  printf("%d ", v); // 방문한 정점 출력
  enqueue(&q, v); // 그 정점을 큐에 대입.
    while(!is_empty(&q)){ // 큐가 비어질때 까지
    v = dequeue(&q); // 큐에서 정점 추출
    for(w=g->adj_list[v]; w; w=w->link){ // 인접 정접 탐색
      if(!visited[w->vertex]){ 
        visited[w->vertex] = TRUE; // 방문 표시 
        printf("%d ",w->vertex); // 정점 출력
        enqueue(&q, w->vertex); // 방문한 정점을 큐에 저장
      }
    }
  }
}
void find_connected_component(GraphType *g)
{
  int i;
  for(i=0; i<g->n; i++){
    if(!visited[i]){ // 방문되지 않았으면 
      count++;
      dfs_list(g, i);
    }
  }
}
//test_program. 
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

  bfs_list(&g, 0);
  printf("\n");
  dfs_list(&g, 0);
}

