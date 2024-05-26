#include<bits/stdc++.h>

using namespace std;
const int mxn = 5e4+105;
bool mem[mxn];

vector<int> weights;

void dfs(int i) {
	// cout << i << '\n';
	if(i >= mxn) return;
	mem[i] = true;
	for(int x : weights) {
		if(i + x < mxn && !mem[i + x])
			dfs(i + x);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, k;
	cin >> k >> n;
	weights.resize(n);
	for(int &x : weights) cin >> x;
	dfs(0);
	vector<int> preff(mxn+1);
	for(int i = mxn - 1; i >= 0; i--) {
		if(mem[i]) preff[i] = i;
		else preff[i] = preff[i+1];
	}
	while(k--) {
		int x;
		cin >> x;
		cout << abs(x - preff[x]) << '\n';
	}
	return 0;
}