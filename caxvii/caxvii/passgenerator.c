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

void *produce(void *start, void *end) { 
  for(int i = start; i <= end; i++){
	pthread_mutex_lock(&mutex);
	hash_add(&h, words[i]);
	pthread_mutex_unlock(&mutex);
	printf(words[i]); //test
  }
}

void *consume(void *args) { 
  for(int i = 0; i < (int)args; i++){
	  int j = rand()%N;
	  char concat_words[];
    //pthread_mutex_lock(&mutex);
	//for(j = 0; !hash_remove(&h, words[j]);j++);
    //pthread_mutex_unlock(&mutex);
	
	while(1){
		for(j; !hash_search(h, words[j]);j++);
		pthread_mutex_lock(&mutex);
		if(hash_remove(&h, words[j])){
			concat_words[j] = words[j];
			hash_remove(&h, words[j]);
			

		

			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);
	}
	
	
	printf("consumed %s\n", words[j]);
	concatenate(concat_words, strlen(concat_words), ',');
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

char* concatenate(charwords[],int len,char separator)
{     char* out = (char)malloc(len 20 + strlen(separator));
	  out[0] = '/0';
	  for (int i = 0; i < len; i++)
	  {       
		sprintf(out,"%s%s%s",out,separator,words[i]);
		return out;
	  } 
}


void main(int argc, char** argv){
	int numOfProducers = argv[2];
	int numOfConsumers = argv[4];
	int start;
	int end;
	char* fileName = (char*)malloc(100);
	fileName = argv[6];
	int numOfPasswords = argv[8];
	int numOfWords = argv[10];



	pthread_mutex_init(&mutex, NULL);
	pthread_t producers[numOfProducers];
	pthread_t consumers[numOfConsumers];
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
	for (i = 0; i < numOfProducers; i++) {



		if (strlen(words) % num_of_words != 0)

		{
			start = (i * (strlen(words) / num_of_prods))
				end = ((i + 1) * (strlen(words) / num_of_prods) - 1)

				if (i == num_of_prods)

				{
					start = (i * (strlen(words) / num_of_prods))
						end = (strlen(words) - 1)
				}
		}

		//printf("Producer %d is getting spawned!\n", i);
		pthread_create(producers + i, NULL, produce, start, end);


	}
	//Step B:
	for(i = 0; i < numOfProducers;i++)
		pthread_join(producers[i], NULL);
	for(i = 0; i < numOfConsumers;i++)
		pthread_create(consumers + i, NULL, consume, (void *)numOfWords);
	for(i = 0; i < numOfConsumers;i++)
		pthread_join(consumers[i], NULL);

	//for (int j = 0; j < )
}