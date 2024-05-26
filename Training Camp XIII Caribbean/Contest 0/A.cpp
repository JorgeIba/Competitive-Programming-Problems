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

struct state {
  int len, link;
  map<int, int> child;
  state(int len = 0, int link = -1) : len(len), link(link) {}
  state(int len, int link, map<int, int> child)
      : len(len), link(link), child(child) {}
};

struct SuffixAutomaton {
  vector<state> st;
  int last = 0;

  SuffixAutomaton() { st.emplace_back(); }

  void extend(char c) {
    int curr = st.size(), p;
    st.emplace_back(st[last].len + 1);
    for (p = last; p != -1 && !st[p].child.count(c); p = st[p].link)
      st[p].child[c] = curr;

    if (p == -1)
      st[curr].link = 0;
    else {
      int q = st[p].child[c];
      if (st[p].len + 1 == st[q].len)
        st[curr].link = q;
      else {
        int w = st.size();
        st.emplace_back(st[p].len + 1, st[q].link, st[q].child);
        for (; p != -1 && st[p].child[c] == q; p = st[p].link)
          st[p].child[c] = w;
        st[q].link = st[curr].link = w;
      }
    }
    last = curr;
  }
};


const int MAXN = 4e5 + 1000;
lli dp[MAXN];

SuffixAutomaton *SA;


lli dp_1(int n) {
    lli &ans = dp[n];
    if(ans != -1) return ans;

    if(n)
        ans = 1;

    for(auto [char_int, next_st]: SA->st[n].child) {
        ans += dp_1(next_st);
    }

    return ans;
}



void dfs(int state, lli k, string &s) {
    if(k == 0) return;

    for(auto [char_int, next_state]: SA->st[state].child) {
        if(dp[next_state] >= k) {
            k--;
            s.push_back(char_int);
            dfs(next_state, k, s);
            return;
        }

        k -= dp[next_state];
    }
    assert(false);
}




int main () {
	//fastIO();
	
    memset(dp, -1, sizeof(dp));

    string s; cin>>s;
    lli k; cin>>k;


    SA = new SuffixAutomaton();
    for(auto c: s) SA->extend(c);

    // cout << dp_1(0) << endl;
    dp_1(0);



    string ans;
    dfs(0, k, ans);

    cout << ans << endl;



	return 0;
}
