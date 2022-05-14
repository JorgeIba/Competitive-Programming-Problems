#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


lli query(lli q){
    cout << "? " << q << endl;
    cout.flush();
    lli ans; cin>>ans;
    return ans;
}

void solve(){
    lli n; cin>>n;
    vector<bool> marked(n+1);
    vector<lli> adj(n+1);

    for(int i = 1; i <= n; i++){
        if(marked[i]) continue;

        lli q = -1, initial = query(i);
        lli last = initial;
        do{
            q = query(i);
            
            adj[last] = q;
            marked[q] = true;
            last = q;
        }while(q != initial);
    }

    
    cout << "! ";
    for(int i = 1; i<=n; i++) cout << adj[i] << " ";
    cout << endl;
    
}





int main () {
	//fastIO();
    lli t; cin>>t;

    while(t--) solve();

	return 0;
}

