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


vector<int> query(int n, vector<int> f){
    cout << "? ";
    forr(i, 1, n) {
        cout << f[i] << " ";
    }
    cout << endl; cout.flush();

    vector<int> g(n+1);
    forr(i, 1, n) cin>>g[i];
    return g;
}


void solve(){
    int n; cin>>n;


    vector<int> f_1(n+1);
    f_1[1] = n;
    forr(i, 2, n) f_1[i] = i-1;

    auto g_1 = query(n, f_1);

    vector<int> f_2(n+1);
    f_2[1] = 1;
    f_2[2] = n;
    forr(i, 3, n) f_2[i] = i-1;

    auto g_2 = query(n, f_2);

    vector<int> ans_inv(n+1);
    forr(i, 1, n){
        if(g_2[i] == i) ans_inv[1] = i;
    }


    vector<int> pos(n+1);
    forr(i, 1, n) pos[g_1[i]] = i;

    int start = ans_inv[1];
    int curr = start;
    int j = 1;
    do{
        ans_inv[j] = curr;

        curr = pos[curr];
        // debugg(curr);
        j++;
    }while(curr != start);

    cout << "! ";
    forr(i, 1, n) cout << ans_inv[i] << " ";
    cout << endl; cout.flush();
}




int main () {
	//fastIO();

    int t; cin>>t;
    while(t--) solve();

	return 0;
}

