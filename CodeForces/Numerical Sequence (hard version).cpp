#include <bits/stdc++.h>

#define lli long long int
#define LL __int128
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

LL evalK(LL n)
{
    return n*(n+1)/2;
}

lli evalD(lli k)
{
    return (pow(10, k)*(9*k -1) + 1) / 9;
}

lli solveDigit(lli possition)
{
    if(possition <= 9) return possition;
    lli l = 1, r = 9, d=-1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( evalK(mid)  <= possition )
        {
            d = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    lli lower = evalD(d);
    lli residue = possition - lower;
    lli power = pow(10, d);
    lli number = power + (residue / (d+1));
    if(residue%(d+1) == 0)
    {
        number--;
        return number % power;
    }
    else
    {
        string aux = to_string(number);
        return aux[residue%(d+1) - 1] - '0';
    }
}
void solve()
{
    lli k; cin>>k;
    LL l = 1, r = 2*(1e9), n = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( evalK(mid) <= (LL)k )
        {
            n = mid;
            l = mid + 1;
        }
        else 
        {
            r = mid - 1;
        }
    }
    LL lower = (n*(n+1)) / 2;
    lli falta = k - lower;
    //cout << falta << endl;
    cout << solveDigit(falta) << endl;
    
}

int main()
{
    //fastIO();
    lli q; cin>>q;
    while(q--) solve();
    return 0;
}