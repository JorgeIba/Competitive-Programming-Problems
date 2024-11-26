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

struct SuffixArray {
    vector<int> suff;       
    string t;               
    vector<int> lcp;        
    vector<vector<int>> cl; 
    int N;                  

    void count_sort(vector<int> &p, const vector<int> &c) {
        int n = c.size();
        vector<int> p_new(n), cnt(n + 1);
        for (int x : c)
            cnt[x + 1]++;

        partial_sum(all(cnt), cnt.begin());
        
        for (int x : p)
            p_new[cnt[c[x]]++] = x;
        p.swap(p_new);
    }

    SuffixArray(string s) {
        t = s + "#";
        N = t.size();
        suff.assign(N, 0);
        vector<int> c_new(N);
        vector<pair<char, int>> a(N);

        for (int i = 0; i < N; i++)
            a[i] = {t[i], i};
        
        sort(all(a));

        for (int i = 0; i < N; i++)
            suff[i] = a[i].second;

        c_new[suff[0]] = 0;
        for (int i = 1; i < N; i++) {
            int x = suff[i-1], y = suff[i];
            c_new[y] = c_new[x] + (a[i].first != a[i - 1].first);
        }

        cl.push_back(c_new);
        for(int k = 1; k < N; k <<= 1) {
            auto &c = cl.back();
            for (int i = 0; i < N; i++)
                suff[i] = (suff[i] + N - k) % N;

            count_sort(suff, c);

            c_new[suff[0]] = 0;
            for (int i = 1; i < N; i++) {
                int x = suff[i-1], y = suff[i];
                pair<int, int> prev = {c[x], c[(x + k) % N]};
                pair<int, int> now = {c[y], c[(y + k) % N]};
                c_new[y] = c_new[x] + (now != prev);
            }
            cl.push_back(c_new);
        }
    }

    void calcLCP() {
        lcp.assign(N, 0);
        int k = 0;
        auto &c = cl.back();
        for (int i = 0; i < N - 1; i++) {
            int pi = c[i];
            int j = suff[(pi - 1 + N) % N];
            while ((i + k) < N && (j + k) < N && t[i + k] == t[j + k])
                k++;
            lcp[pi] = k;
            k = max(k - 1, 0);
        }
    }
};

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

struct LCP {
    int n, m;
    SuffixArray SA;
    vector<int> inv;
    SparseTable<int> *ST;
    vector<int> lcp, suff;

    LCP(string s): n(SZ(s)), m(n+1), SA(s), inv(m) {
        SA.calcLCP();

        lcp = SA.lcp;
        suff = SA.suff;

        lcp.erase(lcp.begin());
        ST = new SparseTable<int>(lcp);

        forn(i, m) {
            inv[suff[i]] = i;
        }
    }

    int get_lcp(int i, int j) {
        if(i == j) return n - i;
        i = inv[i], j = inv[j];
        if(i > j) swap(i, j);
        return ST->minimal(i, j-1);
    }
};

int main () {
    // fastIO();

    string s; cin>>s;
    auto t = s; reverse(all(t));
    int n = SZ(s);

    LCP lcp(s);
    LCP lcp_rev(t);
    
    
    int ans = 1;
    for(int jumps = 1; jumps < n; jumps++) {
        for(int start = 0; start < n - jumps; start += jumps) {
            int i = start, j = start + jumps;

            int d = abs(i - j);
            int r = lcp.get_lcp(i, j);
            int l = lcp_rev.get_lcp(n - j - 1, n - i - 1);
            int inside = j - i - 1;

            if(d <= l) {
                ans = max(ans, (r + l + inside) / d);
            }
        }
    }
    cout << ans << endl;

	return 0;
}

