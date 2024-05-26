#include<bits/stdc++.h>
#define lli long long int
#define ld __float128
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

const ld eps = 1e-18, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b


lli get(vlli& A, int l, int r) {
          // cout << l << ' ' << r << " -> " << A[r] << "-" << (l ? A[l-1] : 0) << " = "<< A[r] - (l? A[l-1] : 0) << endl;
        //   assert(r >=0 && r < A.size());
        //   assert(l >= 0 && l < A.size());
          return A[r] - (l? A[l-1] : 0);
}

const int OFFSET = 1e9;

void solve() {
  int d;
  long double pp;
  cin >> d >> pp;

//   cout << pp << endl;
  ld p = pp;
//   lli P = p * OFFSET;
//   cout << P << endl;
  vlli C(d);
  forn(i,d) cin >> C[i];

  vlli diff(d);
  vlli diff_sq(d);

  forn(i,d-2) {
          diff[i] = C[i+1] - C[i];
          diff_sq[i] = (diff[i] * diff[i]);
  }
  forr(i,1,d-1) {
          diff[i] += diff[i-1];
          diff_sq[i] += diff_sq[i-1];
  }
  int pos = 0, neg = 0;
  forn(i,(int)diff.size()) {
          forr(j, i + 1, (int)diff.size() - 1) {
                  int n = j - i + 1;
                  lli S = get(diff, i, j);
                  lli T = get(diff_sq, i, j);

                  lli Q = (1LL*n * T - (S*S));
                  // ld D_sq = (ld)sum*sum / den;
                  // D_sq >= P ^ 2?
                  // sum*sum >= P^2 * den;
                //   lli X = S*S;
                //   lli Y = P * P;

                  if(S == 0) continue;

                  if(Q == 0) {
                          if(S > 0)
                                  pos++;
                          else
                                  neg++;
                          continue;
                  }
                  cout << S << " --> " << S*S << " -- " << ((long double) (p*p*Q)) << " ---> " << geq(S * S, p*p*Q) << endl;
                  if(geq(S * S, p*p*Q)) {
                        if(S > 0) pos++;
                        else neg++;
                  }
          }
  }
  cout << pos << ' ' << neg << endl;
}

int main() {
//   fastIO();
  int tt = 1;
  // cin >> tt;
  while(tt--)
          solve();
  return 0;
}

