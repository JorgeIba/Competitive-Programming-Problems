#include <bits/stdc++.h>
#define lli long long int
#define ld long double

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli m, n;
	cin>>m>>n;
	long double resultado = 0;
	for(int i=1; i<=m-1; i++)
	{
		ld auxiliar = (double(i)/double(m));
		resultado -= pow(auxiliar,n);
	}
	resultado+= m;
	cout<<fixed<<setprecision(10)<<resultado<<endl;
	
	return 0;
}
