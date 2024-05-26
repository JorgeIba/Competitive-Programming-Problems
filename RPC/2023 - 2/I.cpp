#include<bits/stdc++.h>
#define lli long long int
#define ld long double
#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lli> vlli;

struct Fraction {
  lli a, b;
  Fraction(lli x, lli y) {
    if(x < 0) {
      x *= -1;
      y *= -1;
    }
    lli gcd = __gcd(x,y);
    a = x / gcd;
    b = y / gcd;
  }
  Fraction() {}
};

bool operator>(const Fraction& A, const Fraction& B) {
  return B.b * A.a > A.b*B.a;
}

bool operator<(const pair<Fraction,pii>& A, const pair<Fraction, pii>& B) {
  return A.fi > B.fi;
}

const int inf = 1e8;

template<typename T>
struct SegmentTree{
  vector<pii> st;
  int size;
  T INF = {inf, -inf};
  T op(T left, T right) {
    T ans;
    ans.fi = min(right.fi, left.fi);
    ans.se = max(right.se, left.se);
    return ans;
  }
  void build(int elem, int l, int r, vector<T>& arr) {
    if(l > r) return;
    if(l == r) st[elem] = arr[l-1];
    else {
      int mid = (l+r) >> 1;
      build(2*elem, l, mid, arr);
      build(2*elem + 1, mid + 1, r, arr);
      st[elem] = op(st[2*elem], st[2*elem + 1]);
    }
  }

  SegmentTree(int sz, vector<T>& arr) : size(sz) {
    st.resize(4*size + 10);
    build(1, 1, size, arr);
  }

  void update(int elem, int l, int r, int pos, T val) {
    if(l == pos && l == r) {
      st[elem] = val;
      return;
    }
    if(r < pos || l > pos) return;
    int mid = (l + r) >> 1;
    update(2*elem, l, mid, pos, val);
    update(2*elem + 1, mid + 1, r, pos, val);
    st[elem] = op(st[2*elem], st[2*elem + 1]);
  }
  T query(int elem, int l, int r, int start, int end) {
    if(l > r) return INF;
    if(l >= start && r <= end) return st[elem];
    if(r < start || end < l) return INF;
    int mid = (l + r) >> 1;
    return op(query(2*elem, l, mid, start, end), query(2*elem + 1, mid + 1, r, start, end));
  }
};

bool encounter_in_posT(int x1, int v1, int x2, int v2) {
  if(x1 >= x2)
    return v2 > v1;
  return v2 <= v1;
}

int main() {
  // fastIO();
  int n;
  cin >> n;
  vector<lli> x(n), v(n);
  forn(i,n) cin >> x[i] >> v[i];

  priority_queue< pair<Fraction, pii> > next_time;
  forn(i,n-1) {
    if(v[i + 1] == v[i]) continue;
    if(encounter_in_posT(x[i], v[i], x[i + 1], v[i + 1])) {
      Fraction time_enc(x[i] - x[i+1], v[i + 1] - v[i]);
      // cout << i << ' ' << i + 1 << ' ' << time_enc.a << '/' << time_enc.b << endl;
      next_time.push({time_enc, {i,i+1}});
    }
  }
  vector<pii> aux(n);
  forn(i,n) aux[i] = {i,i};
  SegmentTree<pii> st(n, aux);
  vector<bool> is_alive(n, true);
  while(!next_time.empty()) {
    Fraction frac;
    pii pos;

    auto some = next_time.top(); next_time.pop();
    frac = some.fi;
    pos = some.se;

    // cout << "Sale: " << pos.fi << ' ' << pos.se << endl;
    if(!is_alive[pos.fi] || !is_alive[pos.se]) continue;
    is_alive[pos.fi] = is_alive[pos.se] = false;

    st.update(1, 1, n, pos.fi + 1, {inf, -inf});
    st.update(1, 1, n, pos.se + 1, {inf, -inf});
    auto aux1 = st.query(1, 1, n, 1, pos.fi + 1);
    auto aux2 = st.query(1, 1, n, pos.se + 1, n);

    // cout << "left: " << aux1.fi << ' ' << aux1.se << endl;
    // cout << "right: " << aux2.fi << ' ' << aux2.se << endl;

    int left = st.query(1, 1, n, 1, pos.fi + 1).se;
    int right = st.query(1, 1, n, pos.se + 1, n).fi;

    if(abs(left) != inf && abs(right) != inf) {
      // assert(left != -inf && right != inf);
      if(v[right] == v[left]) continue;
      if(encounter_in_posT(x[left], v[left], x[right], v[right])) {
        Fraction time_enc(x[left] - x[right], v[right] - v[left]);
        // cout << "Entra: " << left << ' ' << right << endl;
        next_time.push({time_enc, {left,right}});
      }
    }
  }

  vector<int> ans;
  forn(i,n) {
    if(is_alive[i])
      ans.push_back(i + 1);
  }

  cout << ans.size() << endl;
  forn(i,ans.size()) {
    cout << ans[i];
    if(i != ans.size() - 1) cout << ' ';
  }
  cout << endl;
  return 0;
}

