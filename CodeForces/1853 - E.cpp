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

    vector<lli> a(n+1);

    forr(i, 1, n) cin>>a[i];
    forr(i, 1, n) a[i] %= k;

    auto get_cost = [&](lli prev, lli next){
        return max(0LL, next - prev);
    };

    auto get_next_greater = [&](lli height, lli mult){
        lli m = (height - mult + (k-1)) / k;
        return mult + (m + (height == mult))*k;
    };

    auto get_next_lower = [&](lli height, lli mult){
        lli m = (height - mult) / k;
        return mult + m*k;
    };

    priority_queue<lli, vector<lli>, greater<lli>> pq;
    lli curr = 0;
    lli ans = 0;
    for(int i = 1; i <= n; i++){
        lli low = get_next_lower(curr, a[i]);
        lli gr = get_next_greater(curr, a[i]);

        lli cost = get_cost(curr, gr);
        pq.push(cost);

        if(low <= curr){
            curr = low;
        } else {
            auto best = pq.top(); pq.pop();
            curr = gr;
            ans += best;
        }
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