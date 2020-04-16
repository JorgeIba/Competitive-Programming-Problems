#include<bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define MOD 11092019

using namespace std;

string cadena;


int main()
{
    cin>>cadena;
    map<char,lli> frequency;
    for(int i=0; i<cadena.length(); i++)
    {
        frequency[  cadena[i] ]++;

    }
    lli res = 1;
    for(auto x: frequency)
    {   
        res = res*(x.second+1) % MOD;
    }

    cout<<res<<endl;

    return 0;
}