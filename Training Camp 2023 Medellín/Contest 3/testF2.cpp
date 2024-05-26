#include<bits/stdc++.h>
using namespace std;
using LL = long long;

LL exgcd(LL a, LL b, LL &x, LL &y){
	if (!b){
		x = 1, y = 0;
		return a;
	}
	LL d = exgcd(b, a % b, y, x);
	y -= ( a / b ) * x;
	return d;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	LL n, m;
	cin >> n >> m;
	LL sum = 0;
	for (int i = 0; i < n; i ++ ){
		int x;
		cin >> x;
		sum = (sum + x) % m;
	}
	
	LL s, d, x, y;
	LL g = exgcd(exgcd(n, n * (n + 1) / 2, s, d), m, x, y);
	LL k = (m - sum + g - 1) / g;
    cout << s << " " << d << " " << x << " " << y << endl;

	cout << k * g + sum - m << "\n";
	x = x * k % m;
	cout << (s * x % m + m) % m << " " << (d * x % m + m) % m << "\n";
	return 0;
}