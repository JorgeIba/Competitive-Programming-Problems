#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

const lli MOD = 1e9+7;
int n, I, J, x, y;

const int maxN = 110;
lli dp[maxN][maxN];

lli fun(int curr, int left, int right){
	if(left > right) {
		return 1;
	}

	lli &ans = dp[curr][left];
	if(ans != -1) return ans;
	ans = 0;

	bool possible_in_left = (	left != I || (left == I && curr == x) ) && (
								left != J || (left == J && curr == y) ) && (
								curr != n || (curr == n && left != 1 && left != n) );


	bool possible_in_right = (	right != I || (right == I && curr == x) ) && (
								right != J || (right == J && curr == y) ) && (
								curr != n || (curr == n   && right != 1 && right != n) );
	// put curr in left
	if( possible_in_left ) {
		ans = (ans + fun(curr+1, left+1, right)) % MOD;
	}
	
	
	// put curr in right
	if(possible_in_right && left != right) {
		ans = (ans + fun(curr+1, left, right-1)) % MOD;
	}

	return ans;
}



void main_(){
	cin>>n>>I>>J>>x>>y;
	 
	memset(dp, -1, sizeof(dp));
	lli ans = fun(1, 1, n);

	cout << ans << endl; 
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

