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

template<typename T>
struct SparseTable{
	vector<vector<T>> ST;
	vector<int> logs;
	int K, N;

	SparseTable(vector<T> & arr){
		N = arr.size();
		K = log2(N) + 2;
		ST.assign(K + 1, vector<T>(N));
		logs.assign(N + 1, 0);
		for(int i = 2; i <= N; ++i)
			logs[i] = logs[i >> 1] + 1;
		for(int i = 0; i < N; ++i)
			ST[0][i] = arr[i];
		for(int j = 1; j <= K; ++j)
			for(int i = 0; i + (1 << j) <= N; ++i)
				ST[j][i] = min(ST[j - 1][i], ST[j - 1][i + (1 << (j - 1))]);
	}

	T minimal(int l, int r){ 
		int j = logs[r - l + 1];
		return min(ST[j][l], ST[j][r - (1 << j) + 1]);
	}
};


vector<int> closest_left(const vector<int> &a){
    int n = SZ(a);
    stack< pair<int,int> > s; // {idx, val}
    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        auto x = a[i];
        while(!s.empty() && x > s.top().second) {
            s.pop();
        }

        ans[i] = (s.empty() ? -1 : s.top().first);

        s.push({i, x});
    }
    return ans;
}


vector<int> closest_right(const vector<int> &a){
    int n = SZ(a);
    stack< pair<int,int> > s;
    vector<int> ans(n);
    for(int i = n-1; i >= 0; i--){
        auto x = a[i];
        while(!s.empty() && x > s.top().second) {
            s.pop();
        }

        ans[i] = (s.empty() ? n : s.top().first);

        s.push({i, x});
    }
    return ans;
}



void main_(){
    int n; cin>>n;

    vector<int> a(n);
    for(auto &x: a) cin>>x;

    lli ans = 0;
    for(int l = 0; l < n; l++){
        ans += 1LL*l*(l+1)/2;
    }

    auto gr_left = closest_left(a), gr_right = closest_right(a);

    SparseTable<int> ST(a);

    for(int i = 0; i < n; i++) {
        auto x = a[i];
        int left = gr_left[i] + 1;
        int k = gr_right[i];

        int ll = k, rr = n-1, first_r = -1;

        while(ll <= rr) {
            int mid = (ll + rr)/2;

            if(x < ST.minimal(k, mid)) {
                first_r = mid;
                ll = mid+1;
            } else {
                rr = mid-1;
            }
        }


        if(first_r == -1) continue;
        ans -= 1LL*(i - left + 1) * (first_r - k + 1);
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

