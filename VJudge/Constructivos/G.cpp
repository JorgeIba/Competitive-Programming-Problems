#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


const int MAXA = 10000;
int main () {
	//fastIO();
	
    set<int> numbers;
    for(int i = 2*3; i <= MAXA; i += 2*3){
        numbers.insert(i);
    }

    for(int i = 2*5; i <= MAXA; i += 2*5){
        numbers.insert(i);
    }

    for(int i = 3*5; i <= MAXA; i += 3*5){
        numbers.insert(i);
    }

    int n; cin>>n;

    vector<int> ans = {2*3, 2*5, 3*5};
    numbers.erase(2*3); numbers.erase(2*5); numbers.erase(3*5);

    while(SZ(ans) < n){
        ans.push_back(*numbers.begin());
        numbers.erase(numbers.begin());
    }

    for(auto x: ans) cout << x << " ";
    cout << endl;

    // int g = 0;
    // for(auto x: ans) g = gcd(x, g);
    // assert(g == 1);

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < i; j++){
    //         assert(gcd(ans[i], ans[j]) > 1);
    //     }
    // }


	return 0;
}

