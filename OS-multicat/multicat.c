#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 8*1024*1024
//8 MB buffer


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_read = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_write = PTHREAD_COND_INITIALIZER;

bool done = false;
int reading_to = 1;
int writing_from = 1;
char buffer_1[SIZE]; 
char buffer_2[SIZE];
int buffer_1_dat = 0;
int buffer_2_dat = 0;



void *read_to_buff(void *data){
  int readed;
    while(true){
	if (done == true){break;}
	pthread_mutex_lock(&lock);
	switch (reading_to){
	  case 1 :{
	      if (buffer_1_dat > 0 ){
		pthread_cond_wait(&cond_read, &lock);
		}
	    readed = read(0, buffer_1 , SIZE);
	    if (readed == 0){ done = true; }
	    buffer_1_dat +=readed;
	    reading_to = 2;
	    pthread_cond_signal(&cond_write);
	    break;
	} 
	  case 2 : {
	      if (buffer_2_dat > 0 ){
		pthread_cond_wait(&cond_read, &lock);
		}
	    readed = read(0,buffer_2,SIZE);
	    if (readed == 0){ done = true;  }
	    buffer_2_dat +=readed;
	    reading_to = 1;
	    pthread_cond_signal(&cond_write);
	    break;
	}	
      }
      pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
    return NULL;
}


void *print_from_buff(void *data){
    int wrote = 0;
    while(true){
	pthread_mutex_lock(&lock);
	switch (writing_from){
	  case 1:{
	    if ( buffer_1_dat == 0 ){
		pthread_cond_wait(&cond_write, &lock);
	    }
	    wrote = write(1, buffer_1, buffer_1_dat);  
	    buffer_1_dat = buffer_1_dat -wrote;
	    writing_from = 2;
	    pthread_cond_signal(&cond_read);
	    break;
	}
	
	  case 2:{
	    if ( buffer_2_dat == 0 ){
		pthread_cond_wait(&cond_write, &lock);
	    }
	    wrote = write(1, buffer_2, buffer_2_dat); 
	    buffer_2_dat = buffer_2_dat - wrote;
	    writing_from = 1;
	    pthread_cond_signal(&cond_read);
	    break;
	  }
	}
	pthread_mutex_unlock(&lock);
        if (done == true){
	    break;}
   }
   
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char** argv) {
    pthread_mutex_init(&lock, NULL);
    pthread_t reader;
    pthread_t printer;

    int create_read_stat = pthread_create(&reader, NULL, read_to_buff,  NULL);
    if (create_read_stat != 0) {
	printf("Error creating reading thread, error code: %d \n",create_read_stat );
    }
    int create_printer_stat = pthread_create(&printer, NULL, print_from_buff,  NULL);
    if (create_printer_stat != 0) {
	printf("Error creating printing thread, error code: %d \n",create_printer_stat );
    }
    int end_status_reader = pthread_join(reader, NULL);
    if (end_status_reader != 0) {
	printf("Reader error, error code: %d \n",end_status_reader );
    }
   /* int end_status_printer = pthread_join(printer, NULL);
    if (end_status_printer != 0) {
	printf("Printer error, error code: %d \n",end_status_printer );
   }*/
   int mutex_status = pthread_mutex_destroy( &lock);
   if (mutex_status != 0) {
       printf("Mutex not destroyed, error code: %d \n",mutex_status );
   }
    return 0;
}
