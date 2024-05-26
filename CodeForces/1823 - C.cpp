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


vector< pair<int,int> > get_divs(int n){
    vector< pair<int,int> > divs;
    int aux = n;
    for(int i = 2; 1LL * i * i <= aux; i++){
        if(n % i == 0){
            int pot = 0;
            while(n % i == 0) n /= i, pot++;
            divs.push_back({i, pot});
        }
    }

    if(n > 1) divs.push_back({n, 1});
    return divs;
};


void main_(){

    int n; cin>>n;
    vector<int> a(n);
    for(auto &x: a) cin>>x;

    map<int,int> all_facts;
    for(auto x: a){
        auto fact = get_divs(x);
        for(auto [p, e]: fact)
            all_facts[p] += e;
    }
    vector< pair<int,int> > facts(all(all_facts));
    lli ans = 0;

    lli rem = 0;
    for(auto [p, e]: facts){
        ans += (e / 2);
        rem += (e % 2);
    }

    ans += (rem / 3);
    cout << ans << endl;
}


int main () {
	fastIO();

	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

