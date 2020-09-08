#include <bits/stdc++.h>
using namespace std;

int main()
{
	int sumaCuadrados=0, cuadradoSumas=0, res;
	for (int i=1; i<=100; i++)
	{
		sumaCuadrados+=(i*i);
	}
	cuadradoSumas=((100*(101))/2) * ((100*(101))/2);
	res=cuadradoSumas-sumaCuadrados;
	cout<<res;
	return 0;
}
