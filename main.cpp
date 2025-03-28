#include <iostream>
#include "graph.h"
using namespace std;


int main(){
    graph cool("inputConnections.txt");
    

    int source, dest;
    cout << "Source: ";
    cin >> source;
    cout  << "Destination: ";
    cin >> dest;
    cout << cool.shortestPath(source, dest) << endl;
}
