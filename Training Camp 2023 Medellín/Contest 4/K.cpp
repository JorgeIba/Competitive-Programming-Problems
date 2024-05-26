#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const int MAXN = 5e3 + 100;
lli nums[MAXN], pref[MAXN];

lli get_sum(int l, int r){
    return pref[r-1] - pref[l-1];
}

lli dp[MAXN][5];
bool visited[MAXN][5];
const lli INF = 1e18;
int n;
lli f(int idx, int move){
    if(move == 3) return -get_sum(idx, n+1);

    lli &ans = dp[idx][move];
    if(visited[idx][move]) return ans;
    visited[idx][move] = true;

    ans = -INF;
    for(int seg = idx; seg <= n+1; seg++){
        if(move == 0 || move == 2){
            ans = max(ans, get_sum(idx, seg) + f(seg, move+1));
        } else{
            ans = max(ans, -get_sum(idx, seg) + f(seg, move+1));
        }
    }

    return ans;
}


void rec(int idx, int move, vector<int> &ans_V){
    if(move == 3) return;

    lli ans = f(idx, move);
    
    for(int seg = idx; seg <= n+1; seg++){
        if(move == 0 || move == 2){
            lli poss = get_sum(idx, seg) + f(seg, move+1);
            if(ans == poss) {
                
                ans_V.push_back(seg);
                rec(seg, move+1, ans_V);
                return;
            }
        } else{
            lli poss = -get_sum(idx, seg) + f(seg, move+1);
            if(ans == poss) {
                
                ans_V.push_back(seg);
                rec(seg, move+1, ans_V);
                return;
            }
        }
    }

    return ;

}

int main () {
	//fastIO();
	
    cin>>n;
    forr(i, 1, n) cin>>nums[i];

    forr(i, 1, n) pref[i] = pref[i-1] + nums[i];

    auto ans = f(1, 0);

    vector<int> ans_seg;
    rec(1, 0, ans_seg);

    for(auto x: ans_seg) cout << x-1 << " ";
    cout << endl;

    

	return 0;
}

