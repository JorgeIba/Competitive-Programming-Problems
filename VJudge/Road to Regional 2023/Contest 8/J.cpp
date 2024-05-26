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

typedef complex<ld> cd;
const ld PI = acos(-1);

int nearestPowerTwo(int n){
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

void fft(vector<cd> &A, bool inv){
    int n = SZ(A);
    for(int i = 1, j = 0; i < n - 1; i++){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}
    
    vector< cd > w(n>>1);

    for(int k = 2; k<=n; k<<=1){
        w[0] = 1;
        for(int j = 1; j<k>>1; j++)
            w[j] =  polar((ld)1.0, (inv?-1:1) * 2*j * PI / k);
        for(int i = 0; i<n; i+=k){
            for(int j = 0; j<k>>1; j++){
                cd u = A[i+j], v = A[i+j+(k>>1)] * w[j];
                A[i+j] = u + v;
                A[i+j+(k>>1)] = u - v;
            }
        }
    }
    if(inv)
        for(auto &x: A) x/=n;
}

template<typename T>
vector<T> multiply(const vector<T> &A, const vector<T> &B){
    int n = SZ(A) + SZ(B) - 1, sz = nearestPowerTwo(n);
    vector<cd> FA(sz), FB(sz);
    for(int i = 0; i<SZ(A); i++) FA[i] = A[i];
    for(int i = 0; i<SZ(B); i++) FB[i] = B[i];
    fft(FA, false); 
    
    if(A==B) FB = FA;
    else fft(FB, false);

    for(int i = 0; i<sz; i++) FA[i]*=FB[i];
    fft(FA, true);
    vector<T> ans(n);
    for(int i = 0; i<n; i++) ans[i] = (T)(round(FA[i].real()));
    return ans;
}

typedef vector<int> Poly;

Poly operator*(const Poly &A, const Poly &B){
    return multiply(A, B);
}


const int N = 5e5 + 100;

int main () {
	//fastIO();

    vector<int> sigma(N);

    for(int d = 1; d < N; d++){
        for(int j = d; j < N; j += d) {
            sigma[j]++;
        }
    }
	
    auto ways = sigma * sigma;

    int t; cin>>t;
    while(t--){
        int l, r; cin>>l>>r;
        int ans = l;
        for(int i = l; i <= r; i++){
            if(ways[ans] < ways[i]){
                ans = i;
            }
        }
        cout << ans << " " << ways[ans] << endl;
    }


	return 0;
}

