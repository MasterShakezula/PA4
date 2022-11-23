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
void hash_init(hash_table* h, int init_capacity);
int hash_search(hash_table h,char *target);
int hash_add(hash_table* h, char *value);
int hash_remove(hash_table* h, char *value);