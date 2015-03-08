#include <pthread.h>
#include <unistd.h>
#include <sys/queue.h>
#include <stdio.h>
using namespace std;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
char buff[100]; //buffer
int poread ;
int powrite;
bool done = false;

void *read_to_buff(void *data){
    char c;
    while(true){
        if( (poread-powrite) == 100){ // ak uz je read moc popredu zaspi
            sleep(0.01); 
            }
        else {
         if (scanf ("%c",&c) == EOF) 
                {done = true; // ak uz nic nenacita skonci
                return NULL;    }
        pthread_mutex_lock(&lock);
        buff[poread % 100] = c;
        poread+= 1;
        pthread_mutex_unlock(&lock);  
        }
    }
}

void *print_from_buff(void *data){
    char c;
    while(true){
        if(powrite==poread && done == true){return NULL;}
        if( powrite == poread) { sleep(0.01);
                    }   
        else{
            pthread_mutex_lock(&lock);
            c = buff[powrite % 100];
            powrite+= 1;
            printf("%c",c); 
            pthread_mutex_unlock(&lock);
            }
        }
    }

int main(int argc, char** argv) {
    poread = 0;
    powrite = 0;
    pthread_mutex_init(&lock, NULL);
    pthread_t reader;
    pthread_t printer;
  
   pthread_create(&reader, NULL, read_to_buff,  NULL);
   pthread_create(&printer, NULL, print_from_buff,  NULL);
   
   int a = pthread_join(printer, NULL);
   pthread_cancel(reader);
   pthread_cancel(printer);
   pthread_mutex_destroy( &lock);
    return 0;
}

