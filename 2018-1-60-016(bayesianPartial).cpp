#include <bits/stdc++.h>
#include<vector>
#include <fstream>

using namespace std ;

vector<string>avalue ;
vector<string>cvalue ;

char a[100], c[100];

int numberofobject;


int findOccurance(string att, string cl)
{
    FILE *fptr;
    int count = 0 ;

    if ((fptr = fopen("data.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fptr, "%s %s", a, c)!= EOF)
    {
        string s = "" ;
        string s2 = "" ;

        for(int i = 0 ; i < strlen(a) ; i++)
        {
            s += a[i] ;
        }
        for(int i = 0 ; i < strlen(c) ; i++)
        {
            s2 += c[i] ;
        }
        if(s == att && s2 == cl)
            count++ ;
    }
    fclose(fptr);
    return count ;
}


int findOccurance2(string cl)
{
    FILE *fptr;
    int count = 0 ;

    if ((fptr = fopen("data.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fptr, "%s %s", a, c)!= EOF)
    {
        string s = "" ;
        string s2 = "" ;
        for(int i = 0 ; i < strlen(c) ; i++)
        {
            s2 += c[i] ;
        }
        if(s2 == cl)
            count++ ;
    }
    fclose(fptr);
    return count ;
}
void ac_value()
{
    numberofobject=0;
    FILE *fptr;
    if ((fptr = fopen("data.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    string s = "" ;
    while (fscanf(fptr, "%s %s", a, c)!= EOF)
    {

        numberofobject++ ;

        bool flag = false ;
        string s = "" ;
        for(int i = 0 ; i < strlen(a) ; i++)
        {
            s += a[i] ;
            /*char array is converted into string*/
        }
        for(int i = 0 ; i < avalue.size() ; i++)
        {
            if(s == avalue[i])
            {
                flag = true ;
                /*only hold the identical value of the attribute*/

            }
        }
        if(!flag)
        {
            avalue.push_back(s) ;
        }


        flag = false ;
        s = "" ;
        for(int i = 0 ; i < strlen(c) ; i++)
        {
            s += c[i] ;
        }
        for(int i = 0 ; i < cvalue.size() ; i++)
        {
            if(s == cvalue[i])
            {
                flag = true ;

            }
        }
        if(!flag)
            cvalue.push_back(s) ;



    }

    fclose(fptr);
}
void train_data()
{
    int m[100];

    ac_value();

    cout<<endl<<"Total data in data file : " <<numberofobject<<endl<<endl ;


    cout<<endl<<"Total class : "<<cvalue.size()<<endl<<endl;
    for(int i = 0 ; i < cvalue.size() ; i++)
    {

        cout<< "\t"<< cvalue[i] << endl ;
    }


    cout<<endl<<"Prior value: "<<endl;
    ofstream pr("prior.txt");

    for(int i = 0 ; i < cvalue.size() ; i++)
    {

        m[i] = findOccurance2(cvalue[i]) ;
        cout <<"\t"<<cvalue[i] <<"   " << (1.00*m[i]) / numberofobject<<endl ;
        pr<<cvalue[i]<<" "<<(1.00*m[i]) / numberofobject<<endl;

    }

    cout<<endl<<endl;

    cout<<"Total attribute : "<< avalue.size()<<endl<<endl;
    for(int i = 0 ; i < avalue.size() ; i++)
    {

        cout<< "\t"<< avalue[i] << endl ;
    }

    cout<<endl<<"Likelihood value :   "<<endl;

    ofstream lk("likelihood.txt" );

    for(int i = 0 ; i < cvalue.size() ; i++)
    {
        for(int j = 0 ; j < avalue.size() ; j++)
        {

            int n = findOccurance(avalue[j], cvalue[i]) ;
            double prob = (1.00*n) / m[i] ;
            cout <<"\t"<< avalue[j] <<" | "<< cvalue[i] << " "<< prob << endl ;
            lk<<avalue[j]<<" "<<cvalue[i]<<" "<<prob<<endl;

        }
    }
    cout<<endl<<endl<< "   Prior and likelihood file created successfully!!!   ";
    cout<< "\n\n\t THANK YOU \n\n "<<endl;


}


void predict_data()
{
    ifstream pvalue,lk_value;
    vector<pair<double,string> >ans_class;
    string attname[10],clname[10],clname1[10],user_att;
    double lkvalue[10],prior[10];
    bool flag= false;

    int att1 = 0, cll1 = 0,z;

    if(cvalue.size()== 0 )
    {
        cout<<"\tPlease Train this code first and select 0...!!!!!"<<endl<<endl;
        return;
    }

    cout<<endl<<"Please Follow The Attribute List :"<<endl;

    for(int q = 0 ; q < avalue.size() ; q++)
    {
        cout<<"( "<< q <<" )  :"<< avalue[q] << endl ;
    }

    cout<<endl<<"Enter The Attribute no. From attribute list : ";
    cin>>z;

    if( z > avalue.size()  )
    {
        cout<<"\n\n\tinvalid attribute number !!!\n\n"<<endl;
        return;
    }

    user_att= avalue[z];


    lk_value.open("likelihood.txt");

    while(!lk_value.eof())
    {
        lk_value>>attname[att1]>>clname[att1]>>lkvalue[att1];
        att1++;
    }


    pvalue.open("prior.txt");

    while(!pvalue.eof())
    {
        pvalue>>clname1[cll1]>>prior[cll1];
        cll1++;
    }


    for(int i=0; i<att1; i++)
    {
        for(int j=0; j<cll1; j++)
        {
            if(attname[i]== user_att && clname[i]==clname1[j] )
            {
                ans_class.push_back({lkvalue[i]*prior[j],clname[i]});
                flag = true;
            }
        }


    }
    sort(ans_class.begin(),ans_class.end());

    if(flag == true)
    {
        cout << "\n\n\tResult\n\n";
        cout<<"  The Class is --> "<<ans_class[ans_class.size()-1].second<<endl<<endl<<endl;
    }
}


int main()
{
    int x;

    while(true)
    {
        cout<<"Here, "<<endl;
        cout<<" press ( 0 ) to train this code. "<<endl;
        cout<<" press ( 1 ) to predict your class ."<<endl;
        cout<<" press ( 2 ) Close this code ."<<endl;
        cout<< endl<<"Enter the value : ";
        cin>>x;

        if(x==0)
        {
            train_data();
        }
        else if (x==1)
        {
            predict_data();

        }
        else if(x==2)
        {
            break;
        }

        else
        {
            cout<<endl<<"\tInvalid value.Try again...."<<endl<<endl;
        }

    }

}

