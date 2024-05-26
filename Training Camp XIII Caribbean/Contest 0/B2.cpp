#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define forn(i, n) for (int i = 0; i < n; i++)
#define forr(i, a, n) for (int i = a; i <= n; i++)
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(), v.end()
#define SZ(v) (int)v.size()
#define endl '\n'
#define fastIO()                                                               \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<lli> vlli;

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

  // It's used to store info about the automaton, for example, the number of
  // paths that pass through a node, which can be used to get the number of
  // different strings
  vector<lli> dp, numb_ac;
  vector<bool> is_ac;

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

  void dfs1(int u) {
    assert(u < numb_ac.size());
    numb_ac[u] = is_ac[u];
    for (auto [c, v] : st[u].child) {
      if (v >= numb_ac.size()) {
        cout << "v: " << v << endl;
      }
      assert(v < numb_ac.size());
      if (numb_ac[v] == -1)
        dfs1(v);
      numb_ac[u] += numb_ac[v];
    }
  }

  void dfs2(int u) {
    assert(u < dp.size());
    dp[u] = numb_ac[u];
    for (auto [c, v] : st[u].child) {
      assert(v < dp.size());
      if (dp[v] == -1)
        dfs2(v);
      dp[u] += dp[v];
    }
  }

  void prec() {

    dp.resize(last+1, -1);
    numb_ac.resize(last+1, -1);
    is_ac.resize(last+1);

    for (int v = last; v != -1; v = st[v].link)
      is_ac[v] = true;
    dfs1(0);
    dfs2(0);
  }

  void getKth(int u, string &ans, lli &k) {
    if (k <= 0)
      return;
    for (auto [c, v] : st[u].child) {
      if (dp[v] >= k) {
        k -= numb_ac[v];
        ans.pb(c);
        getKth(v, ans, k);
        return;
      }
      k -= dp[v];
    }
  }
};

int main() {
  // fastIO();
  string s;
  lli k;
  string ans;
  cin >> s >> k;

  SuffixAutomaton sa;
  for (char c : s)
    sa.extend(c);

  sa.prec();
  /*
  lli maxn = (s.size() * (s.size() + 1)) / 2;
  forr(i, 1, maxn) {
    lli aux = i;
    string t;
    sa.getKth(0, t, aux);
    cout << i << ": " << t << endl;
  }
  */
  sa.getKth(0, ans, k);

  cout << ans << endl;

  return 0;
}