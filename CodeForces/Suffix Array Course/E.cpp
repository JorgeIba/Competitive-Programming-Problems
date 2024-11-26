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

vector<int> getLeft(const vector<int> nums) {
    int n = SZ(nums);
    vector<int> left(n);
    stack< pair<int,int> > st;
    for(int i = 0; i < n; i++) {
        int val = nums[i];
        while(!st.empty() && st.top().first >= val) {
            st.pop();
        }

        if(st.empty()) {
            left[i] = -1;
        } else {
            left[i] = st.top().second;
        }

        st.push({val, i});
    }
    return left;
}


vector<int> getRight(const vector<int> nums) {
    int n = SZ(nums);
    vector<int> right(n);
    stack< pair<int,int> > st;
    for(int i = n-1; i >= 0; i--) {
        int val = nums[i];
        while(!st.empty() && st.top().first >= val) {
            st.pop();
        }

        if(st.empty()) {
            right[i] = n;
        } else {
            right[i] = st.top().second;
        }

        st.push({val, i});
    }
    return right;
}

int main () {
    // fastIO();
    int n, m; cin>>n>>m;

    vector<int> nums(n);
    for(auto &x: nums)
        cin>>x;

    SuffixArray SA(nums);
    SA.calcLCP();
    auto lcp = SA.lcp;

    lcp.erase(lcp.begin());
    auto print_vector = [&](const vector<int> &v, int l, int sz) {
        for(int i = 0; i < sz; i++) {
            cout << v[l+i] << " ";
        }
        cout << endl;
    };

    auto left = getLeft(lcp), right = getRight(lcp);

    array<lli,3> ans = {n, n, -1};
    for(int i = 0; i < SZ(lcp); i++) {
        int l = left[i] + 1, r = right[i] - 1;
        lli range = r - l + 1;
        array<lli,3> cand = {(range+1) * lcp[i], lcp[i], i+1};
        ans = max(ans, cand);
    }

    cout << ans[0] << endl;
    cout << ans[1] << endl;

    if(ans[2] == -1) {
        print_vector(nums, 0, n);
        return 0;
    }
    print_vector(nums, SA.suff[ans[2]], ans[1]);

	return 0;
}

