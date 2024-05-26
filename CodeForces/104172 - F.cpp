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

typedef vector<int> bigInteger;

bigInteger operator+(const bigInteger &L, const bigInteger &R){
    auto A = L;
    auto B = R;
    reverse(all(A));
    reverse(all(B));

    int n = max(SZ(A), SZ(B));
    bigInteger C(n);

    int carry = 0;
    for(int i = 0; i < n; i++){
        int a = 0, b = 0;
        if(i < SZ(A)) a = A[i];
        if(i < SZ(B)) b = B[i];

        int sum = a + b + carry;
        if(sum >= 10){
            carry = 1;
            sum -= 10;
        } else {
            carry = 0;
        }

        C[i] = sum;
    }

    if(carry) C.push_back(carry);

    reverse(all(C));
    return C;
}


bool cmp(const bigInteger &L, const bigInteger &R) {
    if(SZ(L) == SZ(R)) {
        return L < R;
    }
    return SZ(L) < SZ(R);
}


const int MAXN = 2e5 + 100;
bigInteger dp[MAXN][10];

void main_(){
	int n, k; cin>>n>>k;

    bigInteger A(n);
    string s; cin>>s;
    forn(i, n){
        A[i] = s[i] - '0';
    }    

    int jump = n / (k+1);
    auto f = [&](const auto &f, int idx, int k){
        if(idx >= n) return bigInteger(1, 0);
        if(k == 0){
            return bigInteger(A.begin() + idx, A.begin() + n-1 + 1);
        }

        if(!dp[idx][k].empty()) return dp[idx][k];

        int r_opt_1 = (idx + jump - 1) + 1;
        int r_opt_2 = (idx + jump - 1);
        int r_opt_3 = (idx + jump - 1) - 1;

        r_opt_1 = min(r_opt_1, n-1);
        r_opt_2 = min(r_opt_2, n-1);
        r_opt_3 = min(r_opt_3, n-1);

        r_opt_1 = max(idx, r_opt_1);
        r_opt_2 = max(idx, r_opt_2);
        r_opt_3 = max(idx, r_opt_3);

        bigInteger opt_1( A.begin() + idx, A.begin() + r_opt_1 + 1);
        bigInteger opt_2( A.begin() + idx, A.begin() + r_opt_2 + 1);
        bigInteger opt_3( A.begin() + idx, A.begin() + r_opt_3 + 1);

        opt_1 = opt_1 + f(f, r_opt_1 + 1, k-1);
        opt_2 = opt_2 + f(f, r_opt_2 + 1, k-1);
        opt_3 = opt_3 + f(f, r_opt_3 + 1, k-1);

        return dp[idx][k] = min({opt_1, opt_2, opt_3}, [&](const auto &A, const auto &B) {
            return cmp(A, B);
        });
    };

    // TRY 1
    forn(i, n){
        forn(j, 10){
            dp[i][j].clear();
        }
    }
    auto ans_1 = f(f, 0, k);


    // TRY 2
    forn(i, n){
        forn(j, 10){
            dp[i][j].clear();
        }
    }
    jump = (n + (k+1) - 1) / (k+1);
    auto ans_2 = f(f, 0, k);


    auto ans = min(ans_1, ans_2, [&](const auto &A, const auto &B) {
        return cmp(A, B);
    });

    for(auto x: ans) cout << x;
    cout << endl;
}


int main () {
	fastIO();
	
    assert(true); // Alaneos777

	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

