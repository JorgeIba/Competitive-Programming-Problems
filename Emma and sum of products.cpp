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
const lli MOD = 1e5 + 3;

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
    for(int i = 1, j = 0; i < n - 1; i++){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}
    
    vector< cd > w(n>>1);

    for(int k = 2; k<=n; k<<=1){
        cd w1 = polar((ld)1, (inv?-1:1) * 2 * PI / k) ;
        w[0] = 1;
        for(int j = 1; j<k>>1; j++)
            w[j] = w[j-1]*w1;
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
vector<T> multiply(vector<T> A, vector<T> B)
{
    int n = SZ(A) + SZ(B) - 1, sz = nearestPowerTwo(n);
    vector<cd> FA(sz), FB(sz);
    for(int i = 0; i<SZ(A); i++) FA[i] = A[i];
    for(int i = 0; i<SZ(B); i++) FB[i] = B[i];
    fft(FA, false);  fft(FB, false);
    for(int i = 0; i<sz; i++) FA[i]*=FB[i];
    fft(FA, true);
    vector<T> ans(n);
    for(int i = 0; i<n; i++){
        ans[i] = ((lli)(FA[i].real() + 0.5))%MOD;
    } 
    return ans;
}
vector< vector<lli> > ST;

void print(VLL a)
{
    for(auto c: a) cout<<c<<" ";
    cout<< endl;
}


VLL multimultiply(lli l, lli r)
{
    if(l > r) return {1};
    if(l==r) return ST[l];
    lli mid = (l+r)/2;
    return multiply( multimultiply(l,mid), multimultiply(mid+1, r));
}

int main () {
	fastIO();
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    for(int i = 0; i<n; i++)
    {
        ST.push_back({nums[i], 1});
    }

    int ST_n = SZ(ST);
    int sz = nearestPowerTwo(ST_n);
    while(SZ(ST) < sz) ST.push_back({1});

    auto C = multimultiply(0, SZ(ST)-1);
    lli q; cin>>q;
    while(q--)
    {
        lli k; cin>>k;
        cout << C[n-k] << endl; 
    }
    
	return 0;
}