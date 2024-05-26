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


void main_(){
	int n, X; cin>>n>>X;
    vector<int> grades(n-1);
    for(auto &x: grades) cin>>x;


    auto get_sum = [](vector<int> grades){
        sort(all(grades));
        int sum = 0;
        int n = SZ(grades);
        for(int i = 1; i < n-1; i++){
            sum += grades[i];
        }
        return sum;
    };

    int inf = 1e9;
    int ans = inf;
    for(int x = 0; x <= 100; x++){
        auto aux = grades; aux.push_back(x);
        if(get_sum(aux) >= X) ans = min(ans, x);
    }

    cout << (ans != inf ? ans : -1)  << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

