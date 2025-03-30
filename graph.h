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
        bool* visited;
        int* edgeTo;
        int* distTo;
    public:
        graph(string inputFileName){
            //integer and char that will help read the file into the adjacency list
            int firstNum, secondNum;
            char filler;
            

            

            //opening file
            ifstream inputFile(inputFileName);

            //finding out the number of vertices (the first line of input file)
            inputFile >> numVertices ;

            
            //arrays that will help facilitate BFS
            visited = new bool[numVertices];
            edgeTo = new int[numVertices];
            distTo = new int[numVertices];

        

            //adjacency list, allocating memory
            adjList = new ResizingArray<int> *[numVertices];
            for(int i = 0; i < numVertices; i++){
                adjList[i] = new ResizingArray<int>;
            }


            //reading in all the connections from the input file
            while(inputFile >> firstNum >> secondNum ){
               // cout << firstNum << " " << secondNum << endl;
                adjList[firstNum]->Push(secondNum);
                
            }
            inputFile.close();

            
            
            
        }


        ~graph(){

            //deleting adjacency list
            for(int i = 0; i < numVertices; i++){
                delete adjList[i];
                
            }
            delete [] adjList;

            //deleting bfs arrays
            delete [] visited;
            delete [] edgeTo;
            delete [] distTo;
           
        }










        int shortestPath(int source, int destination){

            //Breadth First Search 

            //setting all bfs arrays to nothing
            for(int i = 0; i < numVertices; i++){
                visited[i] = false;
                edgeTo[i] = -1;
                distTo[i] = -1;//-1 represents infinity here
            }

            Queue<int>* bfsQueue = new Queue<int>;

            //starting the timer
            //credit to geeks for geeks for help with using chrono librarie for timing
            auto start = high_resolution_clock::now();

            //load source vertex into queue
        
            bfsQueue->Enqueue(source);
            visited[source] = true;
            distTo[source] = 0;

            //while loop that keeps going until we have found our destination vertex
            while (!bfsQueue->IsEmpty()) {
                
                //dequeueing next vertex
                int v = bfsQueue->Dequeue();

                if(visited[destination]){
                    break;
                }



                //getting the list of vertex that the vertex we just dequeued points to
                
                

                //going through list of connecting vertexes until there is no more
                for(int i = 0; i < adjList[v]->getSize(); i++) {

                    int neighbor = adjList[v]->getValue(i);

                    //updating all the information in the three arrays
                    if (!visited[neighbor]) {
                        bfsQueue->Enqueue(neighbor);
                        visited[neighbor] = true;
                        edgeTo[neighbor] = v;
                        distTo[neighbor] = distTo[v] + 1;
                    }

                
                }

                
            }

            

            //printing out time it took for 
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<nanoseconds>(stop - start);
            cout << "Calculation took: " << duration.count() << " nanoseconds" <<  endl;

            delete bfsQueue;

            if(!visited[destination]){
                cout << "No Path Found" << endl;
                return -1;
            }



            //return the correct distance
            return distTo[destination]; 
            

        }



        

};

#endif