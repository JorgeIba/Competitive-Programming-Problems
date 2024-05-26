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
    int n, m; cin>>n>>m;

    vector< pair<lli,lli> > happ(n);
    for(auto &[a, b]: happ) cin>>a>>b;

    if(n == 1){
        cout << happ[0].second << endl;
        return;
    }

    lli yes = 0;
    for(auto [a, b]: happ) yes += a;

    sort(all(happ), [](auto x, auto y){
        return x.second - x.first > y.second - y.first;
    });

    priority_queue<lli> pq;
    for(auto [a, b]: happ){
        pq.push(b-a);
    }


    lli max_ans = yes;
    lli ans = yes;

    int idx_i = 0, idx_j = m-1-n+1;
    while(SZ(pq) > 1 && idx_i < idx_j){
        if(SZ(pq) == 2) {
            auto diff = pq.top(); pq.pop();
            ans += diff;

            diff = pq.top(); pq.pop();
            ans += diff;
        } else {
            auto diff = pq.top(); pq.pop();
            ans += diff;
        }
        
        max_ans = max(max_ans, ans);

        idx_i += 2;
        idx_j++;
    }

    cout << max_ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

