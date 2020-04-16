#include <bits/stdc++.h>
using namespace std;

int main()
{
	long int n1,n2, aux1, aux2, acum=0;
	cin>>n1>>n2;	
	aux1=n1;
	aux2=n2;
	do
	{
		acum++;
		cout<<aux1<<" "<<aux2<<" ";
		aux1=(aux1+aux2)%10;
		aux2=(aux2+aux1)%10;
	}while ((aux1!=n1)or(aux2!=n2));
	cout<<n1<<" "<<n2<<endl<<acum*2;
	return 0;
}
