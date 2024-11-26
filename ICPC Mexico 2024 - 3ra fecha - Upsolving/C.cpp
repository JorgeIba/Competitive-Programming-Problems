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

template<typename T>
struct SuffixArray {
    vector<int> suff;
    vector<T> t;
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

    SuffixArray(vector<T> s) {
        t = s; t.push_back(-1);
        N = t.size();
        suff.assign(N, 0);
        vector<int> c_new(N);
        vector<pair<T, int>> a(N);

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


int main () {
    // fastIO();
    
    int n; cin>>n;
    vector<int> v(n);
    for(auto &x: v)
        cin>>x;
    

    SuffixArray<int> SA(v);
    SA.calcLCP();

    stack< pair<int,int> > st;
    lli ans = 0, ans_st = 0;
    for(int i = 0; i < SZ(SA.lcp); i++) {
        pair<int,int> val = {SA.lcp[i], 1};
        while(!st.empty() && st.top().first >= val.first) {
            ans_st -= 1LL * st.top().second * st.top().first;

            val.second += st.top().second;
            st.pop();
        }

        ans_st += 1LL * val.first * val.second;
        ans += ans_st;
        st.push(val);
    }

    lli num = 2*ans + 1LL * n * (n+1) / 2;
    lli den = 1LL * n * n;

    lli g = gcd(num, den);
    cout << (num / g) << "/" << (den / g) << endl;

	return 0;
}

