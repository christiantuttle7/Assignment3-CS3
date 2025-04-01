#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>

#include <chrono>
#include "Queue.h"
#include <fstream>

using namespace std;
using namespace std::chrono;


class graph{
    private:
        
        ResizingArray<int> **adjList;
        int numVertices;
        int lastPathTime;

        ResizingArray<int> path;
        Queue<int> bfsQueue;
        
        bool* visited;
        int* edgeTo;
        int* distTo;
    public:
        graph(string inputFileName);
        ~graph();
        int shortestPath(int source, int destination);
        int getLastPathTime();
        void printShortestPath(int source, int destination);

};
#endif
        