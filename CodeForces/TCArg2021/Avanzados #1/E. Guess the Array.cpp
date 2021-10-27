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


lli query(lli i, lli j)
{
    cout << "? " << i << " " << j << endl;
    cout.flush();
    lli sum; cin>>sum;
    return sum;
}


int main () {
	fastIO();
    lli n; cin>>n;

    vector<lli> ans(n+1);

    lli a12 = query(1,2);
    lli a13 = query(1,3);
    lli a23 = query(2,3);

    lli a2 = (a12 - a13 + a23);
    assert(a2 % 2 == 0);
    a2 /= 2;
    lli a1 = a12 - a2;
    lli a3 = a23 - a2;

    ans[1] = a1; ans[2] = a2; ans[3] = a3;
    for(int i = 4; i<= n; i++)
    {
        lli sum = query(i-1, i);
        ans[i] = sum - ans[i-1];
    }

    cout << "! ";
    for(int i = 1; i<=n; i++) cout << ans[i] << " ";
    cout << endl;


	


	return 0;
}

