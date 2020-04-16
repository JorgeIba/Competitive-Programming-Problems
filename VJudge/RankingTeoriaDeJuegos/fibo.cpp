#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

vector<lli> fibo(32);

int main()
{
    fibo[0] = fibo[1] = 1;
    for(int i = 2; i<32; i++)
    {
        fibo[i] = fibo[i-1] + fibo[i-2];
    }
    for(auto x: fibo)
    {
        cout<<x<<" ";
    }
    return 0;
}