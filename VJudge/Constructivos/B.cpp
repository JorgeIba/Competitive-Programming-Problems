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
    int n; cin>>n;

    vector<int> A(n);

    for(auto &x: A) cin>>x;

    map<int,int> fr;
    for(auto x: A) fr[x]++;



    set<int> available;
    forr(i, 1, n) if(!fr[i]) available.insert(i);
    

    vector<int> ans = A;
    for(int i = 0; i < n; i++) {
        auto num = ans[i];

        if(fr[num] == 1) { // no le muevas
            fr[num] = -1;

        } else if(fr[num] == -1) {
            int lowest = *available.begin();
            available.erase(lowest);
            ans[i] = lowest;
            fr[lowest] = -1;
        }
        else {
            assert(fr[num] > 1);

            int lowest = *available.begin();
            if(lowest >= num) {
                fr[num] = -1;
                continue;
            }


            available.erase(lowest);

            ans[i] = lowest;

            fr[num]--;
            if(fr[num] == 1) available.erase(num);
        }
    }

    int changes = 0;
    forn(i, n) {
        changes += (A[i] != ans[i]);
    }

    cout << changes << endl;
    for(auto x: ans) cout << x << " ";
    cout << endl;




	return 0;
}

