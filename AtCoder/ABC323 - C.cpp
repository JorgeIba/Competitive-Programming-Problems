#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


void main_(){
	int n, m; cin>>n>>m;

    vector<int> score_problem(m);
    for(auto &x: score_problem) cin>>x;

    vector< string > solves(n);
    for(auto &s: solves) cin>>s;

    vector<int> scores(n);
    for(int i = 0; i < n; i++){
        scores[i] += (i+1);
        for(int j = 0; j < m; j++){
            if(solves[i][j] == 'o'){
                scores[i] += score_problem[j];
            }
        }
    }

    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        vector<int> not_solved;
        for(int j = 0;  j < m; j++){
            if(solves[i][j] == 'x') not_solved.push_back(j);
        }

        sort(all(not_solved), [&](auto a, auto b){
            return score_problem[a] > score_problem[b];
        });

        int max_score = 0;
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            max_score = max(max_score, scores[j]);
        }

        int total_score = scores[i];
        int j = 0;
        // if(i == 1) {
        //     cout << total_score << " -- " << max_score << endl;
        //     for(auto x: not_solved) {
        //         cout << x << " ";
        //     }
        //     cout << endl;
        // }
        while(j < SZ(not_solved) && total_score <= max_score) {
            total_score += score_problem[not_solved[j]];
            j++;
        }
        ans[i] = j;
    }

    for(auto x: ans) cout << x << endl;

}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

