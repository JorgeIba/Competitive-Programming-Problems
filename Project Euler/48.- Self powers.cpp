#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const lli MOD = 1e11;

lli binMul(lli a, lli b)
{
    lli res = 0;
    while(b)
    {
        if(b&1) res = (res+a)%MOD;
        b>>=1;
        a = (a+a)%MOD;
    }
    return res;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = binMul(res,a);
        b>>=1;
        a = binMul(a,a);
    }
    return res;
}


int main () {
	//fastIO();
    
    lli n; cin>>n;
    lli sum = 0;

    for(int i = 1; i<=n; i++)
    {
        sum = (sum + binPow(i,i))%MOD;
    }
    cout << sum << endl;

    
	return 0;
}