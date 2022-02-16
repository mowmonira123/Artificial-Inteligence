#include<bits/stdc++.h>

using namespace std;

#define V 5


int minD(int dist[], bool Set[])
{

    int min = INT_MAX;
    int min_index;

    for (int v = 0; v < V; v++)
        if (Set[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}


void printS(int dist[], int fin)
{
    cout<<"Vertex \t\t Distance from Source\n";

        cout<<fin <<"\t\t"<<dist[fin]<<"\n"<<endl;
}


void dijk(int graph[V][V], int src, int fin)
{
    int dist[V];

    bool Set[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, Set[i] = false;


    dist[src] = 0;


    for (int count = 0; count < V - 1; count++) {

        int u = minD(dist, Set);


        Set[u] = true;


        for (int v = 0; v < V; v++)


            if (!Set[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printS(dist,fin);
}


int main()
{

   int i, j, src, fin, graph[V][V];
    cout<<"the matrix is"<<"  "<<V<<"*"<<V<<"  "<<endl;

    cout<<"enter the grid" <<endl;
    for(i = 0 ; i < V ; i++){
        for(j = 0 ; j < V ; j++){
            cin>>graph[i][j] ;
        }
    }
    cout<<"enter the starting location"<<endl;
    cin>>src;

    cout<<"enter the finishing location"<<endl;
    cin>>fin ;



    dijk(graph,src,fin);

    return 0;
}
