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


void main_(){
	
    int n, k; cin>>n>>k;
    vector<int> perm(n);
    for(auto &x: perm) cin>>x;
    for(auto &x: perm) x--;

    
    vector< vector<int> > perms(k);
    for(int i = 0; i < k; i++){
        for(int j = i; j < n; j += k){
            perms[i].push_back(perm[j]);
        }
    }

    int wrong = 0;
    for(int i = 0; i < k; i++){
        sort(all(perms[i]));
        for(int j = 0; j < SZ(perms[i]); j++){
            wrong += (perms[i][j] % k != i);
        }
    }


    // cout << "WRONG: " << wrong << endl;
    if(wrong == 0){
        cout << 0 << endl;
    } else if(wrong == 2){
        cout << 1 << endl;
    } else {
        assert(wrong != 1);
        cout << -1 << endl;
    }

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

