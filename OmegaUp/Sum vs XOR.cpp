#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int tam=log2(n) + 1, contador=0;
	for (int i=0; i<tam; i++)
	{
		if(n%2==0)
		{
			contador++;
		}
		n>>=1;
	}
	long long int res= pow(2,contador);
	cout<<res<<endl;
	return 0;
}
