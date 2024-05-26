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


struct Pooling{
    priority_queue<int> best;
    priority_queue< int, vector<int>, greater<int> > others;
    lli sum = 0;
    lli limit;

    Pooling(lli limit): limit(limit) {}

    void insert(int x) {
        others.push(x);

        update();
    }

    int quant() { return SZ(best); }

    void update(){ 

        while(!others.empty()) {
            int x_low = others.top();
            if(best.empty()) {
                if(x_low <= limit) {

                    sum = x_low;
                    best.push(x_low);
                    others.pop();

                } else {break;}
            } else {
                int x_gr = best.top();

                if(x_low < x_gr) {    
                    sum -= x_gr;
                    best.pop();
                    others.pop();
                

                    sum += x_low;
                    best.push(x_low);
                    others.push(x_gr);

                } else if(sum + x_low <= limit){
                    sum += x_low;
                    best.push(x_low);
                    others.pop();
                } else {
                    break;
                }
            }
        }
    }
};


void main_(){
	int n, k; cin>>n>>k;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector<int> best(n+1);

    auto check = [&](lli limit) {
        Pooling P_L(limit);
        Pooling P_R(limit);

        forn(i, n+1) best[i] = 0;

        for(int i = n-1; i >= 0; i--){
            auto x = nums[i];
            P_R.insert(x);
            best[i] = P_R.quant();
        }

        assert(P_R.sum <= limit);
        if(P_R.quant() >= k) return true;

        for(int i = 0; i < n; i++) {
            auto x = nums[i];
            P_L.insert(x);

            assert(P_L.sum <= limit);
    
            if(P_L.quant() + best[i+1] >= k) return true;
        }

        return false;
    };



    lli l = 1, r = 1e15, ans = -1;
    while(l <= r) {
        lli mid = (l + r) / 2;

        if(check(mid)) {
            ans = mid;
            r = mid-1;
        } else {
            l = mid+1;
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