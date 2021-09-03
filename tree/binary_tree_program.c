// 단어 사전 프로그램 
// 자료구조 -> 트리 응용
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#define MAX_WARD_SIZE 100
#define MAX_MENING_SIZE 200

// data field
typedef struct {
  char word[MAX_WARD_SIZE];
  char meaning[MAX_MENING_SIZE];
} element;
// node stracture
typedef struct TreeNode{
  element key;
  struct TreeNode *left, *right;
} TreeNode;

// e1<e2 = return -1
// e1==e2 = return 0
// e1>e2 = return 1
int compare(element e1, element e2)
{
  return strcmp(e1.word, e2.word);
  // 문자를 비교해서 tree에 있는 여부를 확인
}
// print function
void display(TreeNode *p)
{ // 출력
  if(p != NULL){
    printf("(");
    display(p->left);
    printf("%s", p->key.word);
    display(p->right);
    printf(")");
  }
}
// binary tree search 
TreeNode *search(TreeNode *root, element key)
{ // 알파벳 순서로 비교를 해서 방향을 지정함
  TreeNode *p = root;
  while(p != NULL){
    // char 배열 형식의 문자열을 비교 할때는 strcmp
    // string 형식의 문자열을 비교 할때는 compare
    switch(compare(key, p->key)){
      case -1:
        p=p->left;
        break; // 
      case 0:
        return p;
      case 1:
        p=p->right;
        break;
    }
  }
  return p; // if it fails to searching, return NULL
}
// insert key into binary search tree root
// if key in root, do not insert key 
void insert_node(TreeNode **root, element key)
{
  TreeNode *p, *t; // p- parents_Node t- child_Node
  TreeNode *n; // n- NEW_NODE

  t = *root;
  p = NULL;
  // first, searching
  while(t != NULL){
    if(compare(key, t->key) == 0) return;
    p = t;
    if(compare(key, t->key)<0) t = t->left;
    else t=t->right; 
  }
  // can insert item because not in tree
  n = (TreeNode *)malloc(sizeof(TreeNode));
  if(n == NULL) return;
  // copy data
  n->key = key;
  n->left = n->right = NULL;
  // connect parents_node link
  if(p != NULL)
    if(compare(key, p->key)<0) p->left = n;
    else p->right = n;
  else *root = n;
}
// delete function
void delete_node(TreeNode **root, element key)
{
  TreeNode *p, *child, *succ, *succ_p, *t;
  //searching node having the key
  //p is parents of t
  p = NULL;
  t = *root;
  while(t != NULL && compare(t->key, key) != 0){
    //노드 탐색을 먼저 한다.
    p = t;
    t = (compare(key, t->key)<0)? t->left : t->right;
  }
  if(t == NULL){
    //삭제하려는 노드가 없으면 존재하지 않다고 출력
    printf("key is not in the Tree\n");
    return ;
  }
  // if node is Terminal Node,
  if((t->left == NULL) && (t->right == NULL)){
    if(p != NULL){
      // 트리가 비어있지 않다면 
      if(p->left == t) // 부모노드의 왼쪽에 존재 하면 
        p->left = NULL; //link를 끊음
      else p->right = NULL; // 오른쪽에 있으면 오른쪽 link를 끊음
    }
    else *root = NULL; // 트리에 노드가 한개만 있다면 트리를 비움
  }
  // if node is node having one child
  else if((t->left == NULL) || (t->right == NULL)){
    child = (t->left != NULL) ? t->left : t->right;
    // 삭제 하려는 노드의 자식 위치 파악
    if(p != NULL){
      if(p->left == t) // parents_node connects child_node
        p->left = child; // 삭제하려는 노드의 부모와 그 노드의 자식 노드를 연결
      else p->right = child; // 위와 동일
    }
    else *root = child;
  }
  // if node is node having two child
  else {
    // find sequel_node in right sub_tree
    succ_p = t;
    succ = t->right; // 트리 탐색
    // moving left for finding sequel_node
    while(succ->left != NULL){
      succ_p = succ;
      succ = succ->left; // 트리 탐색
    }
    // sequel_node's parents connect child
    if(succ_p->left == succ)
      succ_p = succ->right; //
    else succ_p->right = succ->right;
    // sequel move now_node
    t->key = succ->key;
    t = succ;
  }
  free(t);
}
// help
void help()
{
  printf("****************\n");
  printf("i: insert\n");
  printf("d: delete\n");
  printf("s: search\n");
  printf("p: print\n");
  printf("q: quit\n");
  printf("****************\n");
}
//test program
int main()
{
  char command;
  element e;
  TreeNode *root = NULL;
  TreeNode *tmp;
  do{
    help();
    command = getchar();
    fflush(stdin);
    switch(command){
      case 'i':
        printf("word:");
        gets(e.word);
        printf("meaning:");
        gets(e.meaning);
        insert_node(&root, e);
        break;
      case 'd':
        printf("word:");
        gets(e.word);
        delete_node(&root, e);
        break;
      case 'p':
        display(root);
        printf("\n");
        break;
      case 's':
        printf("word:");
        gets(e.word);
        tmp = search(root, e);
        if(tmp = NULL)
          printf("meaning:%s\n", e.meaning);
        break;
    }    
  }while(command != 'q');
}