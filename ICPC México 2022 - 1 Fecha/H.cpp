#include<bits/stdc++.h>


using namespace std;

int main() {
	int n;
	cin >> n;
	int ans = 0;
	for(int i = 1; i < n; i++) {
		int rest = n - 2*i;
		if(rest >= 2) {
			ans = max(ans, rest/2*i);
		}
	}
	cout << ans << '\n';
	return 0;
}