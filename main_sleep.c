#include <pthread.h>
#include <unistd.h>
#include <sys/queue.h>
#include <stdio.h>


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
char buff[100]; //buffer
int poread ;
int powrite;
int bool;

void *read_to_buff(void *data){
    char c;
    while(bool == 1){
        if( (poread-powrite) == 100){ 
            sleep(0.1); // nahradit  za wait();
            }
        scanf ("%c",&c);  
        pthread_mutex_lock(&lock);
        buff[poread % 100] = c;
        poread+= 1;
        pthread_mutex_unlock(&lock);  
        // ak bude wait treba aj signal
    }
}

void *print_from_buff(void *data){
    char c;
    while(bool == 1){
        if( powrite == poread) { sleep(0.1);
                    }   
        else{
            pthread_mutex_lock(&lock);
            c = buff[powrite % 100];
            powrite+= 1;
            pthread_mutex_unlock(&lock);
            printf("%c",c); 
            }
        }
    }

int main(int argc, char** argv) {
    poread = 0;
    powrite = 0;
    bool = 1;
    pthread_t reader;
    pthread_t printer;
  
   pthread_create(&reader, NULL, read_to_buff,  NULL);
   pthread_create(&printer, NULL, print_from_buff,  NULL);
    // destroy mutex, cancel threads
    while(bool ==1){
    }
    return 0;
}

