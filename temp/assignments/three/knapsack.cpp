/*
Connor Baldes

CS325 Assignment 3: Problem One

1/29/21

*/
#ifndef KNAPSACK_CPP
#define KNAPSACK_CPP


#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <time.h>
#include <chrono> // used to get run time

using namespace std;
using namespace std::chrono; //used to get run time

//This function is an implementation of Dynamic programming it takes in two array one holding the values assosiated with 
// a list of items and another holding those items weights. It also takes in a max weight value, and the number of items 
// 
int knapsack_dp(int w, int* wt, int* val, int n) {
    //create knapsack 2d array to hold table values
    int** knapsack = new int*[n+1];

    for(int i = 0; i < n+1; i++) {
        knapsack[i] = new int[w];
    }
    //fill first row and column with a value of zero to account for position on knapsack table with values of weight 0 or 
    // or 0 items
    for(int i = 0; i < n+1; i++){
        knapsack[i][0] = 0;
    }

    for(int i = 0; i < w+1; i++){
        knapsack[0][i] = 0;
    }
    //loop through size of nap sack not including first row and first column which all have values of 0
    for(int i = 1; i < n+1; i++) {
        for(int j = 1; j < w+1; j++) {
            //check to see if the weight of the curremt item is less than the current weight column
            if(wt[i-1] <= j) {
                //if yes check to see if adding the value at i-1 will increase the value of the knapsack table 
                if((val[i-1] + knapsack[i-1][j-wt[i-1]]) > knapsack[i-1][j]) {
                    //if so add that value to existing max and place it at current index
                    knapsack[i][j] = (val[i-1] + knapsack[i-1][j-wt[i-1]]);

                }
                else {
                    //if not place previosly obtained max at current index
                    knapsack[i][j] = knapsack[i-1][j];

                }
            }
            else {
                //if not place previosly obtained max at current index
                knapsack[i][j] = knapsack[i-1][j];

            }
        }
        
    }
    //return max possible value 
    return knapsack[n][w];
}
//This function has the same purpose as the function above but uses a recursive algorithm to find 
// the max possible value
int knapsack_rec(int w, int* wt, int* val, int n) {
    //if the number of elements is zero or remaining allowed weight is 0 return a value of 0
    if(n == 0 || w == 0) {
        return 0;
    }
    //if the weight of the last item is greater than the max weight
    if(wt[n-1] > w) {
        //recursevly call funtion with the value of n being one less and return the result of that call
        return knapsack_rec(w, wt, val, n-1);
    }
    else {
        //if the value of the last item plus the value recieved from recursively calling the function with the weight being original
        // weight minus weight of last item is greater than the value from recursevly calling the function with the original weight
        if(val[n-1] + knapsack_rec(w-wt[n-1], wt, val, n-1) > knapsack_rec(w, wt, val, n-1)) {
            //return that greather value
            return (val[n-1] + knapsack_rec(w-wt[n-1], wt, val, n-1));
        }
        else {
            //return the other value
            return knapsack_rec(w, wt, val, n-1);
        }
    }

}

int main(int argc, char *argv[]) {
    int weight; //max weight
    int items; // number of items
    int* val; // array of item values
    int* wt; // array of item weights
    int max_dp; //max values DP
    int max_rec; // max value rec

    //seed random number generater
    srand (time(NULL));
    // get max weight and number of items from command line
    items = atoi(argv[1]);
    weight = atoi(argv[2]);
    //create arrays of size number of items
    val = new int[items];
    wt = new int[items];
    //fill array with random values
    for(int i = 0; i < items; i++) {
        val[i] = ((rand() % 1000) + 1);
        wt[i] = ((rand() % (weight/5)) + 1 );
    }
    //time dynamic programing alg function
    auto start_dp = high_resolution_clock::now();
    max_dp = knapsack_dp(weight, wt, val, items);
    auto stop_dp = high_resolution_clock::now(); 
    duration<double> elapsed_dp = stop_dp-start_dp;
    //time recursive programming alg function
    auto start_rec = high_resolution_clock::now();
    max_rec = knapsack_rec(weight, wt, val, items);
    auto stop_rec = high_resolution_clock::now(); 
    duration<double> elapsed_rec = stop_rec-start_rec;

    //print results
    cout << "N=" << items << "  W=" << weight << "  Rec time = " << elapsed_rec.count() << "  DP time = " << elapsed_dp.count() << "  Max Rec = " << max_rec << "  Max DP = " << max_dp << endl;
    

    return 0;
}

#endif