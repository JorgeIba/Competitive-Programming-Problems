#include <bits/stdc++.h>
#define lli long long int
using namespace std;


void funcion()
{
	lli pan, ham, chick, cham, cchik, mayor, menor, contador=0;
	cin>>pan>>ham>>chick>>cham>>cchik;
	mayor=max(cham,cchik);
	menor=min(cham,cchik);
	if (pan<=1)
	{
		cout<<0<<endl;
		return;
	}
	if (pan%2==1)
	{
		pan--;
	}
	if (mayor==cchik)
	{
		while((chick>0)and(pan>0))
		{
			pan=pan-2;
			chick--;
			contador+=cchik;
		}
		while((ham>0)and(pan>0))
		{
			pan=pan-2;
			ham--;
			contador+=cham;
		}
	}
	else if (mayor==cham)
	{
		while((ham>0)and(pan>0))
		{
			pan=pan-2;
			ham--;
			contador+=cham;
		}
		while((chick>0)and(pan>0))
		{
			pan=pan-2;
			chick--;
			contador+=cchik;
		}
	}
	cout<<contador<<endl;
	
}



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli q;
	cin>>q;
	for (int i=0; i<q; i++)
	{
		funcion();
	}
	
	return 0;
}
