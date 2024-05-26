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


int query(int idx){
    idx++;
    cout << "? " << idx << endl;
    cout.flush();
    lli xorr; cin>>xorr;
    return xorr;
}

void main_(){
    int n, k; cin>>n>>k;


    int block = k;
    int many_blocks = n/k;
    
    if(n % k != 0){
        lli total_xor = 0;

        
        for(int i = 0; i < many_blocks; i++){
            auto xorr = query(block * i);
            total_xor ^= xorr;
        }
        int me = block * many_blocks - 1;
        int last = n-1;
        int how_many = (last - me) / 2;

        int last_query = block * (many_blocks-1);

        total_xor ^= query(last_query + how_many);
        total_xor ^= query(last - k + 1);

        cout << "! " << total_xor << endl;
    } else {
        lli total_xor = 0;

        for(int i = 0; i < many_blocks; i++){
            auto xorr = query(block * i);
            total_xor ^= xorr;
        }
        cout << "! " << total_xor << endl;
    }

    cout.flush();
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

