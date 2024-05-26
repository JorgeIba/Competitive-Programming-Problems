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

    lli n, p; cin>>n>>p;
    vector<lli> a(n), b(n);

    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;
    
    vector< pair<lli,lli> > vill;
    forn(i, n){
        vill.push_back({a[i], b[i]});
    }

    sort(all(vill), [&](auto a, auto b){
        if(a.second == b.second) return a.first > b.first;
        return a.second < b.second;
    });

    priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
    pq.push({p, n});

    lli ans = 0;
    for(int i = 0; i < n; i++){
        auto [price, quantity] = pq.top(); pq.pop();
        ans += price;
        quantity--;
        if(quantity) pq.push({price, quantity});


        auto [a, b] = vill[i];
        pq.push({b, a});
    }

    cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

