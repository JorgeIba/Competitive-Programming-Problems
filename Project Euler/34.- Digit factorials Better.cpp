#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int fact[10];

void prec()
{
    fact[0]=fact[1] = 1;
    for(int i = 2; i<=9; i++)
        fact[i] = i * fact[i-1];
}

int sumDigitsFactorial(lli n)
{
    lli suma = 0;
    while(n)
    {
        suma += fact[n%10];
        n/=10;
    }
    return suma;
}


int main()
{
    prec();

    for(int i = 1; i<=2177280; i++)
    {
        if(sumDigitsFactorial(i) == i)
        {
            cout<<i<<endl;
        }
    }

    return 0;
}
