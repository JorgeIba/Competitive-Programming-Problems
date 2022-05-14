#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define lli long long int
#define __ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()
#define SZ(v) v.size()
#define ld long double
using namespace std;
typedef vector<int> vi;
typedef vector<lli> vlli;
int N;


typedef complex<double> cd;
const double PI = acos(-1);

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
        // cd w1 = polar(1.0, (inv?-1:1) * 2 * PI / k) ;
        w[0] = 1;
        for(int j = 1; j<k>>1; j++) // best precision but slower
            w[j] =  polar(1.0, (inv?-1:1) * 2*j * PI / k);
            //w[j] = w[j-1]*w1;
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
vector<T> multiply(const vector<T> &A, const vector<T> &B) //O(n logn), it uses FFT
{
		if(A.size() == 0) return {};
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

vlli obtenerMini(vi& colors, vi& fonts) {
	vlli aux;
	int l = 0, r = N-1;
	reverse(all(fonts));
	while(l < N && fonts[l] >= 0 && colors[l] < 0) {
		aux.push_back(fonts[l]*colors[l]);
		l++;
	}
	while(r >= 0 && fonts[r] < 0 && colors[r] >= 0) {
		aux.push_back(fonts[r]*colors[r]);
		r--;
	}
	vlli A, B;
	for(int i = l; i <= r; i++) {
		A.push_back(fonts[i]);
		B.push_back(colors[i]);
	}
	sort(all(A), [&](lli& a, lli& b) {return abs(a) < abs(b); });
	sort(all(B), [&](lli& a, lli& b) {return abs(a) < abs(b); });
	sort(all(aux), [&] (lli& a, lli& b) { return a < b; });

	for(int i = 1; i < aux.size(); i++) {
		aux[i] += aux[i-1];
	}

	auto ans = multiply(A, B);
	int m = aux.size();
	lli suff = aux.size() > 0? aux.back() : 0;
	forn(i,N-m) aux.push_back(ans[i] + suff);
	return aux;
}
vlli obtenerMaxi(vi& colors, vi& fonts) {
	vlli A, B;
	int l = 0, r = N-1;
	vlli aux;
	while(l < N && colors[l] < 0 && fonts[l] < 0) {
		aux.push_back(colors[l] * fonts[l]);
		l++;
	}	
	while(r >= 0 && colors[r] >= 0 && fonts[r] >= 0) {
		aux.push_back(colors[r] * fonts[r]);
		r--;
	}
	for(int i = l; i <= r; i++) {
		A.push_back(colors[i]);
		B.push_back(fonts[i]);
	}
	sort(all(A),[&](lli& a, lli& b) {return abs(a) < abs(b); });
	sort(all(B),[&](lli& a, lli& b) {return abs(a) < abs(b); });

	auto ans = multiply(A, B);
	int m = aux.size();
	sort(all(aux), [&](lli& a, lli& b) { return a > b; });
	for(int i = 1; i < aux.size(); i++) {
		aux[i] += aux[i-1];
	}
	lli preff = (aux.size() > 0)? aux.back() : 0;
	forn(i,N - m) aux.push_back(ans[i] + preff);
	return aux;
}

int main() {__
	cin >> N;
	vi colors(N);
	vi fonts(N);
	for(int& x : colors) cin >> x;
	for(int& x : fonts) cin >> x;
	sort(all(colors));
	sort(all(fonts));
	auto maxi = obtenerMaxi(colors, fonts);
	auto mini = obtenerMini(colors, fonts);
	// for(auto x : maxi) cout << x << ' '; cout << '\n';
	// for(auto x : mini) cout << x << ' '; cout << '\n';
	forn(i,min(SZ(maxi), SZ(mini))) {
		cout << mini[i] << ' ' <<maxi[i] << '\n';
	}
	return 0;
}