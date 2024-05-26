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

    vector<int> xs(k), cs(k);
    for(auto &x: xs) cin>>x;
    for(auto &x: cs) cin>>x;

    forn(i, k) {
        if(cs[i] > xs[i]) {
            cout << "NO" << endl;
            return;
        }
    }

    string ans(n, 'a');
    ans[0] = 'a';
    ans[1] = 'b';
    ans[2] = 'c';

    string opt;
    for(char c = 'a'; c <= 'z'; c++)
        opt.push_back(c);

    string wild_card = "abc";
    int last_opt = 3;
    int last_wild = 0;

    int total_pals = 3;

    for(int i = 0, j = 3; i < k; i++){
        int x = xs[i], c = cs[i];
        
        int sz_left = (x - j);
        int pal_left = (c - total_pals);
        int many_wild_card = sz_left - pal_left;

        // debugg(x);
        // debugg(c);
        // debugg(j);
        // debugg(last_opt);
        // debugg(last_wild);
        // debugg(sz_left);
        // debugg(pal_left);
        // debugg(many_wild_card);
    
        if(pal_left > sz_left) {
            cout << "NO" << endl;
            return;
        }


        for(int k = 0; k < many_wild_card; k++){
            ans[j] = wild_card[last_wild];
            j++;
            last_wild = (last_wild + 1) % 3;
        }

        for(int k = 0; k < pal_left; k++){
            ans[j] = opt[last_opt];
            j++;
        }
        last_opt++;


        // debugg(ans);

        // cout << endl;
        total_pals = c;
    }

    cout << "YES" << endl;
    cout << ans << endl;

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

