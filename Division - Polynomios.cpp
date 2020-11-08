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

void fft(vector<cd> &A, bool inv) //O(n logn)
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
vector<T> multiply(vector<T> A, vector<T> B) //O(n logn), it uses FFT
{
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



const int p = 0, g = 5;

template<typename T>
vector<T> invertPolynomio(vector<T> F, int d) // R_2n = R_n(2 - R_nF)
{
    vector<T> R_n = { 1/F[0] }; //equivalent to: 1 / F[0]
    while(SZ(R_n) <= d)
    {
        int j = 2*SZ(R_n);
        auto FF = F; FF.resize(j);
        //for(auto x: R_n) cout << x << " ";
        //for(auto x: FF) cout << x << " ";
        vector<T> RnF = multiply(R_n, FF);
        for(auto &x: RnF) x = p-x;
        RnF[0] = RnF[0] + 2 < p? RnF[0] + 2: RnF[0] + 2 - p; 
        R_n = multiply(R_n, RnF);
        R_n.resize(j);
    }
    R_n.resize(d+1);
    return R_n;
}


template<typename T> //A = Q*B + R
vector<T> division(vector<T> A, vector<T> B)
{
    int n = SZ(A), m = SZ(B);
    if(n < m) return {0};
    reverse(all(A));
    reverse(all(B));
    A.resize(n-m+1); B.resize(n-m+1);
    A = multiply(A, invertPolynomio(B, n-m));
    A.resize(n-m+1);
    reverse(all(A)); //R = A-Q*B
    return A;
}

template<typename T> //Return R = A - Q*B
vector<T> remainder(vector<T> A, const vector<T> &B) 
{
	int n = SZ(A),  m = SZ(B);
	if(n >= m){
		vector<T> R = multiply(division(A, B),B);
		A.resize(m-1);
		for(int i = 0; i<m-1; i++){
			A[i] -= R[i];
			if(A[i] < 0) A[i] += p;
		}
	}
	return A;
}


int main () {
	//fastIO();
    vector<lli> A = {1, 1, 2, 4};
    vector<lli> B = {8, 1}; 
    //invertPolynomio(A, 4);
    auto Q = remainder(A, B);
    for(auto x: Q) cout << x << " ";
	return 0;
}