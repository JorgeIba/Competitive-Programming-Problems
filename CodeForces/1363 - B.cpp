#include <bits/stdc++.h>
//Dont hack me plz :(

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli buscar(char a, char b, string s)
{
    lli n = s.length();
	lli primero=0, segundo=0;
	if(s[0]==b)
		primero++;
	for(int i = 1; i<n; i++)
    {
		if(s[i]==a)
			segundo++;
	}
	lli res = primero+segundo;
	for(int i = 1; i<n; i++)
    {
		if(s[i]==b){
			primero++;
		} else{
			segundo--;
		}
		res = min(res, primero+segundo);
	}
	return res;
}

void solve(){
	string s; cin>>s;
	lli n = s.size();
	lli res = buscar('0', '1', s);

	res=min(res, buscar('1', '0', s));

	cout<<res<<endl;
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