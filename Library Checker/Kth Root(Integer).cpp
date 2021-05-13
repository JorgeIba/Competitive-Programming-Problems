#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define i128 __int128

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

#define ull unsigned long long

i128 power(i128 a, lli b)
{
    i128 res = 1;
    while(b)
    {
        if(b&1) res = res * a;
        b>>=1;
        a = a*a;
    }
    return res;
}


ull maxA = -1;

int main () {
	fastIO();
    lli t; cin>>t;

    while(t--)
    {
        ull A, K; cin>>A>>K;
        i128 l = 1, r = maxA, ans = 0;
        while(l<=r)
        {
            i128 mid = (l+r)/2;

            bool flag = true;

            i128 aux = 1;
            for(i128 k = 1; k<=K; k++)
            {
                aux *= mid;
                if(aux > A)
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                ans = mid;
                l = mid+1;
            } 
            else
            {
                r = mid-1;
            }
        }
        cout << (ull) ans << endl;
    }

	return 0;
}