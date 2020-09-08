#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

vector<lli> digits;



int main()
{
    lli n; cin>>n;

    while(n>0)
    {
        lli aux = n%10;
        digits.push_back(aux%3);
        n/=10;
    }

    

    return 0;
}