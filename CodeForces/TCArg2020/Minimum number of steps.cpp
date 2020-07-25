#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9+7;

lli binPow(lli a, lli b)
{
    lli res = 1;
    a = a%MOD;
    while(b)
    {
        if(b&1) res = (res*a)%MOD;
        b>>=1;
        a = (a*a)%MOD;
    }
    return res;
}

int main()
{
    fastIO();
    string s; cin>>s;
    lli countPower = 0, n = s.length();
    lli suma = 0;
    for(int i = 0; i<n; i++)
    {
        if(s[i] == 'a')
        {
            countPower++;
        }
        else
        {
            suma = (suma + binPow(2, countPower) - 1)%MOD;
            if(suma < 0) suma += MOD;
        }
    }
    cout << suma << endl;
    return 0;
}