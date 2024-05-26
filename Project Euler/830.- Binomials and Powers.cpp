#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

using comp = complex<double>;
using poly = vector<int>;
const double PI = acos(-1.0);

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

const int MAXN = 2e6;
const int MAXLOG = 21;
comp wp[MAXLOG][MAXN], wp_inv[MAXLOG][MAXN];
void prec_ftt() {
    for(int i = 0, n = 1; i < MAXLOG; i++, n <<= 1) {
        for(int j = 0; j < n; ++j)
			wp[i][j] = polar(1.0, PI * j / n); // best precision but slower

        for(int j = 0; j < n; ++j)
			wp_inv[i][j] = polar(1.0, PI * j / n * (-1)); // best precision but slower
    }
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	for(int k = 1, logg = 0; k < n; logg++, k <<= 1){
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				comp t = X[i + j + k] * (inv == 1 ? wp[logg][j] : wp_inv[logg][j]);
				X[i + j + k] = X[i + j] - t;
				X[i + j] += t;
			}
		}
	}
	if(inv == -1)
		for(int i = 0; i < n; ++i)
			X[i] /= n;
}


poly convolutionMod(const poly & A, const poly & B, int mod){
	int s = sqrt(mod);
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	vector<comp> a(size), b(size);
	for(int i = 0; i < SZ(A); ++i)
		a[i] = comp(A[i] % s, A[i] / s);
	for(int i = 0; i < SZ(B); ++i)
		b[i] = comp(B[i] % s, B[i] / s);
	fft(a, 1), fft(b, 1);
	comp I(0, 1);
	vector<comp> c(size), d(size);
	for(int i = 0, j = 0; i < size; ++i){
		j = (size-1) & (size-i);
		comp e = (a[i] + conj(a[j])) * 0.5;
		comp f = (conj(a[j]) - a[i]) * 0.5 * I;
		comp g = (b[i] + conj(b[j])) * 0.5;
		comp h = (conj(b[j]) - b[i]) * 0.5 * I;
		c[i] = e * g + I * (e * h + f * g);
		d[i] = f * h;
	}
	fft(c, -1), fft(d, -1);
	poly D(sz);
	for(int i = 0; i < sz; ++i){
		int p0 = (lli)round(real(c[i])) % mod;
		int p1 = (lli)round(imag(c[i])) % mod;
		int p2 = (lli)round(real(d[i])) % mod;
		D[i] = p0 + s*(p1 + (lli)p2*s % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

int MOD;

poly operator*(poly &A, poly &B) {
    return convolutionMod(A, B, MOD);
}

poly operator%(poly A, int m) {
    poly C = A;
    for(int i = m; i < SZ(C); i++) {
        int idx = i % m;
        C[idx] += C[i];
        if(C[idx] >= MOD) C[idx] -= MOD;
    }
    C.resize(min(SZ(C), m));
    return C;
}


poly powerModPoly(poly A, lli b, int m) {
    poly R = {1};
    while(b) {
        if(b & 1) R = (R * A) % m;
        b >>= 1; 
        A = (A * A) % m;
    }

    return R;
}

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b) {
        if( b & 1 ) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


lli ans_for_mod(lli n, int m, int mod) {
    MOD = mod;
    poly base = {1, 1};

    cout << "Aqui voy" << endl;

    auto RES = powerModPoly(base, n, m) % mod;

    cout << "PASE" << endl;

    lli ans = 0;
    for(int r = 0; r < min(SZ(RES), (int) mod); r++) {
        ans = (ans + powerMod(r, n, mod) * RES[r] % mod);
        if(ans >= mod) ans -= mod;
    }

    return ans;
}


tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

pair<lli, lli> crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < SZ(a); ++i){
		auto[d, s, t] = extendedGcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return {-1, -1};
		lli step = m[i] / d;
		lli k = s * (((a[i] - x) / d) % step) % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return {x, mod};
}




int main () {
	// fastIO();

    prec_ftt();
	
    int A = 83*83*83;
    int B = 89*89*89;
    int C = 97*97*97;

    // lli n; cin>>n;
    lli n = 1'000'000'000'000'000'000;

    lli ans_A = ans_for_mod(n, A, A);
    lli ans_B = ans_for_mod(n, B, B);
    lli ans_C = ans_for_mod(n, C, C);

    auto [ans, mod] = crt({ans_A, ans_B, ans_C}, {A, B, C});

    cout << ans << endl;


	return 0;
}

