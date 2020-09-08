#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std;

#define cd complex<ld>

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

typedef complex<ld> cd;
const ld PI = acos(-1);

int nearestPowerTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

const int LOG = 16, maxN = 3e4;
cd wp[16][maxN]; // wn[i][j] = w_{2^i}^j
cd wn[16][maxN];

void init()
{
    for(int i = 0; i<LOG; i++)
    {
        int n = pow(2, i);
        cd wnp = polar((ld)1, 2*PI/n);
        cd wnn = polar((ld)1, -2*PI/n);
        wp[i][0] = 1;
        wn[i][0] = 1;
        for(int j = 1; j<maxN; j++)
        {
            wp[i][j] = wp[i][j-1]*wnp;
            wn[i][j] = wn[i][j-1]*wnn;
        }
    }
}

void fft(vector<cd> &A, bool inv)
{
    int n = SZ(A);
    for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}
    
    for(int k = 2; k<=n; k<<=1)
    {
        int loga = log2(k);
        for(int i = 0; i<n; i+=k)
        {
            for(int j = 0; j<k/2; j++)
            {
                cd u = A[i+j], v = A[i+j+k/2] * (inv?wn[loga][j]:wp[loga][j]);
                A[i+j] = u + v;
                A[i+j+k/2] = u - v;
            }
        }
    }
    if(inv)
        for(auto &x: A) x/=n;
}


vector<lli> multiply(vector<lli> &A, vector<lli> &B)
{
    int n = SZ(A) + SZ(B) - 1, sz = nearestPowerTwo(n);
    vector<cd> FA(sz), FB(sz);
    for(int i = 0; i<SZ(A); i++) FA[i] = A[i];
    for(int i = 0; i<SZ(B); i++) FB[i] = B[i];
    fft(FA, false);
    fft(FB, false);
    vector<cd> C(sz);
    for(int i = 0; i<sz; i++) C[i] = FA[i]*FB[i];
    fft(C, true);
    vector<lli> ans(n);
    for(int i = 0; i<n; i++) ans[i] = (lli)(round(C[i].real()));
    return ans;
}




void solve () {
	
    lli n; cin>>n;
    vector<cd> A(n+1), B(n+1);

    for(int i = 0; i<=n; i++) cin>>A[i];
    for(int i = 0; i<=n; i++) cin>>B[i];

    auto C = multiply(A, B);
	
    for(auto c: C)
    {
        cout << (lli)(round(c.real())) << " ";
    }
    cout << endl;
    return;
}

int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}