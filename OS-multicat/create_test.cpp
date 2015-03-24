#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;


int main(int argc, char** argv) {
    for (int i = 0; i< 10000000; i++){
      int r = rand() % 50 + 20;
      cout << "abcd"<<r <<"fghijk"<< endl;
    }
    return 0;
}