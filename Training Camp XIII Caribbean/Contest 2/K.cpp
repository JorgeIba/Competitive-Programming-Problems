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

const int MAXN = 2e6 + 1, SIG = 26;
const int MAXT = 11;

int len[MAXN], link[MAXN];
int child[MAXN][SIG + MAXT];
int sz = 0;
int last = 0;
short dp_msk[MAXN];
int dp_cnt[MAXN];
int income[MAXN];
int order[MAXN];
int sz_order = 0;


void init() { 
    len[sz] = 0;
    link[sz] = -1;
    sz++;
}

void extend(int c) {

    int curr = sz, p;

    len[sz] = len[ last ] + 1;
    link[sz] = -1;
    sz++;

    for(p = last; p != -1 && child[p][c] == -1; p = link[p])
        child[p][c] = curr;

    if (p == -1)
            link[curr] = 0;
    else {
        int q = child[p][c];
        if(len[p] + 1 == len[q])
            link[curr] = q;
        else {
            int w = sz;
            len[sz] = len[p] + 1;
            link[sz] = link[q];
            forn(i, SIG + MAXT) 
                child[sz][i] = child[q][i];
            sz++;

            for(; p != -1 && child[p][c] == q; p = link[p])
                child[p][c] = w;

            link[q] = link[curr] = w;
        }
    }
    last = curr;
}


void toposort() {
    int n = sz;
    for(int i = 0; i < n; i++) {
        for(int c = 0; c < SIG + MAXT; c++){
            auto v = child[i][c];
            if(v == -1) continue;
            income[v]++;
        }
    }

    queue<int> q;
    
    for(int i = 0; i < n; i++) if(income[i] == 0) {
        order[sz_order++] = i;
        q.push(i);
    }

    
    while(!q.empty()) {
        auto u = q.front(); q.pop();

        for(int c = 0; c < SIG + MAXT; c++) {
            auto v = child[u][c];
            if(v == -1) continue;

            income[v]--;

            if(income[v] == 0) {
                order[sz_order++] = v;
                q.push(v);
            }
        }
    }
}


void dfs(int u) {
    if(dp_msk[u] != -1) return;

    dp_msk[u] = 0;

    forn(c, SIG + MAXT) {
        int v = child[u][c];
        if(v == -1) continue;

        if(c < SIG) {
            if(dp_msk[v] == -1) dfs(v);

            dp_msk[u] |= dp_msk[v];
        } else {
            dp_msk[u] |= (1 << (c - SIG));
        }
    }

    order[sz_order++] = u;
}


int main () {
	fastIO();
    memset(child, -1, sizeof(child));
    memset(dp_msk, -1, sizeof(dp_msk));

	init();

    string s;
    int num = 0;
    while(cin>>s) {
        for(int i = 0; i < SZ(s); i++) {
            extend(s[i] - 'a');
        }
        extend(num + SIG);
        num++;
    }

    dfs(0);

    int m = sz;

    int MASK = (1LL << num) - 1;

    for(int i = 0; i < m; i++) {
        int u = order[i];
        if(dp_msk[u] != MASK) continue;

        for(int c = 0; c < SIG; c++) {
            auto v = child[u][c];
            if(v == -1) continue;
            if(dp_msk[v] == MASK) {
                dp_cnt[u] = max(dp_cnt[u], dp_cnt[v] + 1);
                assert(dp_msk[u] >= dp_msk[v]);
            }
        }
    }

    cout << *max_element(dp_cnt, dp_cnt + m) << endl;

	return 0;
}

