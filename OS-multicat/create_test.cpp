#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;


int main(int argc, char** argv) {
    for (int i = 0; i< 10000000; i++){
      for (int j = 0; j<10 ; j++){
	int r = rand() % 200 ;
	cout << r;
      }
      cout << endl;
    }
    return 0;
}
