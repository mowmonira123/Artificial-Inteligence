#include <bits/stdc++.h>
#define ld long double
#define ROW 4
#define COL 6


using namespace std;

int c = 0 ;
int t_cost = 0;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int grid[ROW][COL] =
{
    {0, 4, 0, 8, 0, 0},
    {4, 6, 3, 2, 0, 8},
    {0, 0, 7, 3, 4, 7},
    {0, 2, 9, 1, 2, 1}
};
/*{0, 3, 4, 1, 0, 0},
    {4, 6, 0, 2, 0, 8},
    {0, 1, 7, 0, 1, 7},
    {0, 2, 3, 1, 7, 3}*/



int sol_grid[ROW][COL];



struct Priority_Queue
{
    int x, y;
    ld Cost;
    bool flag;
} pQ[4];                             ///Only need to store 4 elements at a time. Top, Right, Bottom and Left co-ordinate


void reset_priority_queue()
{
    for(int i = 0; i < 4; i++)     /// as there are only 4 elements
    {
        pQ[i].x = -1;
        pQ[i].y = -1;
        pQ[i].Cost = INT_MAX;           // setting the co-ordinate as invalid or null
        pQ[i].flag = true;
    }
}



int minimum_cost(int d1,int d2)
{
    double minv = INT_MAX;
    int min_cost = -1;

    for(int i=0; i<4; i++)
    {
        if(pQ[i].x== d1 && pQ[i].y==d2)
        {
            pQ[i].flag = false;
            return i;
        }

        if(pQ[i].Cost<minv && pQ[i].flag==true )
        {

            minv = pQ[i].Cost;
            min_cost = i;

        }
    }

    pQ[min_cost].flag = false;
    return min_cost;
}



ld cal_GndH_Value(int row, int col, int fin1, int fin2)
{

    return (grid[row][col] + ((double)sqrt(
                                  (row - fin1) * (row - fin1)
                                  + (col - fin2) * (col - fin2))));
}



bool ValidCheck(int x, int y)
{

    if(x >= 0 && x < ROW && y >= 0 && y < COL && grid[x][y] >0 )
    {

        return true;                     // our goal is to find if any node's flag is set to false
                                         // Bcz it will mean there is still a node in the queue
                                // if we find a node which flag is set to true
                                // we immediately terminate and return the value
    }

    return false;             // So if the queue is empty this function will return yes (false)
}



bool aStarSearch(int x,int y, int d1,int d2)
{

    if (ValidCheck(x, y) == false && c==0)
    {
        cout<<"Source is invalid\n\n";
        return false;
    }

    if (ValidCheck(d1, d2) == false && c==0) {
		cout<<"Destination is 0 or invalid!!!!\n";
		return false;
	}

    t_cost = t_cost+grid[x][y];

    reset_priority_queue();              ///as for every current co-ordinate we are going to generate 4 new points, so,
                                ///we need to refresh or empty the priority queue every time, because we need to
                                ///delete previous 4 points that were stored in the queue currently.
                                ///after resetting the queue, we are going to store the new 4 points

    if(x == d1 && y == d2)      /// we have reached our goal co-ordinate
    {
        sol_grid[x][y] = grid[x][y];

        if(c==0)
        {
            cout<<"source and destination same\n\n";
        }

        return true;
    }

     //If we have not reached our goal co-ordinate yet, first check if we are in the right co-ordinate or not
    if(ValidCheck(x,y) == true)
    {
        sol_grid[x][y] = grid[x][y];                      //This co-ordinate is valid, so set the solution array as 1

        /// Now, we are going to check 4 points, TOP, DOWN, RIGHT, LEFT
        /// So, if the co-ordinates are valid we are going to calculate the heuristic or distance
        /// and store it in the priority queue.
        /// after storing the 4 neighbor, we are going to pick the least distant co-ordinate from the goal
        /// after that, we will set the current as this co-ordinate, that means we'll recursively call the function again


        for(int k=0; k<sizeof(dx) ; k++)
        {
            int i = x + dx[k];
            int j = y + dy[k];

            if(ValidCheck(i, j) == true && sol_grid[i][j] == 0 )    // Checking BOTTOM and also checking if the node is previously
        {                                                   // visited or not, if it is already visited then the
                                                            // corresponding solution grid value must be set to 1.
                                                            // So if it is already visited, we are not going to visit
                                                            // it again, because that node might be the parent node
                                                            // of current node, so if we allow this visit, the code will
                                                            //  fall into infinite loop. So we are only allowing unvisited
                                                            // node.
            pQ[k].x = i;
            pQ[k].y = j;
            pQ[k].flag = true;

            pQ[k].Cost = cal_GndH_Value(i, j, d1, d2);
        }

        }

        int index = minimum_cost(d1,d2);   // Selecting the index of minimum distant node from the queue


        x= pQ[index].x;          // Setting the x,y as the minimum distant node
        y = pQ[index].y;



        c=1;

        if(aStarSearch(x,y,d1,d2) == true)// Recursively calling the function
        {
             if(x==d1 && y==d2)
             {
                 cout<<"total cost will be : "<<t_cost<<endl;
             }

            return true;            // It means, if the right co-ordinate is the nearest from the
                                                    // goal, we are now at the right.
        }

        sol_grid[x][y] == 0;    // If all the above options have failed, that means we have

        return false;            // failed to reach the goal node with this path, so set all
                                                    // the path to 0 and return false

    }
    return false;
}






int main()
{

    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            sol_grid[i][j]=0;
        }
    }


    int source1,source2, destination1,destination2;

    cout << "Enter source: ";
    cin >> source1 >> source2;

    cout << "Enter destination: ";
    cin >> destination1 >> destination2;

    cout<<endl;

    bool result = aStarSearch( source1,source2, destination1,destination2);

    if(result == false)
    {
        cout << "\nPath Unavailable!!!!" << endl;
    }

    else
    {

        cout << "\nPath Available!!!\n\n" << endl;

        cout<<"Showing Path in grid : \n";

        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if(sol_grid[i][j]>0)
                {
                    cout <<"   " <<"("<<i<<","<<j<<")" << "   ";

                }
               else{
                cout << "     " << sol_grid[i][j] << "     ";
               }
            }

            cout << endl;
        }

    }

    cout << endl ;

    return 0;
}



