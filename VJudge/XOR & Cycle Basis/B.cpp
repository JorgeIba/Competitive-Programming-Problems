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


const int LOG_D = 32;
vector<lli> basis(LOG_D);

void insert_vector(lli mask, bool zeros = false){
    for(int i = LOG_D-1; i>=0; i--){
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i]){
            basis[i] = mask;

			if(!zeros) return;

			for(int j = 0; j<LOG_D; j++)
			{
				if(j==i) continue;
				if(j < i){
					if(basis[i] & (1LL << j)) basis[i] ^= basis[j];
                }
				else{
					if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
                }
			}
            return;
        }
        mask ^= basis[i];
    }
}


void main_(){
    int n, k; cin>>n>>k;

    fill(all(basis), 0LL);

    forn(i, n){
        lli x; cin>>x;
        insert_vector(x, true);
    }

    forn(i, LOG_D){
        if(~k & (1LL << i)){
            k ^= basis[i];
        }
    }
    cout << k << endl;

}


int main () {
	//fastIO();
	
    int t = 1;
	cin>>t;
	
	while(t--) main_();



	return 0;    
}

