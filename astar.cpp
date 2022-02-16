#include<bits/stdc++.h>
#include<vector>

using namespace std;


vector <int> path_store;
vector <int> dist;
vector <int> Heuristic;

int total_Node;

struct Priority_Queue
{
    int Node,dis;
    bool flag;
} Q[100];

struct node
{
    int nd;
    int weight;
} temp;

vector <node>adj[100];

void show_path(int start, int dest)
{


    if(dest==start)
    {
        return;
    }

    else
    {
        show_path(start,path_store[dest]);
    }

    cout<<dest<<" ";
}


bool If_Visited()
{
    for(int i=0; i<total_Node; i++)
    {
        if(Q[i].flag==true)
        {

            return true;

        }
    }

    return false;
}

int min_distance()
{
    int minimumValue = INT_MAX;
    int minimumIndex;
    for(int i=0; i<total_Node; i++)
    {
        if(Q[i].dis<minimumValue && Q[i].flag==true)
        {
            minimumValue = Q[i].dis;
            minimumIndex = i;

        }
    }

    return minimumIndex;
}


void A_str_srch(int src)
{

    int path;
    Q[src].dis=0;
    dist[src] = 0;
    while(If_Visited())
    {
        path = min_distance();


        Q[path].flag = false;

        for(int i=0; i<adj[path].size(); i++)
        {

            temp = adj[path][i];

            if(dist[temp.nd]>dist[path]+temp.weight)
            {
                dist[temp.nd]=dist[path]+temp.weight;
                Q[temp.nd].dis = dist[temp.nd]+Heuristic[temp.nd];
                path_store[temp.nd] = path;

            }
        }
    }
}

int main()
{
    int nde,edges,u,v,wt,start,dst,heur;
    cout<<"Enter the total nodes and edges value : ";
    cin>>total_Node>>edges;
    cout<<"Enter directed nodes from to where along with the weight : "<<endl;
    for(int i=0; i<edges; i++)
    {
        cin>>u>>v>>wt;
        temp.nd=v;
        temp.weight = wt;
        adj[u].push_back(temp);
        temp.nd = v;
        adj[v].push_back(temp);
    }
    for(int i=0; i<total_Node; i++)
    {
        Q[i].Node=i;
        Q[i].dis = INT_MAX;
        Q[i].flag = true;
        path_store.push_back(INT_MAX);
        dist.push_back(INT_MAX);
        cout<<"Input Heuristic cost of : "<<i<<" : ";
        cin>>heur;
        Heuristic.push_back(heur);
    }

    cout<<"Source & destination node :";
    cin>>start>>dst;
    A_str_srch(start);

    cout<<"Showing Path: ";
    cout<<start<<" ";
    show_path(start,dst);
    cout<<"\nTotal Weight is : ";
    for(int i=0; i<total_Node; i++)
    {
        if(i==dst)
            cout<<Q[i].dis<<" ";

    }
    cout<<endl;
}

/*
7 10
0 1 5
0 2 10
1 2 2
1 4 1
2 5 4
3 1 1
3 4 4
4 5 3
6 3 2
6 0 3
Input Heuristic cost of : 0 : 9
Input Heuristic cost of : 1 : 4
Input Heuristic cost of : 2 : 2
Input Heuristic cost of : 3 : 5
Input Heuristic cost of : 4 : 3
Input Heuristic cost of : 5 : 0
Input Heuristic cost of : 6 : 7

source 6 destination 5

ans: path:6 3 1 4 5
     weight : 7
*/