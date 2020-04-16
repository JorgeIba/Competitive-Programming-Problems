#include <iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int Andrew=0, Dmitry=0, Michal=0;
	int verdes=0, moradas=0, negras=0, total=0;
	cin>>Andrew>>Dmitry>>Michal;
	cin>>verdes>>moradas>>negras;
	total=verdes+moradas+negras;
	Andrew-=verdes;
	if (Andrew<=0)
	{
		verdes=Andrew*(-1);
	}
	else 
	{
		cout<<"NO";
		return 0;
	}
	if ((verdes>0) or (moradas>0))
	{
		total=moradas+verdes;
		Dmitry-=total;
		if (Dmitry<=0)
		{
			total=Dmitry*(-1);
		}
		else 
		{
			total=0;
		}
	}
	
	total=total+negras;
	
	if (total>0)
	{
		Michal-=total;
		if (Michal<=0)
		{
			total=Michal*(-1);
		}
		else 
		{
			total=0;
		}
	}

	if ((Michal<=0)and(Dmitry<=0)and(Andrew<=0))
	{
		cout<<"YES";
	}
	else 
	{
		cout<<"NO";
	}
	return 0;
}
