/*
    Connor Baldes

    merge sort test

    CS325

    1/12/21


*/


#ifndef MERGETIME_CPP
#define MERGETIME_CPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


void merge(int* array, int left, int middle, int right) {


    int left_size = middle - left + 1;
    int right_size = right - middle;

    int left_array[left_size];
    int right_array[right_size];

    for(int i = 0; i < left_size; i++) {
        left_array[i] = array[left + i];
    }
    for(int i = 0; i < right_size; i++) {
        right_array[i] = array[middle + 1 + i];
    }

    int index_one = 0;
    int index_two = 0;
    int index_three = left;

    while(index_one < left_size && index_two < right_size) {
        if(left_array[index_one] <= right_array[index_two]) {
            array[index_three] = left_array[index_one];
            index_one += 1;
        }
        else {
            array[index_three] = right_array[index_two];
            index_two += 1;
        }
        index_three += 1;
    }

    while(index_one < left_size) {
        array[index_three] = left_array[index_one];
        index_one += 1;
        index_three += 1;
    }

    while(index_two < right_size) {
        array[index_three] = right_array[index_two];
        index_two += 1;
        index_three += 1;
    }
}
void merge_sort(int* array, int left, int right) {
    if(left >= right) {
        return;
    }
    int middle = (left+right-1)/2;
    merge_sort(array,left,middle);
    merge_sort(array,middle+1, right);
    merge(array, left, middle, right);
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
    merge_sort(data, 0, size-1);
    auto stop = high_resolution_clock::now(); 
    duration<double> elapsed = stop-start;
    cout << "Size: " << size << " Time: " << elapsed.count() << endl;
    

    return 0;
}



#endif