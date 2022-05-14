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
    lli n, k; cin>>n>>k;
    vector<lli> clients(n);
    for(auto &x: clients) cin>>x;


    deque<lli> dq;

    lli ans_l = -1, ans_r = -1, ans = 0;

    lli total = 0;
    

    for(int i = 0; i<n; i++)
    {
        dq.push_back(clients[i]);
        total += clients[i];

        while(!dq.empty() && k + total < 0)
        {
            lli last = dq.front();
            total -= last;
            dq.pop_front();
        }

        if(k + total >= 0) 
        {
            lli sz = SZ(dq);
            
            if(sz > ans)
            {
                ans = sz;
                ans_r = i;
                ans_l = i - SZ(dq) + 1;
            }
        }
    }

    if(ans == 0)
    {
        cout << -1 << endl;
    } 
    else
    {
        assert(ans_l+1 >= 1 && ans_r+1 >= 1);

        cout << ans_l+1 << " " << ans_r + 1 << endl;
    } 
}


int main () {
	fastIO();

    lli t; cin>>t;

    while(t--) solve();
	


	return 0;
}

