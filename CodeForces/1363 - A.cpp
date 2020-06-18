#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve(){
	int n, x, aux;
	cin>>n>>x;
	int pares=0, impares=0;
	forn(i,0, n){
		cin>>aux;
		if(aux%2)
			impares++;
		else
			pares++;
	}
	if(impares==0 || (n==x && impares%2==0)){
		cout<<"No\n";
		return;
	}
	if(x%2==0){
		if(pares>0){
			cout<<"Yes\n";
			return;
		} else{
			cout<<"No\n";
			return;
		}
	} else{
		cout<<"Yes\n";
		return;
	}
}



int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}