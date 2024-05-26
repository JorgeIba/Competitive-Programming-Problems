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


int query(int i, int j){
    cout << "? " << i << " " << j << endl;
    cout.flush();
    int sum; cin>>sum;
    return sum;
}


int main () {
	//fastIO();

    int n; cin>>n;


    vector<int> S(3);
    S[0] = query(1, 2);
    S[1] = query(1, 3);
    S[2] = query(2, 3);


    vector<int> arr(n+1);
    arr[1] = (S[0] + S[1] - S[2]) / 2;
    arr[2] =  S[0] - arr[1];
    arr[3] =  S[1] - arr[1];


    forr(i, 4, n){
        int sum = query(1, i);
        arr[i] = sum - arr[1];
    }

    cout << "! ";
    forr(i, 1, n) cout << arr[i] << " ";
    cout << endl;





	return 0;
}

