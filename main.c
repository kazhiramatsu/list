
#include "list.h"

struct users {
  char *name;
  list_t list;
};

struct users *
user_new(char *name)
{
  struct users *user = malloc(sizeof(struct users));
  user->name = name;
  list_init(&user->list);
  return user;
}

int
main(int argc, char **argv)
{
  list_t head;

  list_init(&head);

  struct users *user = user_new("a");
  struct users *user2 = user_new("b");
  list_add(&head, &user->list);
  list_add(&head, &user2->list);

  list_t *l;
  list_each(&head, l) {
    printf("%s\n", container_of(l, struct users, list)->name);
  }
  return 0;
}
