#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include<vector>
using namespace std ;
/* y_pred = w0x0 + w1x1 + w2x2 + w3x3*/
int m;
double a = 0.01, input[100];
vector<float>w , y_pred, slop, y, x[100];


void linearRegression(int feature, int m){
    for(int i = 0 ; i < m ; i++)
    {
        float cal = 0.0 ;
            for(int j = 0 ; j <= feature ; j++){
            cal += w[j]*x[j][i] ;
        }
        y_pred.push_back(cal) ;
    }
}
void findSlop(int feature, int m)
{

    for(int i = 0 ; i <= feature ; i++)//
    {
        float temp = 0.0 ;
        for(int j = 0 ; j <m ; j++){
            temp += (y_pred[j] - y[j]) * x[i][j] ;
        }
        slop.push_back(temp) ;
    }
}

void findNewW(int feature, int m )
{
     for(int i = 0 ; i <= feature ; i++){
            w[i]= w[i] - a* slop[i];
     }
}
void prediction(int feature)
{
    double temp;
     for(int i = 0 ; i <= feature ; i++){
            temp += w[i]*input[i];
     }
     cout<<endl<<" \tThe predicted rent will be : "<<temp<<endl;

}

int main()
{
    fstream newfile;
    m = 0 ;
    int feature = 3 ;
    cout<< "Number of feature : "<< feature << endl<<endl;
    //cin>> feature ;
    newfile.open("dataRegression.txt",ios::in);
    if(newfile.is_open()){
        string str ;
        while(getline(newfile, str)){
        m++ ;
        stringstream check1(str);
        string intermediate;
        int i = 1 ;
        for(int k = 0 ; k < m ; k++)
        x[0].push_back(1) ;

            while(getline(check1, intermediate, ','))
            {
                float val = atof(intermediate.c_str()) ;
                if(i<=feature){

                    x[i].push_back(val) ;
                    i++ ;
                }
                else{
                    y.push_back(val) ;
                }
            }
        }

        newfile.close() ;
    }
    cout<<"total data in testing : "<< m << endl<<endl ;
    for(int i = 0 ; i <= feature ; i++){
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        w.push_back(r) ;
    }
    cout<< "Initial value of W : " ;
    for(int i = 0 ; i <= feature ; i++){
        cout << w[i] << " " ;
    }
    cout<< endl<<endl ;
   linearRegression(feature, m) ;
   findSlop(feature, m) ;
   findNewW(feature, m ) ;
   cout<< "Learn value of W : " ;
    for(int i = 0 ; i <= feature ; i++){
        printf("%f ", w[i]) ;
    }
    cout<< endl<<endl ;

    cout<<"Enter flat_size, room_no and availability of lift(0/1) for predicted rent :  ";
    input[0]=1;
     for(int i = 1 ; i <= feature ; i++){
            cin>>input[i];
            if(i==feature){
               if(input[i]!= 0 && input[i] != 1)
            {
                cout<<"\tEnter valid input for lift 0 or 1 !!!!!"<<endl;
                return 0;
            }
            }
     }
    prediction(feature);

}

