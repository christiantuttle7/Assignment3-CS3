#include "graph.h"

graph::graph(string inputFileName){
            //integer and char that will help read the file into the adjacency list
            int firstNum, secondNum;
            

            

            //opening file
            ifstream inputFile(inputFileName);
            if(!inputFile.is_open()){
                cerr << "Error opening File...termininating";
                exit(1);
            }

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


graph::~graph(){

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









int graph::shortestPath(int source, int destination){

            //Breadth First Search 

            //setting all bfs arrays to nothing
            for(int i = 0; i < numVertices; i++){
                visited[i] = false;
                edgeTo[i] = -1;
                distTo[i] = -1;//-1 represents infinity here
            }

            
            // queue from last calculation
            Queue<int> bfsQueue ;


            //starting the timer
            //credit to geeks for geeks for help with using chrono librarie for timing
            auto start = high_resolution_clock::now();

            //load source vertex into queue
        
            bfsQueue.Enqueue(source);
            visited[source] = true;
            distTo[source] = 0;

            //while loop that keeps going until we have found our destination vertex
            while (!bfsQueue.IsEmpty()) {
                
                //dequeueing next vertex
                int v = bfsQueue.Dequeue();

                if(visited[destination]){
                    break;
                }
                
                

                //going through list of connecting vertexes until there is no more
                for(int i = 0; i < adjList[v]->getSize(); i++) {

                    int neighbor = adjList[v]->getValue(i);

                    //updating all the information in the three arrays
                    if (!visited[neighbor]) {
                        bfsQueue.Enqueue(neighbor);
                        visited[neighbor] = true;
                        edgeTo[neighbor] = v;
                        distTo[neighbor] = distTo[v] + 1;
                    }
                }
            }

            //stopping timer
            auto stop = high_resolution_clock::now();
            //storing timer in public variable lastPathTime 
            auto duration = duration_cast<nanoseconds>(stop - start);
            lastPathTime = duration.count();
            


            if(!visited[destination]){
                //no path found, return -1 
                return -1;
            }


        


            //return the correct distance
            return distTo[destination]; 
            

}

int graph::getLastPathTime(){
    //returns last calculated time from bfs
    return lastPathTime;
}




void graph::printShortestPath(int source, int destination){

    
    //this will hold the path dest->source
    ResizingArray<int> path;
        
    //making sure the path has been calculated in the shortestPath() function
    if (!visited[destination] || distTo[source] != 0) {
        cout << "No path found or path not calculated\n";
        return;
    }




    //figure out the path edge by edge using edgeTo[] array
    int nextEdge = destination;

    while (nextEdge != source) {
        path.Push(nextEdge);
        nextEdge = edgeTo[nextEdge];
        if (nextEdge == -1) {
            cout << "Error in path reconstruction";
            return;
        }
    }
    path.Push(source); //push the edge into the array

    //print out the path (it was stored backwards)
    for (int i = path.getSize() - 1; i >= 0; i--) {
        cout << path.getValue(i) << "->";
    }
    cout << endl;
    
    return;
 }



        



