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

template<typename T>
struct DisjointSparseTable {
  vector<vector<T>> left, right;
  int K, N;
  typedef function<T(T,T)> typeFun;
  T NEUTRO;
  typeFun OP;

  DisjointSparseTable(const vector<T>& arr, T neutro, typeFun op) : NEUTRO(neutro), OP(op) {
    N = arr.size();
    K = log2(N) + 2;
    left.assign(K + 1, vector<T>(N));
    right.assign(K + 1, vector<T>(N));

    for(int j = 0; (1<<j) <= N; j++) {
      int mask = (1 << j) - 1;
      T acum = NEUTRO;
      forn(i,N) {
        acum = OP(acum, arr[i]);
        left[j][i] = acum;
        if((i&mask) == mask) acum = NEUTRO;
      }
      acum = NEUTRO;
      for(int i = N - 1; i>= 0; --i) {
        acum = OP(arr[i], acum);
        right[j][i] = acum;
        if((i&mask) == 0) acum = NEUTRO;
      }
    }
  }

  T query(int l, int r) {
    if(l > r) return 1e8;
    if(l == r) return left[0][l];
    int i = 31 - __builtin_clz(l ^ r);
    return OP(right[i][l], left[i][r]);
  }
};

int _max(int a, int b) { return max(a, b); }

int main() {
  fastIO();
  int n;
  cin >> n;
  vector<int> a(n);
  forn(i,n) cin >> a[i];
  vector<int> last((int)1e6 + 10, -1);
  lli ans = 0;
  DisjointSparseTable<int> rmq(a, -1, _max);
  for(int i = n - 1; i >= 0; i--) {
    if(last[a[i]] != -1) {
      lli aux = rmq.query(i + 1, last[a[i]]-1);
      if(aux < a[i]) ans += last[a[i]] - i -1;
    }
    last[a[i]] = i;
  }
  cout << ans << endl;
  return 0;
}

