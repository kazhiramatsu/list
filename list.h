#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

typedef struct list_s list_t;

struct list_s {
  struct list_s *prev;
  struct list_s *next;
};

#define container_of(ptr, type, member) ({                  \
  const __typeof__( ((type *)0)->member ) *__mptr = (ptr);  \
  (type *)( (char *)__mptr - offsetof(type,member) );})

#define list_each(list, iter) \
  for (iter = (list)->next; (iter != list); iter = iter->next)

static
inline
void
list_init(list_t *list)
{
  list->next = list;
  list->prev = list;
}

static
inline
void
do_list_add(list_t *prev, list_t *next, list_t *new)
{
  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;
}

static
inline
void
list_add(list_t *head, list_t *new)
{
  do_list_add(head->prev, head, new);
}

static
inline
void
do_list_delete(list_t *prev, list_t *next)
{
  next->prev = prev;
  prev->next = next;
}

static
inline
void
list_delete(list_t *list)
{
  do_list_delete(list->prev, list->next);
  list->next = NULL;
  list->prev = NULL;
}

#endif
