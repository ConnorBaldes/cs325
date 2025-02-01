/*
    Connor Baldes

    insertion sort test

    CS325

    1/12/21


*/

#ifndef INSERTTIME_CPP
#define INSERTTIME_CPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;



void insertion_sort(int* array, int size) {

    int i;
    int key;
    int j;

    for(i = 1; i < size; i++) {

        key = array[i];
        j = i -1;

        while( j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j-1;
        }
        array[j+1] = key;
    }
}

int main(int argc, char *argv[]) {
    int size;
    int* data;
    srand (time(NULL));

    size = atoi(argv[1]);
    data = new int[size];
    for(int i = 0; i < size; i++) {
        data[i] = rand() % 10001;
    }
    auto start = high_resolution_clock::now();
    insertion_sort(data, size-1);
    auto stop = high_resolution_clock::now(); 
    duration<double> elapsed = stop-start;
    cout << "Size: " << size << " Time: " << elapsed.count() << endl;

    

    return 0;
}



#endif