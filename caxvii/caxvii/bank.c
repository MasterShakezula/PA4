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
node *hashtable[HASH_SIZE];
unsigned hash(char *key) {
  unsigned hashval = 0;
  for (int i = 0; i < strlen(key); i++)
    hashval = key[i] + 31 * hashval;
  return hashval % HASH_SIZE;
}
int hash_search(char *target) {
  node *head = hashtable[hash(target)];
  for (; head; head = head->next)
    if (!strcmp(head->key, target))
      return 1;
  return 0; // unsuccessful
}
int hash_add(char *value) {
  unsigned index = hash(value);
  node *head = hashtable[index];
  if (!head) {
    hashtable[index] = (node *)malloc(sizeof(node));
    hashtable[index]->next = NULL;
    hashtable[index]->key = strdup(value);
  } else {
    node *prev = head;
    for (; head; prev = head, head = head->next)
      if (!strcmp(head->key, value))
        return 0;
    prev->next = (node *)malloc(sizeof(node));
    prev->next->next = NULL;
    prev->next->key = strdup(value);
  }
  return 1; // successful
}
int hash_remove(char *value) {
  unsigned index = hash(value);
  node *head = hashtable[index];
  if (!head)
    return 0; // doesn't exist! unsuccessful
  else if(!strcmp(head->key, value)){
    hashtable[index] = head->next;
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
  return 1; // successful
}
void print_all() {
  for (int i = 0; i < HASH_SIZE; i++)
    for (node *temp = hashtable[i]; temp; temp = temp->next)
      printf("%s\t", temp->key);
  printf("\n");
}
void hash_init(){
	for(int i = 0; i < HASH_SIZE;i++)
		hashtable[i] = NULL;
}
int main(void) {
	hash_init();
  char *fruits[] = {"apple",  "banana",    "orange",    "banana", "kiwi",
                    "grapes", "srawberry", "blueberry", "orange"};
  for (int i = 0; i < 9; i++)
    printf("Adding %s was%s successful!\n", fruits[i],
           hash_add(fruits[i]) ? "" : " not");
  char *temp = (char *)malloc(4);
  for (int i = 0; i < 900; i++) {
    sprintf(temp, "%d", i);
    hash_add(temp);
  }
  for (int i = 0; i < 850; i++) {
    sprintf(temp, "%d", i);
    hash_remove(temp);
  }
  print_all();
  return 0;
}