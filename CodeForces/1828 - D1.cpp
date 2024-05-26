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

void main_(){
    int n; cin>>n;

    vector<int> a(n);
    for(auto &x: a) cin>>x;

    lli ans = 0;
    for(int l = 0; l < n; l++){
        for(int r = l+1; r < n; r++){
            ans += (r - l);
        }
    }


    SparseTable<int> ST(a);

    for(int l = 0; l < n; l++){
        int maxi = a[l];
        for(int k = l; k < n; k++){
            maxi = max(maxi, a[k]);
            int ll = k+1, rr = n-1, ans_m = -1;

            while(ll <= rr) {
                int mid = (ll + rr)/2;

                if(maxi < ST.minimal(k+1, mid)){
                    ans_m = mid;
                    ll = mid+1;
                } else {
                    rr = mid-1;
                }
            }

            if(ans_m != -1) ans -= (ans_m - k);
        }
    }

    cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

