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


int query(int x){
    cout << x << endl;
    cout.flush();
    int y; cin>>y;
    return y;
}

void main_(){
	
    int n; cin>>n;
    
    const int MAX_ITER = 3*n + 5;
    vector<bool> in(3*n+5);
    forn(i, n){
        int x; cin>>x;
        if(x >= MAX_ITER) continue;
        in[x] = true;
    }

    if(in[0] == false){
        int y = query(0);
        assert(y == -1);
        return;
    }


    for(int i = 0; i < MAX_ITER; i++){
        if(in[i] == false){
            int y = query(i);
            if(y == -1) {
                return;
            }

            while(y != -1){
                y = query(y);
            }
            return;
        }
    }

    assert(false);
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

