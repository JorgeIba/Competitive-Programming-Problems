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
 
VI digits;
int n;

VI getDigits(lli num) 
{
    VI digits;
    while(num)
    {
        digits.push_back(num%10);
        num/=10;
    }
    return digits;
}


lli fun(lli idx, bool canAll, bool legal, lli r)
{
    if(idx >= r)
    {
        return legal;
    }

    int digit = digits[idx];
    int limit = canAll ? 9 : digit;
    lli ans = 0;
    for(int d = 0; d<=limit; d++)
    {
        if(d < limit)
        {
            ans += fun(idx+1, true, true, r-1);
        }
        else // d == limit
        {
            if(digits[r]  < d)
            {
                ans+= fun(idx+1, canAll | (d < limit), legal, r-1);
            }
            else
            {
                ans+= fun(idx+1, canAll | (d < limit), legal, r-1);
            } 
        }   
    }
    return ans;
}





lli f(lli num)
{
    if(num <= 0) return 0;
    digits = getDigits(num);
    n = SZ(digits);
    //memset(dp, -1, sizeof(dp));
    return fun(0, false, false, n-1);
}


void solve()
{
    lli l, r; cin>>l>>r;
    if(l>r) swap(l,r);
    cout << f(r) - f(l-1) << endl;
}

int main () {
	//fastIO();
    lli l, r; cin>>l>>r;
    //cout << f(l) << " " << f(r) << endl;
    cout << f(r) << endl;
    //int t; cin>>t;
    //while(t--) solve();
 
	return 0;
}