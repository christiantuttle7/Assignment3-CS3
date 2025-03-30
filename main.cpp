#include <iostream>
#include "graph.h"

using namespace std;


int main(){

    
    graph mainGraph("inputConnections.txt");

    int sourceArray[3];
    int numSources = 3;
    int destArray[3];
    int numDests = 3;

    auto start = high_resolution_clock::now();

    cout << "Enter Three Source: ";
    cin >> sourceArray[0] >>sourceArray[1] >> sourceArray[2];
    cin.ignore();
    cout << "Enter Three Destinations";
    cin >> destArray[0] >> destArray[1] >> destArray[2];
    cin.ignore();

    cout << endl;

    for(int i = 0; i < numSources; i++){
        cout << "Source: " << sourceArray[i] << endl;
        for(int j = 0; j < numDests; j++){
            int p = mainGraph.shortestPath(sourceArray[i], destArray[j]);
            cout << "Shortest Path to " << destArray[j] << ": " << p << endl;
        }
        cout << endl;
    }

    
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(stop - start);
    cout << "Program took: " << duration.count() << "seconds" <<  endl;



    
}
