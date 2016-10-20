#ifndef _CYCLICLIST
#define _CUCLICLIST

typedef int elem;

typedef struct _node {
  elem info;
  struct _node *next;
} Node;

typedef struct _list {
  Node *head;
  int length;
} List;

#endif
