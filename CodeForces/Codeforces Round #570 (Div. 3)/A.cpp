#include <bits/stdc++.h>
using namespace std;


int sumaDigits(int n)
{
	int aux=0;
	while(n!=0)
	{
		aux+=n%10;
		n/=10;
	}
	return aux;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;	
	for (int i=n; i<=2000; i++)
	{
		if ((sumaDigits(i) % 4)==0)
		{
			cout<<i;
			return 0;
		}
	}
	return 0;
}
