#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


int get_maximum(int n, int k, const vector<vector<int>> &cycles) {

    int ans = 0;
    int rem = 0;
    for(auto &cycle: cycles) {
        int m = SZ(cycle);
        for(int i = 1; i < m; i+=2) {
            if(k) {
                ans += 2;
                k--;
            }
        }
        rem += (m & 1);
    }

    ans += min(rem, k);
    return ans;
}

const int maxK = 1e6+10;


int get_minimum(int n, int k, const vector<vector<int>> &cycles) {

    map<int, int> freqs;
    for(auto &cycle: cycles) {
        freqs[ SZ(cycle) ]++;
    }

    vector<int> A;
    for(auto [sz, fr_sz]: freqs) {

        int bin = 1;
        while(fr_sz) {
            int to_add = min(fr_sz, bin);
            A.push_back(to_add * sz);
            fr_sz -= to_add;
            bin <<= 1;
        }
    }

    int m = SZ(A);


    vector< bitset<maxK> > dp(m+1);
    dp[0][0] = true;

    for(int i = 1; i <= m; i++){
        int sz = A[i-1];

        dp[i] = dp[i-1];

        dp[i] |= (dp[i-1] << sz);
    }

    return (dp[m][k] ? k : k+1);
}


int main () {
	//fastIO();

    int n, k; cin>>n>>k;
    vector<int> perm(n+1);
    for(int i = 1; i <= n; i++) cin>>perm[i];


    vector< vector<int> > cycles;
    vector<bool> visited(n+1);
    for(int i = 1; i <= n; i++) {
        if(visited[i]) continue;

        vector<int> cycle;

        int p = i, start = i;
        do {
            visited[p] = true;
            cycle.push_back(p);
            p = perm[p];
        }while(p != start);

        cycles.push_back(cycle);
    }


    cout << get_minimum(n, k, cycles) << " " << get_maximum(n, k, cycles) << endl;


	return 0;
}

