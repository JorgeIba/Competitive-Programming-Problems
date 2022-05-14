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


lli binPow(lli a, lli b, lli mod)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}




int main () {
	fastIO();
    lli t; cin>>t;

    while(t--)
    {
        string s; cin>>s;
        reverse(all(s));
        VLL ans;
        for(int n = 2; n <= 6; n++)
        {
            lli sum = 0;
            for(int i = 0; i<SZ(s); i++)
            {
                sum += binPow(10, i, n) * (s[i] - '0') % n;
                sum %= n;
            }
            if(sum == 0)
            {
                ans.push_back(n);
            }
        }
        if(SZ(ans))
        {
            for(int i = 0; i<SZ(ans); i++)
            {
                cout << ans[i];
                if(i < SZ(ans) - 1) cout << " ";
            }
            for(auto x: ans) cout << x << " ";
            cout << endl;
        }
        else
        {
            cout << -1 << endl;
        }
        


    }
	


	return 0;
}

