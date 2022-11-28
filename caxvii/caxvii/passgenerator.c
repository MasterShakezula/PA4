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
int lenOfPasswords =0;

void *produce(void *args) { 
  for(int i = 0; i < (int)args; i++){
	int index = rand()%N;
    pthread_mutex_lock(&mutex);
    hash_add(&h, words[index]);
    pthread_mutex_unlock(&mutex);
	printf("Produced -> %s\n", words[index]);
  }
}

char* concatenate(char* whatever[], int len, char* separator){

  char* out = (char)malloc(len (20 + strlen(separator)));
  sprintf(out, "%s%s%s", out, separator, whatever[0]);
  for(int i = 1; i < len; i++)
    sprintf(out, "%s%s%s", out, separator, whatever[i]);
  return out;
  
}


void *consume(void *args) { 

  char* passwords[lenOfPasswords];
  int count = 0;
  for(int i = 0; i < (int)args; i++){
	  int j;

	while(1){
		for(j = 0; !hash_search(h, words[j]);j++);
		pthread_mutex_lock(&mutex);
		if(hash_remove(&h, words[j])){
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);
	}

	printf("Consumed -> %s\n", words[j]);
    if(count < lenOfPasswords ){
      passwords[count++] = words[j];
    }
    if(count == lenOfPasswords){
      printf("%s\n", concatenate(passwords, lenOfPasswords, ","));
    }
    
  } 
  pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[]){
	pthread_mutex_init(&mutex, NULL);
  int numOfProducers;
  int numOfConsumers;
  int numOfPasswords;
  int lenOfPasswords;
	pthread_t producers[numOfProducers]; // make it match the argv passed in [2]
	pthread_t consumers[numOfConsumers]; // make it match the argv passed in [4]
  //int pass_len = 2;
  //int k = 10;
  //int m = 5;
  int j;

  
  
  
#include <pthread.h>

  int numOfProducers;
  int numOfConsumers;
  int numOfPasswords;
  
	pthread_t producers[numOfProducers]; // make it match the argv passed in [2]
	pthread_t consumers[numOfConsumers]; // make it match the argv passed in [4]
  //int pass_len = 2;
  //int k = 10;
  //int m = 5;
  int j;

  
  
  if(argc > 11){
    printf("Too many arguments, use the following format:\n");
    printf("-p n -c m -f file -n k -l -l\n");
  }
  if(argv[2] != NULL){
    numOfProducers = atoi(argv[2]);
    pthread_t producers[numOfProducers];
    printf("Number of producers %d\n", numOfProducers);
  }
  if(argv[4] != NULL){
    numOfConsumers = atoi(argv[4]) + 1;
    pthread_t consumers[numOfConsumers];
    printf("Number of consumers %d\n", numOfConsumers);
  }
  
  if(argv[8] != NULL){
    numOfPasswords = atoi(argv[8]);
    printf("Number of passwords %d\n", numOfPasswords);
  }
  if(argv[10]!= NULL){
    lenOfPasswords = atoi(argv[10]);
    printf("number of passleng %d\n", lenOfPasswords);
  }
  
  
	hash_init(&h, 99991);
	srand(time(NULL));
	FILE* f = fopen("dict.txt", "r");
	char* line = (char*)malloc(26);
	int i = 0;
	while(fgets(line, 25, f)){
		line[strlen(line) - 2] = '\0';
		words[i++] = strdup(line); // STEP 1: add dictionary to words[] 
	}
	/*for(int j = 0; j < 10;j++){
		printf("%s\n", words[rand()%i]);
	}*/

  // STEP 2 spawning producers
	for(i = 0; i < numOfProducers;i++){
		//printf("Producer %d is getting spawned!\n", i);
		pthread_create(producers + i, NULL, produce, (void*)1); 
	}
  
	//STEP 3: Join Producers
	for(i = 0; i < numOfProducers;i++)
		pthread_join(producers[i], NULL);

  //STEP 4: Spawn Consumers
	for(i = 0; i < numOfConsumers;i++){

    //Make array to store passwords

    //STEP 4.1 Consumer #i generates K/m passwords
		pthread_create(consumers + i, 
          NULL, 
          consume, 
          (void*)((numOfPasswords)/numOfConsumers));
    //pthread_create(consumers + i, NULL, consume, (void *)(k/m));
    printf("Inside consumer creation loop\n");


    }
if(argc > 11){
    printf("Too many arguments, use the following format:\n");
    printf("-p n -c m -f file -n k -l -l\n");
  }
  if(argv[2] != NULL){
    numOfProducers = atoi(argv[2]);
    pthread_t producers[numOfProducers];
    printf("Number of producers %d\n", numOfProducers);
  }
  if(argv[4] != NULL){
    numOfConsumers = atoi(argv[4]) + 1;
    pthread_t consumers[numOfConsumers];
    printf("Number of consumers %d\n", numOfConsumers);
  }
  
  if(argv[8] != NULL){
    numOfPasswords = atoi(argv[8]);
    printf("Number of passwords %d\n", numOfPasswords);
  }
  if(argv[10]!= NULL){
    lenOfPasswords = atoi(argv[10]);
    printf("number of passleng %d\n", lenOfPasswords);
  }
  
  
	hash_init(&h, 99991);
	srand(time(NULL));
	FILE* f = fopen("dict.txt", "r");
	char* line = (char*)malloc(26);
	int i = 0;
	while(fgets(line, 25, f)){
		line[strlen(line) - 2] = '\0';
		words[i++] = strdup(line); // STEP 1: add dictionary to words[] 
	}
	/*for(int j = 0; j < 10;j++){
		printf("%s\n", words[rand()%i]);
	}*/

  // STEP 2 spawning producers
	for(i = 0; i < numOfProducers;i++){
		//printf("Producer %d is getting spawned!\n", i);
		pthread_create(producers + i, NULL, produce, (void*)1); 
	}
  
	//STEP 3: Join Producers
	for(i = 0; i < numOfProducers;i++)
		pthread_join(producers[i], NULL);

  //STEP 4: Spawn Consumers
	for(i = 0; i < numOfConsumers;i++){

    //Make array to store passwords

    //STEP 4.1 Consumer #i generates K/m passwords
		pthread_create(consumers + i, 
          NULL, 
          consume, 
          (void*)((numOfPasswords)/numOfConsumers));
    //pthread_create(consumers + i, NULL, consume, (void *)(k/m));
    printf("Inside consumer creation loop\n");

    //4.1.1 removing 'l' random words from the central hash table

    //4.1.2 produce password by concatenating all words into one
  
    //pthread_mutex_destroy(&mutex);
  }
  for(j = 0; j < lenOfPasswords; j++){
      printf("concatenate!!!\n");
      //char* out = concatenate(words, lenOfPasswords, ",");
      //printf("%s", out);
      }
	for(i = 0; i < numOfConsumers;i++){
    printf("inside join consumer loop \n");
		pthread_join(consumers[i], NULL); // STEP 5 join consumers
    printf("Did it break here?!?!?!?!\n");
    } 
  pthread_mutex_destroy(&mutex);
}