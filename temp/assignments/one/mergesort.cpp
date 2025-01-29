/*
    Connor Baldes

    merge sort implementaion

    CS325

    1/12/21


*/
#ifndef MERGE_CPP
#define MERGE_CPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

//this function takes the file object and reads out integers and places them in an array
int* get_array(fstream &file, int &size, int &end) {

    char cur;
    int pos = 0;
    string data;
    string token;
    //get the first number from file which will be size of array
    getline(file,token, ' ');
    if(token == "\0") {
        end = 1;
        return NULL;
    }
    size = stoi(token);
    //create new array
     int* array = new int[size];
    //fill array will all but last number
    for(int i = 0; i < size-1; i++) {
        getline(file, token, ' ');


        array[i] = stoi(token);
    }
    //last number is filled seperately so new line can be removed.
    getline(file, token, '\n');
    array[size-1] = stoi(token);
    //return array
    return array;
}
//this functin is used to sort the values in a recursevly called array 
// Disclaimer: I learned this merge sort algorithm from the website https://www.geeksforgeeks.org/merge-sort/
// I created my own implementation for this project but I learned how to to merge sort from the above website. 

void merge(int* array, int left, int middle, int right) {

    //set variable holding the size of the left array
    int left_size = middle - left + 1;
    //set variable holding the size of the right array
    int right_size = right - middle;
    //create new arrays that will each hold half the the array passed to the function
    int left_array[left_size];
    int right_array[right_size];
    //fill both arrays with the left taking all the org array values to the left of the middle
    // and the opposite for the right array
    for(int i = 0; i < left_size; i++) {
        left_array[i] = array[left + i];
    }
    for(int i = 0; i < right_size; i++) {
        right_array[i] = array[middle + 1 + i];
    }
    //create variables to hold the current index of all three arrays in the function
    int index_one = 0;
    int index_two = 0;
    int index_three = left;
    //as long as the left index is smaller than the left side and vise versa for right continue
    while(index_one < left_size && index_two < right_size) {
        //check if left array at cur index is larger than right array at cur index
        if(left_array[index_one] <= right_array[index_two]) {
            //if so set original array at cur index to left array value
            array[index_three] = left_array[index_one];
            index_one += 1;
        }
        //if not do the opposite
        else {
            array[index_three] = right_array[index_two];
            index_two += 1;
        }
        index_three += 1;
    }
    //while left has not reached its end
    while(index_one < left_size) {
        //put the cur value of left array at cur value of original array and increment the indexes.
        array[index_three] = left_array[index_one];
        index_one += 1;
        index_three += 1;
    }
    //while right has not reached its end
    while(index_two < right_size) {
        //put the cur value of right array at cur value of original array and increment the indexes.
        array[index_three] = right_array[index_two];
        index_two += 1;
        index_three += 1;
    }
}
void merge_sort(int* array, int left, int right) {
    //used for recursive call
    if(left >= right) {
        return;
    }
    //create variable to hold position of the middle of the array
    int middle = (left+right-1)/2;
    //recursevely call merge sort on left and right sides
    merge_sort(array,left,middle);
    merge_sort(array,middle+1, right);
    merge(array, left, middle, right);
}
int main() {
    int size;
    int line = 1;
    int array_size;
    fstream file;
    int left;
    int right;
    int end = 0;
    int* data;

    file.open("data.txt");
    if(file == NULL) {
        cout << "Unable to open Data file. " << endl;
        exit(1);
    }
    cout << endl;
    while(1) {
        //get data
       data = get_array(file, size, end);
        if(end == 1) {
            break;
        }
        array_size = sizeof(data) / sizeof(data[0]);
        cout << "Unsorted Line " << line << ": ";
        for(int i = 0; i <size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;

        merge_sort(data, 0, size-1);
        cout << "Sorted Line " << line << ": ";
        for(int i = 0; i <size; i++) {
            cout << data[i] << " ";
        }
        cout << "\n" << endl;
        line += 1;
    }

    return 0;
}



#endif