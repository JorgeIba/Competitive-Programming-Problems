#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const long long int MOD = 1e9 + 7;

lli binPow(lli a, lli e)
{
    lli res = 1;
    a = a%MOD;
    while(e)
    {
        if(e&1) res = (res*a)%MOD;
        e >>= 1;
        a = (a*a)%MOD;
    }
    return res%MOD;
}

lli inverse = binPow(2LL, MOD-2);

lli Gauss(lli n)
{
    n = n%MOD;
    lli aux = (n*(n+1))%MOD;
    lli aux2 = (aux*inverse)%MOD;
    return aux2;
}


vector< lli > num;
vector< lli > pot;

void getNum(lli n)
{
    num.clear();
    while(n)
    {
        num.push_back((n % 7LL));
        n /= 7LL;
    }
    reverse(all(num));
}


lli fun()
{
    lli suma = 0, aux =1;
    for(int i = 0; i<num.size()-1; i++)
    {
        lli digit = num[i];
        lli powA = pot[ num.size() - (i+1) ]%MOD;
        suma = (suma + (((aux)*Gauss(digit)%MOD)*powA)%MOD   )%MOD;
        aux = (aux*(digit+1))%MOD;
    }
    lli digit = num[ num.size()-1 ];
    return (suma + aux*Gauss(digit+1))%MOD;
}

void prec()
{
    pot.clear(); pot.resize(100);
    for(lli i = 0; i<100; i++)
    {
        pot[i] = binPow(28LL, i);
    }
}


void solve(int t)
{
    unsigned lli n; cin>>n;
    assert(n>=0);
    if(n == 0LL)
    {
        cout << "Case "<< t << ": "<< 0;
        return;
    }
    getNum(n);
    
    lli total = Gauss(n+1);
    lli zeros = fun();


    lli res = (lli)((total - zeros)%MOD)%MOD;
    //cout<< (total)<< " "<<zeros<<endl;
    if(res < 0) res += MOD;
    assert(res>=0 && res<MOD);
    cout << "Case "<< (int)t << ": "<< (res)%MOD;
    return;
}

int main()
{
    fastIO();
    prec();
    
    lli t; cin>> t;
    for(int i = 1; i<=t; i++)
    {
        solve(i);
        if(i<t) cout << endl;
    } 
    
    return 0;
}