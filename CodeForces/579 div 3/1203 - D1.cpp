#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string a,b;
	cin>>a>>b;
	size_t busqueda = a.find(b);
	lli izq = busqueda;
	lli der = a.length() - (busqueda + b.length());
	lli res= max(izq,der);
	cout<<res<<endl;
	
	return 0;
}
