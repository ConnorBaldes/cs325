/*
Connor Baldes

CS325 HW4

2/9/21

*/


#ifndef LAST_TO_START_CPP
#define LAST_TO_START_CPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <time.h>
#include <fstream>

using namespace std;

struct activity {
    int number;
    int start;
    int finish;

};

void insertion_sort(struct activity* A, int size) {

    int i;
    struct activity key;
    int j;
    //loop through full array
    for(i = 1; i < size; i++) {

        key.number = A[i].number;
        key.start = A[i].start;
        key.finish = A[i].finish;
        j = i -1;
        //while j is greter than 0 and the value at array index j is less than the current value at
        // array index i continue
        while( A[j].start < key.start && j >= 0) {
            A[j + 1].number = A[j].number;
            A[j + 1].start = A[j].start;
            A[j + 1].finish = A[j].finish;
            j = j-1;
        }
        A[j + 1].number = key.number;
        A[j + 1].start = key.start;
        A[j + 1].finish = key.finish;
    }
}


//this function takes the file object and reads out integers and places them in an array
void get_array(fstream &file, int size, struct activity* A) {

    string token;
    //loop for the number of activities in the current set and add 
    //their values to an array. 
    for(int i = 0; i < size; i++) {

        getline(file, token, ' ');
        A[i].number = stoi(token);

        getline(file, token, ' ');
        A[i].start = stoi(token);

        getline(file, token);
        A[i].finish = stoi(token);

    }

}

void last_to_first(struct activity* A, int num_act, int set) {

    int num_selected = 0; //number of selected items
    struct activity* selected_act; //array to hold selected activities
    selected_act = new struct activity[num_act];   
    
    //set first activity to last activity that starts in set.
    selected_act[0].number = A[0].number;
    selected_act[0].start = A[0].start;
    selected_act[0].finish = A[0].finish;
    num_selected += 1; //increment the number of selected activities
    //loop through all activities
    for(int i = 1; i < num_act; i++) {
        //if the finish time of the current activity is less than or equal to the 
        //start time of the previously selected activity add it to the list of selected
        // activities
        if(A[i].finish <= selected_act[num_selected-1].start) {
            selected_act[num_selected].number = A[i].number;
            selected_act[num_selected].start = A[i].start;
            selected_act[num_selected].finish = A[i].finish;
            num_selected += 1;
        }

    }
    //print results
    cout << "Set " << set << endl;
    cout << "Number of activities selected = " << num_selected << endl;
    cout << "Activities: ";
    for(int i = num_selected; i > 0; i--) {
        cout << selected_act[i-1].number << " ";
    }
    cout << "\n" << endl;

    delete [] selected_act;
    selected_act = NULL;

}

int main() {

    fstream file;
    string temp;
    int num_act;
    //pointer to an activity struct
    struct activity* A;
    int set = 0; //number of sets
    file.open("act.txt");
    if(file == NULL) {
        exit(1); //if file cant be opened end program
    }
    
    while(1){

        getline(file, temp); //get number of activities in next set
        if(file.eof()) { //if all sets have been processed end of file flag will be set and loop will break
            break;
        }
        set += 1; //increase number of sets
        num_act = stoi(temp);
        A = new struct activity[num_act]; //initialize array with the number of elements being the size of current set
        get_array(file, num_act, A); // fill array
        insertion_sort(A, num_act); // sort array
        last_to_first(A, num_act, set); // get optimal set

   
        delete [] A;
        A = NULL;
    }
    file.close();

    return 0;
}

#endif