#include <pthread.h>
#include <unistd.h>
#include <sys/queue.h>
#include <stdio.h>
using namespace std;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
const  int buff_size = 1000; 
char buff[buff_size]; //buffer
int poread ;
int powrite;
bool done = false;
//int counter = 0; //counter can be used to see how many times yield was called

void *read_to_buff(void *data){
    char c;
    while(true){
        if( (poread-powrite) == buff_size){ // buffer full
                  pthread_yield();
  //          counter++;
            }
        else {
            c = getchar();
         if (c == EOF) 
                {done = true; 
                return NULL;    }
        pthread_mutex_lock(&lock);
        buff[poread % buff_size] = c;
        poread+= 1;
        pthread_mutex_unlock(&lock);  
        }
    }
}

void *print_from_buff(void *data){
    char c;
    while(true){
        if(powrite==poread && done == true){return NULL;} 
        if( powrite == poread) { pthread_yield(); // buffer empty
    //                counter++;
                    }   
        else{
            pthread_mutex_lock(&lock);
            c = buff[powrite % buff_size];
            powrite+= 1;
            putchar(c);
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
  // printf("%d",counter); 
    return 0;
}

