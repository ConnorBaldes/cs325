/*
Connor Baldes

CS325 HW5

2/23/21

*/


#ifndef E_MST_CPP
#define E_MST_CPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <time.h>
#include <fstream>
#include <cmath> 

using namespace std;
//structure to hold the value of a point on a graph
struct point {
    
    int x;
    int y;
};
//structure to hold values for each test case 
struct test_case {

    int vertices;
    struct point* points;
    int** graph;

};


//this function takes the file object and reads out integers and places them in an array
void get_test_case(fstream &file, struct test_case* A, int i) {

    string token;
    getline(file, token);
    A[i].vertices = stoi(token); //set number of vertices in a given set
    A[i].points = new struct point[A[i].vertices]; //create an array that is the size of the number of vertices to hold the point values
    A[i].graph = new int*[A[i].vertices];
    for(int j = 0; j < A[i].vertices; j++) {
        A[i].graph[j] = new int[A[i].vertices];
    }
    //loop for the number of points in the current set and add 
    //their values to an array. 
    for(int j = 0; j < A[i].vertices; j++) {

        getline(file, token, ' ');
        A[i].points[j].x = stoi(token);

        getline(file, token);
        A[i].points[j].y = stoi(token);


    }

}
//this function is used to get the distance from one point on the graph to another point
int get_distance(struct test_case* tc,int i , int p1, int p2 ) {

    int x_dist = abs(tc[i].points[p1].x - tc[i].points[p2].x);
    int y_dist = abs(tc[i].points[p1].y - tc[i].points[p2].y);
    int distance = round(sqrt((x_dist*x_dist)+(y_dist*y_dist))); //a^2 + b^2 = c^2 round to nearest integer

    return distance;
}

void set_dist_graph(struct test_case* tc, int tcase) {
    for(int i = 0; i < tc[tcase].vertices; i++) {

        for(int j = 0; j < tc[tcase].vertices; j++) {

            tc[tcase].graph[i][j] = get_distance(tc, tcase, i, j); //set the distance for all point to all other points. 
        }
    }
}

int get_min_key(struct test_case* tc, int tcase, int* key, int* mst) {

    int min = 9999999; //arbitrarily large number 
    int index;
    for(int i = 0; i < tc[tcase].vertices; i++) {

        if(key[i] < min && mst[i] == 0) { //if the value of key[i] is less than the current min and i is not already in the mst 
            min = key[i]; // set min to current key
            index = i;  // set index of key to i
        }
    }

    return index;
}

int get_mst(struct test_case* tc, int tcase) {

    int weight = 0;
    //initialize arrays all the size of the number of vertices in the case
    int key[tc[tcase].vertices];
    int parent[tc[tcase].vertices];
    int present[tc[tcase].vertices];

    int w;
    // initially define arrays
    for(int i = 0; i < tc[tcase].vertices; i++) {
        key[i] = 9999999; //arbitrarily large number
        parent[i] = 0; 
        present[i] = 0;
    }
    parent[0] = -1;
    key[0] = 0;
    for(int i = 0; i < tc[tcase].vertices; i++) {

        w = get_min_key(tc, tcase, key, present); //get the index of the min key
        
        present[w] = 1; //set the index of present at the min key index to true indicating it is in the mst

        for(int j = 0; j < tc[tcase].vertices; j++) {

            if(tc[tcase].graph[w][j] > 0 && present[j] == 0 && key[j] > tc[tcase].graph[w][j]) { // if the value of the distance graph at min key index j is greater than 0
                                                                                                 // and j is not present in the mst and key at j is greater that distance at w j
                key[j] = tc[tcase].graph[w][j]; //key at j is now the value of the distance graph at the min key index j 
                parent[j] = w; //the parent is set to the prev min key index

            }
        }
    }

    for(int i = 0; i < tc[tcase].vertices; i++) {
        int u = parent[i];
        int v = i;
        weight += tc[tcase].graph[v][u]; //get the total weight of the mst
    }
    return weight;
}

int main() {

    fstream file;
    string temp;
    int num_cases;
    struct test_case* test_cases;
    int weight;
    
    file.open("graph.txt");
    if(file == NULL) {
        exit(1); //if file cant be opened end program
    }
    getline(file, temp);
    num_cases = stoi(temp);
    test_cases = new struct test_case[num_cases]; // array of test cases
    cout << "Number of cases: " << num_cases << endl;
    for(int i = 0; i < num_cases; i++) {

        get_test_case(file, test_cases, i); // fill array
        set_dist_graph(test_cases, i); //fill distance graph array
        weight = get_mst(test_cases, i); // get total weight of case 
        cout << "Test Case "<< i+1 << " weight: " << weight << endl;

    }
    delete [] test_cases;
    test_cases = NULL;
    file.close();

    return 0;
}

#endif