#include <bits/stdc++.h>
#include<cstdlib>
#include<vector>

using namespace std;

int binaryNum[6][8];

struct chromosome
{
    int a, b;
    double fitness ;
    vector<int>prob ;
} temp, dvalue[6], par[6] ;


int f(int a, int b)
{
    return 2*a*a + 3*b - 38 ;
}
void calculateFitness()
{
    for(int i = 0 ; i < 6 ; i++)
    {
        int fVal = abs(f(dvalue[i].a, dvalue[i].b)) ;
        dvalue[i].fitness = 1.00/fVal ;
        cout<<dvalue[i].fitness<<endl;
    }
}
void copyToPar(int x, int y)
{
    par[y].a = dvalue[x].a ;
    par[y].b = dvalue[y].b ;

}
void chooseParent()
{
    for(int i = 0 ; i < 6 ; i++)
    {
        for(int j = 0 ; j < 6 ; j++)
        {
            if(dvalue[i].fitness < dvalue[j].fitness)
            {
                swap(dvalue[i], dvalue[j]);
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++)
    {
        dvalue[i].prob.push_back(i) ;
    }
    dvalue[0].prob.push_back(6) ;
    dvalue[0].prob.push_back(7) ;
    dvalue[1].prob.push_back(8) ;

    int cur = 0 ;
    for(int i = 0 ; i < 6 ; i++)
    {
        int randVal = rand() % 9 ;
        if(randVal == 0 || randVal == 6 || randVal == 7)
        {
            copyToPar(0, i) ;
        }
        else if(randVal == 1 || randVal == 8)
        {
            copyToPar(1, i) ;
        }
        else if(randVal == 2)
        {
            copyToPar(2, i) ;
        }
        else if(randVal == 3)
        {
            copyToPar(3, i) ;
        }
        else if(randVal == 4)
        {
            copyToPar(4, i) ;
        }
        else if(randVal == 5)
        {
            copyToPar(5, i) ;
        }
    }
}

void crossOver()
{
    for(int z=0; z<6 ; z++)
    {

        int q=0;
        for (int i = 3; i >= 0; i--)
        {
            int k = par[z].a >> i;
            if (k & 1)
            {
                binaryNum[z][q] = 1;
                q++;
            }
            else
            {
                binaryNum[z][q]=0;
                q++;
            }

        }

        for (int i = 3; i >= 0; i--)
        {
            int k = par[z].b >> i;
            if (k & 1)
            {
                binaryNum[z][q]= 1;
                q++;
            }
            else
            {
                binaryNum[z][q]=0;
                q++;
            }
        }

    }
    cout<<"before crossover :"<<endl;
    for(int j=0 ; j<6 ; j++)
    {
        for(int i=0; i<8 ; i++)
        {
            cout<<binaryNum[j][i];
        }
        cout<<endl;
    }

    for(int j=0 ; j<5 ; j=j+2)
    {
        int r = (rand() % 5)+1;

        cout<<"cross over point : "<<r<<endl;
        for(int i=r; i<8 ; i++)
        {
            swap(binaryNum[j][i], binaryNum[j+1][i]);
        }
    }

    cout<<"after crossover :"<<endl;
    for(int j=0 ; j<6 ; j++)
    {
        for(int i=0; i<8 ; i++)
        {
            cout<<binaryNum[j][i];
        }
        cout<<endl;
    }
    cout<<endl;



}
void mutation()
{
    float mutation_rate = 0.1;
    int p,q, x, y, d;
    int m = abs(6*8*mutation_rate);
    for(int i=0 ; i<m ; i++)
    {
        p= rand() % 6 ;
        q= rand() % 8 ;
        if(binaryNum[p][q]==0)
        {
            binaryNum[p][q]=1;
        }
        else
        {
            binaryNum[p][q]=0;
        }
    }


    cout<<"after mutation :"<<endl;
    for(int j=0 ; j<6 ; j++)
    {
        for(int i=0; i<8 ; i++)
        {
            cout<<binaryNum[j][i];
        }
        cout<<endl;
    }


    for(int j=0 ; j<6 ; j++)
    {
        d=8;
        x=0;
        y=0;
        for(int i=0; i<4 ; i++)
        {
            if(binaryNum[j][i]==1)
            {
                x=x+d;
                d=d/2;
            }
            else
            {
                d=d/2;
            }
        }
        dvalue[j].a= x;
        d=8;
        for(int i=4; i<8 ; i++)
        {
            if(binaryNum[j][i]==1)
            {
                y=y+d;
                d=d/2;
            }
            else
            {
                d=d/2;
            }
        }
        dvalue[j].b=y;
    }


    cout<< "new a & b :"<<endl;
    for(int i = 0 ; i < 6 ; i++)
    {

        cout<<dvalue[i].a<<" ";
        cout<<dvalue[i].b<<endl;
    }
    cout<<endl<<endl;


}
int main()
{
    int i, j ;
    for(i = 0 ; i < 6 ; i++)
    {
        int x = rand() % 10 ;
        int y = rand() % 10 ;
        dvalue[i].a = x ;
        dvalue[i].b = y ;
        dvalue[i].fitness = 0 ;
    }

    for(i = 0 ; i < 100 ; i++)
    {
        cout<<"Iteration: "<< i<<"\n" ;


        for(j = 0 ; j < 6 ; j++)
        {
            if(f(dvalue[j].a, dvalue[j].b) == 0)
            {
                cout<<"Solution :"<<dvalue[j].a<< " "<<dvalue[j].b<<"\n" ;
                return 0;
            }
            calculateFitness() ;
            chooseParent() ;
            crossOver() ;
            mutation() ;
        }
    }

}
