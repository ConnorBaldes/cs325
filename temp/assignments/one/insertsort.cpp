/*
    Connor Baldes

    insertion sort implementaion

    CS325

    1/12/21


*/
#ifndef INSERT_CPP
#define INSERT_CPP

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

    return array;
}

//this functin is used to sort the values in an array  
// Disclaimer: I learned this insertion sort algorithm from the website https://www.geeksforgeeks.org/insertion-sort/
// I created my own implementation for this project but I learned how to use insertion sort from the above website. 
void insertion_sort(int* array, int size) {

    int i;
    int key;
    int j;
    //loop through full array
    for(i = 1; i < size; i++) {

        key = array[i];
        j = i -1;
        //while j is greter than 0 and the value at array index j is greater than the current value at
        // array index i continue
        while( j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j-1;
        }
        array[j+1] = key;
    }
}

int main() {
    int size;
    int line = 1;
    fstream file;
    int end = 0;
    int* data;

    file.open("data.txt");
    if(file == NULL) {
        cout << "Unable to open Data file. " << endl;
        exit(1);
    }
    cout << endl;
    while(1) {

       data = get_array(file, size, end);
        if(end == 1) {
            break;
        }
        cout << "Unsorted Line " << line << ": ";
        for(int i = 0; i <size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;

        insertion_sort(data, size);
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