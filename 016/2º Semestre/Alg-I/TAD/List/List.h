#ifndef LIST_H
#define LIST_H

typedef struct _operations {
  int (*setInvalidValue)(void *elem);
  int (*isInvalidValue)(void *elem);
  int (*copy)(void *src, void **dest);
  int (*destroyElement)(void *elem);
} Operations;

typedef struct _node {
  void *info;
  struct _node *next;
} Node;

typedef struct _list {
  Node *header, *last;
  unsigned int numOfElem;
  Operations *opts; // operações
} List;

#endif
