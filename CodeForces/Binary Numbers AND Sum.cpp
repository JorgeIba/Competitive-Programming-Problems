#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli binPow(lli a, lli b, lli MOD)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = (res*a)%MOD;
        b >>=1;
        a =(a*a)%MOD;
    }
    return res;
}

int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    string sa, sb; cin>>sa>>sb;
    lli maxSize = max(n,m);
    vector< lli > a(maxSize);
    vector< lli > b(maxSize);
    
    for(int i = maxSize-n; i<maxSize; i++)
    {
        a[i] = sa[i-maxSize+n] - '0';
    } 
    for(int i = maxSize-m; i<maxSize; i++)
    {
        b[i] = sb[i-maxSize+m] - '0';
    } 

    vector<lli> sumas(maxSize);
    sumas[0] = b[0];
    for(int i = 1; i<maxSize; i++)
    {
        sumas[i] = sumas[i-1] + b[i];
    }
    vector< lli > potencias(maxSize);
    for(int i = maxSize-1; i>=0; i--)
    {
        if(a[i])
            potencias[i] = sumas[i];
    }
    const lli MOD = 998244353;
    lli power = 0, suma = 0;
    for(int i = maxSize-1; i>=0; i--)
    {
        suma = (suma + binPow(2, power, MOD)*potencias[i])%MOD;
        power++;
    }
    cout << suma << endl;
    return 0;
}