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


lli n, m; 
vector<vector<lli>> allAns;
void dfs(int idx, int num, vector<lli> ans){
    if(idx == n) {
        allAns.push_back(ans);
        return;
    }

    for(int d = num+1; d <= m; d++) {
        auto c_ans = ans;
        c_ans.push_back(d);
        dfs(idx+1, d, c_ans);
    }

}


int main () {
	//fastIO();

    cin>>n>>m;

    vector<lli> ans;
    dfs(0, 0, ans);


    for(auto v: allAns) {
        for(auto x: v) {
            cout << x << " ";
        }
        cout << endl;
    }

	return 0;
}

