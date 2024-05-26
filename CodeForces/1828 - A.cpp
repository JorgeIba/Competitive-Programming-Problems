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


void main_(){
    int n; cin>>n;

    vector<int> arr(n);

    lli sum = 0;
    for(int i = 1; i < n; i++){
        arr[i] = (i+1);
        sum += i+1;
    }

    sum %= n;

    int left = (n - sum);

    arr[0] = left;

    // sum = 0;
    // for(int i = 0; i < n; i++){
    //     assert(arr[i] % (i+1) == 0);
    //     sum += arr[i];
    // }

    // assert(sum % n == 0);

    for(auto x: arr) cout << x << " ";
    cout << endl;
}

int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

