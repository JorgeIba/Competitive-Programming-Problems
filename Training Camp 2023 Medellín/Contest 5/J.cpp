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



int main () {
	//fastIO();
    string s, t; cin>>s>>t;
    int n = SZ(s), m = SZ(t);

    vector<int> removes(n);
    for(auto &x: removes) cin>>x;


    auto check = [&](int mid){
        string aux;
        vector<bool> put(n, 1);

        forn(i, mid) {
            int remove = removes[i];
            put[remove-1] = 0;
        }

        forn(i, n) if(put[i]){
            aux.push_back(s[i]);
        }

        int i = 0, j = 0;
        while(i < SZ(aux) && j < m){
            if(aux[i] == t[j])
                j++;

            i++;
        }

        return j == m;
    };


    int l = 0, r = n-1, ans = 0;
    while(l <= r){
        int mid = (l+r)/2;
        if(check(mid)){
            ans = mid;
            l = mid+1;
        } else {
            r = mid-1;
        }
    }

    cout << ans << endl;



	return 0;
}

