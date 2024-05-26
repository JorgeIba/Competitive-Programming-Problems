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


void solve() {
    int n; cin>>n;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    nums.resize(2*n);
    for(int i = 0; i < n; i++) {
        nums[n + i] = nums[i];
    }

    nums.insert(nums.begin(), 0);
    for(int i = 1; i < SZ(nums); i++)
        nums[i] += nums[i-1];


    SparseTable<int> *ST = new SparseTable<int>(nums);

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int last = nums[i-1];
        int mini = ST->minimal(i, i + n - 1);
        
        ans += (mini > last);
    }

    cout << ans << endl;
}


int main () {
	//fastIO();

    // freopen("positive.in", "r", stdin);
    // freopen("positive.out", "w", stdout);
	
    solve();


	return 0;
}

