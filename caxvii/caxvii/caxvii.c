#include <pthread.h>
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 93512
//if RAND_MAX is 32767
hash_table h;
#define long_rand(n) (((int)rand()<<15 + (int)rand())%n)
pthread_mutex_t mutex;
char* words[N];
void *produce(void *args) { 
  for(int i = 0; i < (int)args; i++){
	int index = rand()%N;
    pthread_mutex_lock(&mutex);
    hash_add(&h, words[index]);
    pthread_mutex_unlock(&mutex);
	printf("produced %s\n", words[index]);
  }
}
void *consume(void *args) { 
  for(int i = 0; i < (int)args; i++){
	  int j;
    //pthread_mutex_lock(&mutex);
	//for(j = 0; !hash_remove(&h, words[j]);j++);
    //pthread_mutex_unlock(&mutex);
	
	while(1){
		for(j = 0; !hash_search(h, words[j]);j++);
		pthread_mutex_lock(&mutex);
		if(hash_remove(&h, words[j])){
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);
	}
	
	
	printf("consumed %s\n", words[j]);
  }
  /*while(1){
		for(j = 0; !hash_search(h, words[j]);j++);
		pthread_mutex_lock(&mutex);
		if(hash_remove(&h, words[j]))
			break;
		pthread_mutex_unlock(&mutex);
	}
	*/
}
void main(void){
	int numOfProducers = argv[2];
	int numOfConsumers = argv[4];
	char* fileName = (char*)malloc(100);
	fileName = argv[6];
	int numOfPasswords = argv[8];
	int numOfWords = argv[10];
	pthread_mutex_init(&mutex, NULL);
	pthread_t producers[10];
	pthread_t consumers[5];
	hash_init(&h, 99991);
	srand(time(NULL));
	FILE* f = fopen("dict.txt", "r");
	char* line = (char*)malloc(26);
	int i = 0;
	while(fgets(line, 25, f)){
		line[strlen(line) - 1] = '\0';
		words[i++] = strdup(line);
	}
	/*for(int j = 0; j < 10;j++){
		printf("%s\n", words[rand()%i]);
	}*/
	//Step A. 
	for(i = 0; i < 10;i++){
		//printf("Producer %d is getting spawned!\n", i);
		pthread_create(producers + i, NULL, produce, (void *)10);
	}
	//Step B:
	for(i = 0; i < 10;i++)
		pthread_join(producers[i], NULL);
	for(i = 0; i < 5;i++)
		pthread_create(consumers + i, NULL, consume, (void *)20);
	for(i = 0; i < 5;i++)
		pthread_join(consumers[i], NULL);
}