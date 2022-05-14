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
    lli n, m; cin>>n>>m;
    vector<string> dict(n);
    for(auto &x: dict) cin>>x;

    string original; cin>>original;


    map<string, array<lli,3> > subs;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            for(int k = 2; k <= 3 && j + k - 1 < m; k++)
            {
                subs[ dict[i].substr(j, k) ] = {j + 1, j+k, i + 1};
            }
        }
    }


    vector< array<lli, 4> > dp(m+1);
    for(auto &x: dp) x = {-1, -1, -1, -1};

    // dp[i] prefix upto i is ok

    const int finish = -10;
    dp[0] = {finish, finish, finish, finish};

    for(int i = 1; i <= m; i++)
    {
        for(int j = 2; j <= 3; j++)
        {
            lli index_l = i - j + 1;
            if(index_l < 1) continue;

            string substr = original.substr(index_l-1, j);
            if(!subs.count(substr)) continue;
            if(dp[index_l-1][0] == -1) continue;

            auto ans_substr = subs[substr];

            dp[i] = { ans_substr[0], ans_substr[1], ans_substr[2], index_l-1};
        }
    }

    if(dp[m][0] == -1){
        cout << -1 << endl;
    } else {
        vector< array<lli,3> > ans;
        lli curr = m;
        do{
            ans.push_back({dp[curr][0], dp[curr][1], dp[curr][2]});
            curr = dp[curr][3];
        }while(curr != 0);

        reverse(all(ans));


        cout << SZ(ans) << endl;
        for(auto x: ans) cout << x[0] << " " << x[1] << " " << x[2] << endl;
    }
}


int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

