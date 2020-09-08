#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int numberSolutions(lli p)
{
    int solutions = 0;
    for(lli d1 = 1; d1*d1<=(p*p / 2); d1++) // Looking for divisors
    {
        if((p*p / 2) % d1 == 0) //checking if d1 is divisor of p*p / 2
        {
            lli d2 = (p*p/2) / d1;
            lli a = p - d2, b = p-d1;
            if( (p-a)*(p-b) == (p*p)/2 && a > 0 && b > 0) // If 'a' and 'b' satisfy the equation
            {
                solutions++;
            }
        }
    }
    return solutions;
}

int main()
{
    int maximum = -1, ans = -1;
    for(int p = 2; p<=10000; p+=2)
    {
        int possible = numberSolutions(p);
        if(possible > maximum)
        {
            maximum = possible;
            ans = p;
        }
    }
    cout << ans << " " << maximum << endl;

    return 0;
}