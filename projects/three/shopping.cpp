/*
Connor Baldes

CS325 Assignmet 3: Problem Two

1/29/21

*Note: Much of the code in this program is re-used from my implementation of "knapsack.cpp" therefore
       I will only be adding comments on the portions that are original to this program because the comments 
       for the re-used parts are in the program "knapsack.cpp"
*/


#ifndef SHOPPING_CPP
#define SHOPPING_CPP


#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <time.h>
#include <fstream>

using namespace std;

//This function takes all the values aquired after analizing a single case and outputs 
// them to the file "results.txt"
void print(int max_v, int cur_case, int**fv, int f, int n, int* num_items, fstream& file) {

    file << "Test Case: " << cur_case << endl;
    file << "Total Price: " << max_v << endl;
    file << "Member Items:" << endl;
    //loop through array of item numbers each family member should by
    for(int i = 0; i < f; i++) {
        file << i+1 << ": ";
        for(int j = num_items[i]-1; j >=0; j--) {
            file << fv[i][j] << " ";
        }
        file << endl;
    }
      
}
//same as in knapsack.cpp except for the addition of an array to hold the item numbers each family member should get and 
// how many items each family member should have
int knapsack_dp(int w, int* wt, int* val, int n, int* fv, int* num_items) {
    int k = 0; // value that will hold the number of items a specific family member shold get
    int weight = w; //variable to hold weight value we can adjust
    int** knapsack = new int*[n+1];

    for(int i = 0; i < n+1; i++) {
        knapsack[i] = new int[w+1]; //Id just like to take a moment to say FUCK THIS LINE OF CODE. I spent literally hours trying to debug
                                    //my program and it turned out that what was braking the whole thing was the fact that in my knapsack.cpp
                                    //implementation the value is int[w] and here it needed to be int[w+1] and that is literaly the only reason
                                    //my assigment was late. 
    }

    for(int i = 0; i < n+1; i++){
        knapsack[i][0] = 0;
    }

    for(int i = 0; i < w+1; i++){
        knapsack[0][i] = 0;
    }

    for(int i = 1; i < n+1; i++) {
        for(int j = 1; j < w+1; j++) {

            if(wt[i-1] <= j) {

                if((val[i-1] + knapsack[i-1][j-wt[i-1]]) > knapsack[i-1][j]) {
                    
                    knapsack[i][j] = (val[i-1] + knapsack[i-1][j-wt[i-1]]);

                }
                else {

                    knapsack[i][j] = knapsack[i-1][j];

                }
            }
            else {

                knapsack[i][j] = knapsack[i-1][j];

            }
        }

        
    }
    //m = max value 
    int m = knapsack[n][w];
    //loop through to find item numbers eack family member should get 
    // and how many items they should get
    for(int i = n; i>0 && m > 0 ; i--) {
        if(m == knapsack[i-1][weight]) {
            continue;
        }
        else{
            fv[k++] = i;
            m = m - val[i-1];
            weight = weight - wt[i-1];
        }
            
        
    }
    *num_items = k;
    return knapsack[n][w];
}
void run_cases(fstream& file,fstream& file2, int cur_case) {

    int* num_items;
    string temp;
    int weight = 0;
    int n = 0; //number of items in a case
    int* fw = NULL; // array to hold weight each family member can hold
    int** fv = NULL; //2-d array to hold item numbers each family member should have
    int* val = NULL; //array to hold price of items
    int* wt = NULL; //array to hold weight of items
    int f = 0; //number of family members
    int max_v = 0;
    int** knapsack = NULL;
    //get number of items
    getline(file, temp);
    n = stoi(temp);
    //create value and weight arrays for the number of items
    val = new int[n];
    wt = new int[n];

    //read lines from file to fill the arrays with their valies
    for(int i = 0; i < n; i++) {

        getline(file, temp, ' ');
        val[i] = stoi(temp);
        getline(file, temp);
        wt[i] = stoi(temp);

    }
    //get number of family members and create arrays to hold their values
    getline(file, temp);
    f = stoi(temp);
    fw = new int[f];
    fv = new int*[f];
    num_items = new int[f];

    for(int i = 0; i < f; i++) {
        fv[i] = new int[n];
        memset(fv[i], 0, sizeof(fv[i]));
        getline(file, temp);
        fw[i] = stoi(temp);
        
        
    }
    //for eack family member run knapsack function
    for(int i = 0; i < f; i++) {

        weight = fw[i];

        max_v += knapsack_dp(weight, wt, val, n, fv[i], &num_items[i]);
 
        weight = 0;

    }

    //print full case results to file "results.txt"
    file2.open("results.txt", ios::out | ios::app);
    if(file2.is_open()) {
        print(max_v, cur_case, fv, f, n, num_items, file2);
    }
    file2.close();

}

int main() {
    fstream file2;
    fstream file; //shopping.txt
    string temp; //string for getline storage
    int cases; //number of cases


    file.open("shopping.txt");
    if(file == NULL) {
        cout << "Unable to open Data file. " << endl;
        exit(1);
    }
    //get number of cases
    getline(file, temp);
    cases = stoi(temp);

    //run for number of cases
    for(int i = 0; i < cases; i++) {
        
        run_cases(file,file2, i+1);

    }
    file.close();



    return 0;
}

#endif