#include<stdio.h>
#include<stdlib.h>

#define MAX_ELEMENT 100
typedef struct TreeNode {
  int weight;
  struct TreeNode *left_child;
  struct TreeNode *right_child;
} TreeNode;
typedef struct {
  TreeNode *ptree;
  int key;
} element;
typedef struct {
  element heap[MAX_ELEMENT];
  int heap_size;
} HeapType;

void init(HeapType *h)
{
  h->heap_size = 0;
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
  int parent, child;
  element item, temp;

  item = h->heap[1];
  temp = h->heap[(h->heap_size)--];
  parent = 1;
  child = 2; // 초기 setting.
  while(child <= h->heap_size){
    // 현재 노드의 자식노드중 더 큰 자식 노드를 찾는다.
    if((child < h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
      child++;
    if(temp.key <= h->heap[child].key) break;
    h->heap[parent] = h->heap[child];
    parent = child;
    child *= 2; // 자리 위치 변환
  }
  h->heap[parent] = temp; // 자리 최종 선언
  return item;
}
TreeNode *make_tree(TreeNode *left, TreeNode *right)
{
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  if(node == NULL){
    fprintf(stderr,"ERROR!!\n");
    exit(1);
  }
  node->left_child = left;
  node->right_child = right;
  return node;
}
void distory_tree(TreeNode *root)
{
  if(root == NULL) return;
  distory_tree(root->left_child);
  distory_tree(root->right_child);
  free(root);
}
void huffman_tree(int freq[], int n)
{
  int i;
  TreeNode *node, *x;
  HeapType heap;
  element e,e1,e2;

  init(&heap);
  for(i=0; i<n; i++){
    node = make_tree(NULL,NULL);
    e.key = node->weight = freq[i];
    e.ptree = node;
    insert_min_heap(&heap,e);
  }
  for(i=1;i<n;i++){
    e1 = delete_min_heap(&heap);
    e2 = delete_min_heap(&heap);
    x = make_tree(e1.ptree, e2.ptree);
    e.key = x->weight = e1.key + e2.key;
    e.ptree = x;
    insert_min_heap(&heap, e);
  }
  e = delete_min_heap(&heap);
  distory_tree(e.ptree);
}
void main()
{
  int freq[] = {15, 12, 8, 6, 4};
  huffman_tree(freq, 5);
}
