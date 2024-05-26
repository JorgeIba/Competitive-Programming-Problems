#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

void main_(){

    lli n; cin>>n;


    if(n % 2 == 0) {
        for(int i = 1; i <= n/2; i++) {
            cout << n-i << " " << n+i << " ";
        }
        cout << endl;
        return;
    } else {
        vector<lli> ans = {n+2};
        for(int i = 1; i <= (n-1)/2; i++) {
            ans.push_back(n-i+2);
            ans.push_back(n+i+2);
        }

        sort(all(ans));

        ans[0]--;
        ans[n-1]++;
        ans[n-2]++;

        for(auto x: ans) cout << x << " ";
        cout << endl;
    }

}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

