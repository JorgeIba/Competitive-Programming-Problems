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
	int n; cin>>n;

    vector<int> score(n);
    vector<string> mat(n);
    for(auto &s: mat) cin>>s;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat[i][j] == 'o') {
                score[i]++;
            }
        }
    }
    
    vector<pair<int,int>> scores;
    forn(i, n) scores.push_back({i, score[i]});

    sort(all(scores), [&](auto a, auto b){
        auto [id_a, sc_a] = a;
        auto [id_b, sc_b] = b;
        if(sc_a != sc_b) return sc_a > sc_b;
        return id_a < id_b;
    });

    for(auto [id, sc]: scores) cout << id+1 << " ";
    cout << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

