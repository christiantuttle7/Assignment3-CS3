#pragma once
#include <iostream>
#include <fstream>
#include "list.h"
#include "Queue.h"





class graph{
    private:
        
        List<int> **adjList;
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
            adjList = new List<int> *[numVertices];
            for(int i = 0; i < numVertices; i++){
                adjList[i] = new List<int>;
            }


            //reading in all the connections from the input file
            while(inputFile >> firstNum >> secondNum ){
               // cout << firstNum << " " << secondNum << endl;
                adjList[firstNum]->push_front(secondNum);
                
            }
            inputFile.close();

            
            //cout << adjList[6]->frontNode()->getNext()->getData() << endl;
            
        }










        int shortestPath(int source, int destination){

            //Breadth First Search 

            //load source vertex into queue
            Queue<int>* bfsQueue = new Queue<int>;
            bfsQueue->Enqueue(source);
            visited[source] = true;
            distTo[source] = 0;

            //everytime you dequeue an element, add all vertexes that point from that vertex into queue
            while (!bfsQueue->IsEmpty()) {
                int v = bfsQueue->Dequeue();

                Node<int>* currentNode = adjList[v]->frontNode();
                while (currentNode != nullptr) {
                    int neighbor = currentNode->getData();
                    if (!visited[neighbor]) {
                        bfsQueue->Enqueue(neighbor);
                        visited[neighbor] = true;
                        edgeTo[neighbor] = v;
                        distTo[neighbor] = distTo[v] + 1;
                }
                currentNode = currentNode->getNext();
            }
        }


        //return the correct distance
        return distTo[destination]; 
            
    

        }



        

};