#include <bits/stdc++.h>
#define lli long long int
 
using namespace std;
 
int main()
{
	lli n;
	cin>>n;
	n=n*(n-1)*(n-2)*(n-3)*(n-4);
	lli aux = n;
	n=n/120;
	n*=aux;
	cout<<n<<endl;
	return 0;
}
