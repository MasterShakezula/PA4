#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 101
struct node {
  char *key;
  struct node *next;
};
typedef struct node node;
typedef struct{
	node**table;
	int size;
	int capacity;
}hash_table;
void hash_init(hash_table* h, int init_capacity){
	h->capacity = init_capacity;
	h->table = (node**) malloc(init_capacity * sizeof(node*));
	h->size = 0;
	for(int i = 0; i < init_capacity;i++)
		h->table[i] = NULL;
	for(int i = 0; i < init_capacity;i++)
		h->table[i] = NULL;
}
unsigned hash(hash_table h, char *key) {
  unsigned hashval = 0;
  for (int i = 0; i < strlen(key); i++)
    hashval = key[i] + 31 * hashval;
  return hashval % h.capacity;
}
int hash_search(hash_table h,char *target) {
  node *head = h.table[hash(h, target)];
  for (; head; head = head->next)
    if (!strcmp(head->key, target))
      return 1;
  return 0; // unsuccessful
}
int hash_add(hash_table* h, char *value) {
  unsigned index = hash(*h, value);
  node *head = h->table[index];
  if (!head) {
    h->table[index] = (node *)malloc(sizeof(node));
    h->table[index]->next = NULL;
    h->table[index]->key = strdup(value);
  } else {
    node *prev = head;
    for (; head; prev = head, head = head->next)
      if (!strcmp(head->key, value))
        return 0;
    prev->next = (node *)malloc(sizeof(node));
    prev->next->next = NULL;
    prev->next->key = strdup(value);
  }
  h->size++;
  if(h->size >= 2 * h->capacity)//load factor will exceed 2 in the next add operation!
	;//rehash(h);
  return 1; // successful
}
int hash_remove(hash_table* h, char *value) {
  unsigned index = hash(*h, value);
  node *head = h->table[index];
  if (!head)
    return 0; // doesn't exist! unsuccessful
  else if(!strcmp(head->key, value)){
    h->table[index] = head->next;
    free(head);
  } else{
    node *prev = head;
    for (head = head->next; head; prev = head, head = head->next)
      if (!strcmp(head->key, value))
        break;
    if (!head)
      return 0; // doesn't exist! unsuccessful
    prev->next = head->next;
    free(head);
  }
  h->size--;
  return 1; // successful
}
void print_all(hash_table h) {
  for (int i = 0; i < h.capacity; i++)
    for (node *temp = h.table[i]; temp; temp = temp->next)
      printf("%s\t", temp->key);
  printf("\n");
}

int main2(void) {
	hash_table h;
	hash_init(&h, 101);
  char *fruits[] = {"apple",  "banana",    "orange",    "banana", "kiwi",
                    "grapes", "srawberry", "blueberry", "orange"};
  for (int i = 0; i < 9; i++)
    printf("Adding %s was%s successful!\n", fruits[i],
           hash_add(&h, fruits[i]) ? "" : " not");
  char *temp = (char *)malloc(4);
  for (int i = 0; i < 900; i++) {
    sprintf(temp, "%d", i);
    hash_add(&h, temp);
  }
  for (int i = 0; i < 850; i++) {
    sprintf(temp, "%d", i);
    hash_remove(&h, temp);
  }
  print_all(h);
  return 0;
}