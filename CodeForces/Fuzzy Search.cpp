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
vector<T> multiply(vector<T> &A, vector<T> &B)
{
    int n = SZ(A) + SZ(B) - 1, sz = nearestPowerTwo(n);
    vector<cd> FA(sz), FB(sz);
    for(int i = 0; i<SZ(A); i++) FA[i] = A[i];
    for(int i = 0; i<SZ(B); i++) FB[i] = B[i];
    fft(FA, false);  fft(FB, false);
    for(int i = 0; i<sz; i++) FA[i]*=FB[i];
    fft(FA, true);
    vector<T> ans(n);
    for(int i = 0; i<n; i++) ans[i] = (T)(round(FA[i].real()));
    return ans;
}

string s, T;
int n, m, k; 

VLL disperse(VLL v, char c)
{
    VLL ans(n);
    for(int i = 0; i<n; i++)
    {
        if(s[i] == c){
            int inLeft = max(0, i-k);
            int inRigt = min(n, i+k+1);
            ans[inLeft] += 1;
            if(inRigt < n)
                ans[inRigt] += -1; 
        }
    }
    
    int counting = 0;
    for(int i = 0; i<n; i++)
    {
        counting += ans[i];
        if(counting > 0){
            ans[i] = 1;
        }
        else ans[i] = 0;
        assert(counting >= 0);
    }
    
    return ans;
}

int main () {
	fastIO();
    cin>>n>>m>>k;

    cin>>s>>T;

    vector<lli> a(n), g(n), c(n), t(n);
    for(int i = 0; i<n; i++)
    {
        char ca = s[i];
        if(ca == 'A') a[i] = 1;
        else if(ca == 'G') g[i] = 1;
        else if(ca == 'C') c[i] = 1;
        else t[i] = 1;
    }

    vector<lli> ta(m), tg(m), tc(m), tt(m);
    for(int i = 0; i<m; i++)
    {
        char ca = T[i];
        if(ca == 'A') ta[i] = 1;
        else if(ca == 'G') tg[i] = 1;
        else if(ca == 'C') tc[i] = 1;
        else tt[i] = 1;
    }

    a = disperse(a, 'A');
    g = disperse(g, 'G');
    c = disperse(c, 'C');
    t = disperse(t, 'T');

    reverse(all(ta));
    reverse(all(tg));
    reverse(all(tc));
    reverse(all(tt));


    auto ca = multiply(a, ta);
    auto cg = multiply(g, tg);
    auto cc = multiply(c, tc);
    auto ct = multiply(t, tt);

    int howMuch = 0;
    for(int i = 1; i<=n; i++)
    {
        int total = ca[n-i] + cg[n-i] + cc[n-i] + ct[n-i];
        if(total == m) howMuch++;
        //cerr << "Total de puntos con " << i-1 << " shifts: " << total << endl;
    }
    cout << howMuch << endl;


	return 0;
}