#include<iostream>
#include<math.h>
using namespace std;
int n[4];

int main()
{
	unsigned long i,num=0,d;
	cout<<"Enter any Binary number:";
	for(int i=0; i<4 ;i++)
	{
	    cin>>n[i];
	}


	for(i=0;n[4]!=0;++i)
	{
	d=n[4]%10;
	num=(d)*(pow(2,i))+num;
	n[4]=n[4]/10;
	}

	cout<<num;
	return 0;
}
