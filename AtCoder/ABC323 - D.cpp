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

    vector<pair<lli,lli>> slimes(n);
    for(auto &[s, c]: slimes) cin>>s>>c;

    map<lli,lli> fr;
    set<lli> smallest;

    for(auto [s, c]: slimes) {
        fr[s] = c;
        smallest.insert(s);
    }

    int left = 0;
    while(!smallest.empty()){
        lli x = *smallest.begin(); smallest.erase(x);
        lli new_sz = 2*x;
        lli fr_x = fr[x];
        fr[x] = 0;

        // debugg(new_sz);
        // debugg(fr_x/2);
        // debugg(fr[new_sz] + fr_x/2);
        // cout << endl;

        left += (fr_x % 2);
        if(fr_x > 1){
            fr[new_sz] += fr_x/2;
            smallest.insert(new_sz);
        }
    }

    cout << left << endl;

}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

