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
        // cd w1 = polar(1.0, (inv?-1:1) * 2 * PI / k) ;
        w[0] = 1;
        for(int j = 1; j<k>>1; j++) 
            w[j] =  polar((ld)1.0, (inv?-1:1) * 2*j * PI / k);
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
vector<T> multiply(const vector<T> &A, const vector<T> &B)
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




int main () {
	fastIO();

    int n, q; cin>>n>>q;

    vector<int> perm(n+1);
    forr(i, 1, n) cin>>perm[i];

    vector<vector<int>> cycles;

    vector<bool> visited(n+1);
    forr(i, 1, n){
        if(visited[i]) continue;

        vector<int> cycle;
        int start = i, curr = i;
        do{
            visited[curr] = 1;
            cycle.push_back(curr);
            curr = perm[curr];
        }while(start != curr);

        cycles.push_back(cycle);
    }

    vector< vector<lli> > ans_per_size(n+1);
    auto calc_ans = [&](const vector<int> &cycle) -> void {
        int m = SZ(cycle);
        vector<lli> A(2*m), B(m);
        forn(i, m){
            B[i] = A[i + m] = A[i] = cycle[i];
        }
        reverse(all(B));
        auto M = multiply(A, B);

        if(ans_per_size[m].empty()) {
            ans_per_size[m].resize(m);
        }

        forn(i, m) ans_per_size[m][i] += M[i+m-1];
    };

    for(const auto &cycle: cycles)
        calc_ans(cycle);


    vector< vector<lli> > ans_all_sizes;
    forr(i, 1, n){
        if(ans_per_size[i].empty()) continue;
        ans_all_sizes.push_back(ans_per_size[i]);
    }
    


    while(q--){
        lli k; cin>>k;
        
        lli ans_k = 0;
        for(const auto &ans_size: ans_all_sizes){
            int m = SZ(ans_size);
            ans_k += ans_size[k % m];
        }

        cout << ans_k << endl;
        
    }
	


	return 0;
}

