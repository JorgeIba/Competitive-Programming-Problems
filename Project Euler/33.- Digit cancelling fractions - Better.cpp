#include <bits/stdc++.h>
#define lli long long int

using namespace std;


// (10a + b)/(10b + c) == a/c
// c = 10ab/(9a+b)

int main()
{
    lli ans = 1;
    lli num = 1;
    for(int a = 1; a<=9; a++)
    {
        for(int b = 1; b<=9; b++)
        {
            if(10*a*b % (9*a + b) == 0)
            {
                int c = 10*a*b / (9*a + b);
                ans *= c;
                num *= a;
            }
        }
    }
    cout<< ans / (__gcd(num,ans))<<endl;

    return 0;
}