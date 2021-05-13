#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define i128 __int128 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;
lli num[55], L, R, mem[55][2][55];
int n, k;
/*
lli dp(int i, bool canUseAll, int bits, const vi& dig){
	if(i == n) return bool(bits==k);
	//lli &ans =  mem[i][canUseAll][bits];
	lli ans = 0;
	if(ans != -1) return ans;
	ans = 0;
	int lim = canUseAll? dig[i] : 1;
	forn(j,lim+1)
		ans += dp(i+1,j < lim, bits + bool(j), dig);
	return ans;
}
lli fun(lli a){
	vi dig(n,0);
	forn(i,n){
		if(a &(1ll<<i))
			dig[i] = 1;
	}
	lli ans = 0;
	memset(mem, -1, sizeof(mem));
	return dp(0,0,0,dig);
}*/
const int maxN = 55;
i128 nCr[maxN][maxN];

void prec()
{
    nCr[0][0] = 1;
    for(int i = 1; i<maxN; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            if(j==0 || j == i) nCr[i][j] = 1;
            else
            {
                nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j];
            }
        }
    }
}


lli nums(lli limit, lli n)
{
	if(limit < 0) return 0;
	lli k = int(log2(limit+1));
	lli pow2 = pow(2, k);
	if( (pow2 - 1) == limit ) return nCr[k][n];
	return nCr[k][n] + nums(limit - pow2, n-1);
}


lli counting(lli l, lli r, lli k)
{
	return nums(r,k) - nums(l-1,k);
}
lli sum(lli msk){
	lli ans = 0;
	forn(i,n){
		if(msk & (1ll<<i))
			ans += num[i];
	}
	return ans;
}
int main(){
	fastIO();
	prec();
	cin >> n >> k;
	forn(i,n) cin >> num[i];
	cin >> L >> R;
	sort(num, num+n);
	lli l = 0, r = (1ll<<n)-1;
	lli A = -1;
	while(l <= r){
		lli mid = l + (r-l)/2;
		if(sum(mid) <= R){
			A = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	lli B = -1;
	l = 0, r = (1ll<<n)-1;
	while(l <= r){
		lli mid = l + (r-l)/2;
		if(sum(mid) >= L){
			B = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	if(A==-1 || B == -1) cout << "0\n";
	else cout << counting(B, A, k) << '\n';
	return 0;
}


