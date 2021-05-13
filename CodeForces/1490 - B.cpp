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


void solve()
{
    int n; cin>>n;
    vector<lli> rems(3);
    for(int i = 0; i<n; i++)
    {
        int a_i; cin>>a_i;
        rems[a_i%3]++;
    }

    int target = n / 3;
    int ans = 0;


    for(int i = 0; i<=5; i++)
    {
        if(rems[i%3] > target)
        {
            int excedente = rems[i%3] - target;
            rems[i%3] = target;
            rems[(i+1)%3] += excedente;
            ans += excedente;
        }
    }

    cout << ans << endl;
}

int main () {
	fastIO();
    int t; cin>>t;
    while(t--) solve();

	return 0;
}