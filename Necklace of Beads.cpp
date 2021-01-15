#include<iostream>
#include<algorithm>
 
#define endl '\n'
#define lli long long int
#define forn(i,n) for (int i = 0; i < n; i++)
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


using namespace std;


lli binPow(lli a, lli b)
{
    lli res = 1; 
    while(b)
    {
        if(b&1) res = (1LL*res*a);
        b>>=1;
        a = (1LL*a*a);
    }
    return res;
}

int main () {
	fastIO();
    
    while (true)
    {
        lli n, k=3; cin>>n; if(n==-1) break;
        if(n<=0) 
        {
            cout << 0 << endl; continue;
        }
        lli suma = 0;
        for(lli i = 0; i<n; i++)
        {
            suma += binPow(k, __gcd(i, n));
        }
        if(n%2 == 0)
            suma += (n/2) * binPow(k, n/2) * (k+1);
        else
            suma += n*binPow(k, (n+1)/2);
        cout << suma/(2*n) << endl;
    }
    
	return 0;
}