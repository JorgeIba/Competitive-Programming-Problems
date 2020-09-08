#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef complex<ld> cd;
const ld PI = acos(-1);

int nearestPowerTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

void fft(vector<cd> &A, bool inv)
{
    int n = SZ(A);
    for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}
    
    vector< cd > w(n>>1);

    for(int k = 2; k<=n; k<<=1)
    {
        cd w1 = polar((ld)1, (inv?-1:1) * 2 * PI / k) ;
        w[0] = 1;
        for(int j = 1; j<k>>1; j++)
            w[j] = w[j-1]*w1;

        for(int i = 0; i<n; i+=k)
        {
            for(int j = 0; j<k>>1; j++)
            {
                cd u = A[i+j], v = A[i+j+k/2] * w[j];
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
    vector< lli > A(n+1), B(n+1);

    for(auto &x: A) cin>>x;
    for(auto &x: B) cin>>x;
	
    auto C = multiply(A, B);

    for(auto x: C) cout << x << " ";
    cout << endl;
}

int main()
{
    fastIO();
    int t; cin>>t;
    while(t--) solve();
}