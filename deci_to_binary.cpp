#include <iostream>
using namespace std;


int decToBinary(int n)
{
    int binaryNum[8];
    int a=0;
    for (int i = 3; i >= 0; i--) {
        int k = n >> i;
        cout<<k<<endl;
        /*k & 1 does a bitwise AND operation of the k variable and the 1 literal. The expression results in either 0 (if the LSB of k is 0) or 1 (if the LSB of k is 1). As the expression is the condition for the if statement, it is implicitly cast to bool, for which 1 maps to true and 0 maps to false.*/
        if (k & 1){
                cout<<"a= "<<a<<endl;
           binaryNum[a]=1;
           a++;
        }
        else{
            binaryNum[a]=0;
            a++;
        }
    }

    for(int j=0 ;j<4;j++)
    {
        cout<<binaryNum[j];
    }

}
/*int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

int binaryToDecimal(int n)
{
    int num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return dec_value;
}

// Driver program to test above function
int main()
{
    int num = 10101001;

    cout << binaryToDecimal(num) << endl;
}
*/

int main()
{
    int n = 12;
    decToBinary(n);
}
