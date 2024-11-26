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
        t = s; t.push_back(char(1));
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
};

const int LOWER = -1, EQUAL = 0, GREATER = 1;


int main () {
    fastIO();
    string s; cin>>s;
    
    int q; cin>>q;
    vector< pair<int,int> > queries(q);
    forn(i, q){
        int l, r; cin>>l>>r; l--, r--;
        queries[i] = {l, r};
    }
    
    SuffixArray SA(s);

    auto compare_same_size = [&](int l_1, int r_1, int l_2, int r_2) {
        int sz = r_1 - l_1 + 1;
        int msb = 31 - __builtin_clz(sz);

        if(SA.cl[msb][l_1] == SA.cl[msb][l_2]) {
            if(SA.cl[msb][r_1 - (1 << msb) + 1] == SA.cl[msb][r_2 - (1 << msb) + 1]) {
                return EQUAL;
            }

            return (SA.cl[msb][r_1 - (1 << msb) + 1] < SA.cl[msb][r_2 - (1 << msb) + 1]) ? LOWER : GREATER;
        } 

        return (SA.cl[msb][l_1] < SA.cl[msb][l_2]) ? LOWER : GREATER;
    };

    sort(all(queries), [&](auto a, auto b) {
        auto [l_1, r_1] = a;
        auto [l_2, r_2] = b;

        int sz_1 = r_1 - l_1 + 1;
        int sz_2 = r_2 - l_2 + 1;

        int mn = min(sz_1, sz_2);
        int cmp = compare_same_size(l_1, l_1 + mn - 1, l_2, l_2 + mn - 1);

        if(cmp == EQUAL) {
            if(sz_1 == sz_2) return a < b;
            
            return sz_1 < sz_2;
        } else if(cmp == LOWER) {
            return true;
        } else {
            return false;
        }
    });

    for(auto [l, r]: queries) {
        cout << l+1 << " " << r+1 << endl;
    }

	return 0;
}