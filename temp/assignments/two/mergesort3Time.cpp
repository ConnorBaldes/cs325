/*
    Connor Baldes

    merge sort test

    CS325

    1/20/21


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


/*
    This function is used to merge together 3 different ranges of an array in a sorted order. 
    Disclaimer: The mergesort3 algorithm that I implemented was inspired by the the page 
    https://www.geeksforgeeks.org/3-way-merge-sort/ I learned the basics for how to implement a 3 way merge
    sort alg from this site and used what I learned to help me implement my mergesort3 program. 

*/
void merge3(int* data, int min, int middle_one, int middle_two, int max, int* org) {
    //initialize variable that will be used to iterate through the input arrays. 
    int i = min;
    int j = middle_one;
    int k = middle_two;
    int w = min;
    //loop through each of the three split ranges of the array starting at each ranges beginning
    // and continuing as long as none of the ranges have been exceeded
    while( (i < middle_one) && (j < middle_two) && (k < max)) {
        //if the value at the minimum value is less than the value at the first midpoint
        if(data[i] < data[j]) {
            //if the value at min is less than the value at the second midpoint
            if(data[i] < data[k]) {
                org[w++] = data[i++];
            }
            else {
                org[w++] = data[k++];
            }
        }
        else {
            //if the value at the first midpoint is less than the value at the second midpoint
            if(data[j] < data[k]) {
                org[w++] = data[j++];
            }
            else {
                org[w++] = data[k++];
            }
        }
    }
    //loop for case where the first range and the second range have values remaining
    while((i < middle_one) && (j < middle_two)) {
        if(data[i] < data[j]) {
            org[w++] = data[i++];
        }
        else {
            org[w++] = data[j++];
        }
    }
    // same as last loop but for values in the second and third ranges
    while((j < middle_two) && (k < max)) {
        if(data[j] < data[k]) {
            org[w++] = data[j++];
        }
        else{
            org[w++] = data[k++];
        }

    }
    // again same as last loop but for values in the first and third loop
    while((i < middle_one) && (k < max)) {
        if(data[i] < data[k]){
            org[w++] = data[i++];
        }
        else {
            org[w++] = data[k++];
        }
    }
    //copy values left from first range
    while(i < middle_one) {
        org[w++] = data[i++];
    }
    //copy values left from second range
    while(j < middle_two) {
        org[w++] = data[j++];
    }
    //copy values left from third range
    while(k < max) {
        org[w++] = data[k++];
    }

}
/*
    Function that will recursively sort a given array by splitting it into subarrays and 
    sorting those sub arrays then combining the sub arrays back together until the original array 
    is returned sorted.
    As stated in the description for the merge3 function I received insperation and guidance for implementing this 
    mergesort3 alg from the site https://www.geeksforgeeks.org/3-way-merge-sort/ 
*/
void mergesort3(int* data, int min, int max, int*org) {
    //if the array only has one element it does not need to be sorted. 
    if((max - min) < 2) {
        return;
    }
    //create variables to hold the two mid points in the 3 way array split
    int middle_one = (min + ((max - min)/3));
    int middle_two = (min + 2*((max - min)/3) + 1);
    //sort the 3 subarray recursively
    mergesort3(org, min, middle_one, data);
    mergesort3(org, middle_one, middle_two, data);
    mergesort3(org, middle_two, max, data);
    //merge the subarrays
    merge3(org, min, middle_one, middle_two, max, data);
}


int main(int argc, char *argv[]) {
    int size;
    int* data;
    int* data2;
    srand (time(NULL));

    size = atoi(argv[1]);
    data = new int[size];
    data2 = new int[size];
    for(int i = 0; i < size; i++) {
        data[i] = rand() % 10001;
        data2[i] = data[i];
    }
    auto start = high_resolution_clock::now();
    mergesort3(data, 0, size, data2);
    auto stop = high_resolution_clock::now(); 
    duration<double> elapsed = stop-start;
    cout << "Size: " << size << " Time: " << elapsed.count() << endl;
    

    return 0;
}



#endif