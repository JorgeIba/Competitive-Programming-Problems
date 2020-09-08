#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

lli n, k; 
vector< ld > nums;
vector< vector<ld> > comb(505, vector<ld> (505));
vector< ld > r(505);
//vector< __float128 > coeff(600,  1.0);

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

using comp = complex<ld>;
const ld PI = acos(-1.0);

void fft(vector<comp> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<comp> wp(n>>1);
	for(int k = 1; k < n; k <<= 1){
		for(int j = 0; j < k; ++j)
			wp[j] = polar((ld)1.0, (ld)PI * j / k * inv);
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				comp t = X[i + j + k] * wp[j];
				X[i + j + k] = X[i + j] - t;
				X[i + j] += t;
			}
		}
	}
	if(inv == -1)
		for(int i = 0; i < n; ++i)
			X[i] /= n;
}

vector<comp> convolution(vector<ld> C, vector<ld> D){
    vector< comp > A, B;
    for(auto x: C) A.push_back(x);
    for(auto x: D) B.push_back(x);


	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	fft(A, 1), fft(B, 1);
	for(int i = 0; i < size; i++)
		A[i] *= B[i];
	fft(A, -1);
	A.resize(sz);
	return A;
}



void prep()
{
	comb[0][0] = 1;
	for(int i = 1; i<=500; i++)
	{
		for(int j = 0; j<=500; j++)
		{
			if(!j) comb[i][0] = 1;
			else
			{
				comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
			}
		}
	}
    for(int i = 0; i<n; i++)
    {
        assert(n-i-1 >= 0 && k-1 >=0 && comb[n][k] != 0);
        r[i] = comb[n-i-1][k-1] / comb[n][k];
    }
    r.resize(n);
}

int main () 
{
	//fastIO();
    cin>>n>>k;
    //prec();
	prep();
    nums.resize(n);

    for(int i = 0; i<n; i++)
    {
        cin>>nums[i];
        assert(nums[i] >= 0);
    } 

    auto ans = convolution(nums, r);

    vector< ld > ansFinal(n);
    for(int i = 0; i<SZ(ans); i++)
    {
        ansFinal[ i%n ] += ans[i].real();
    }

    cout << fixed << setprecision(10);
    for(auto x: ansFinal) cout << x << " ";

	
	return 0;
}