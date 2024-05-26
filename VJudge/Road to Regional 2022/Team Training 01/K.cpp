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

const int MAXA = 50;

int fr[MAXA + 10];

int n;

bool f(int num) {
    if(fr[num] > n/2) return false;
    if(fr[num] >= 1) return true;

    return f(num+1);
}



int main () {
	//fastIO();
	
    cin>>n;

    vector<int> nums(n);
    for(auto &x: nums) {
        cin>>x;
        fr[x]++;
    }

    if(f(1)){
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
    }

	return 0;
}

