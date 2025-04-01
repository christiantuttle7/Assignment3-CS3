#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include "graph.h"

using namespace std;

void printLog(int[], ResizingArray<int>&, ResizingArray<int>&, ResizingArray<int>&, int);
int main(){

    
    graph mainGraph("inputConnections.txt");

    int sourceArray[3];
    int numSources = 3;
    int destination;
    ResizingArray<int> destinations;
    ResizingArray<int> shortestPaths;
    ResizingArray<int> shortestPathsTime;
    int shortestPath, shortestPathTime;

    //start program timer (credit to geek for geeks in the latex document)
    auto start = high_resolution_clock::now();

    //gets the three sources from user
    cout << "Enter Three Source: ";
    for(int i = 0; i < numSources; i++){
        cin >> sourceArray[i];
    }
    cin.ignore();

    //while loop that keeps asking user for a destination output until it recieves a -1
    //(it breaks from inside the loop)
    while(true){
        cout << "Destination " << destinations.getSize() +1 << ": ";
        cin >> destination;
        cin.ignore();
        

        if(destination == -1){
            
            break;
        }

        destinations.Push(destination);

        for(int i = 0; i < numSources; i++){
            //calculates shortest path from source -> destination

            shortestPath = mainGraph.shortestPath(sourceArray[i], destination);

            
            //gets the time it took to get that calculation
            shortestPathTime = mainGraph.getLastPathTime();


            //if the shortestPath == 1 it means no path was found in shorestPath()
            if(shortestPath == -1){
                cout << "Shortest Path from " << sourceArray[i] <<": No Path Found(" << 
                mainGraph.getLastPathTime() << " nanoseconds)" << endl;
                shortestPaths.Push(-1);

            } 
            else{
                cout << "Shortest Path from " << sourceArray[i] <<": " << shortestPath <<
                "( <"<< mainGraph.getLastPathTime()  << " nanoseconds)" << endl;
                cout << "Path: ";
                
                //print path
                mainGraph.printShortestPath(sourceArray[i], destination);

                shortestPaths.Push(shortestPath);
                
            }
            

            shortestPathsTime.Push(shortestPathTime);

            

        }
        
        cout << endl;
        
    }
    
    cout << endl;

    //print formatted log
    printLog(sourceArray, destinations, shortestPaths, shortestPathsTime, numSources);

    //stop timer and print out time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Program took: " << duration.count() << "seconds" <<  endl;


    std::cout << std::chrono::system_clock::now() << '\n';

    return 0;



    
}


void printLog(int sourceArray[], ResizingArray<int>& destinations, ResizingArray<int>& shortestPaths, 
ResizingArray<int>& shortestPathsTime, int numSources){
    cout <<setw(4) << "S  |" << setw(4) << "D  |" << 
    setw(4) << "Dist. |" << setw(4) <<"Time" << endl;
    cout << "-------------------------------" << endl;
    int resultIndex = 0;
    for( int i = 0; i < destinations.getSize(); i++){
        for(int j = 0; j < numSources; j++ ){
            if(shortestPaths.getValue(resultIndex) == -1){
                
                cout << sourceArray[j] << setw(5) << destinations.getValue(i) << setw(5) << "N/A" << 
                setw(10) << shortestPathsTime.getValue(resultIndex) << endl;

                
            }else{
                //cout << "Shortest Path from " << sourceArray[j] << " -> " << destinations.getValue(i) <<
                //": " << shortestPaths.getValue(resultIndex) << endl;
                cout << sourceArray[j] << setw(5) << destinations.getValue(i) << setw(5) <<
                shortestPaths.getValue(resultIndex)<< setw(10) << shortestPathsTime.getValue(resultIndex) << endl;
            }
            resultIndex ++;
        }
    }
}