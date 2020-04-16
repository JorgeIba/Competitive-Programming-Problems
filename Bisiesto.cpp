#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	long long unsigned int casos=0; 
	int ano=0;
	cin>>casos;
	for (int i=0; i<casos; i++)
	{
		cin>>ano;
		if (ano%4==0)
		{
			if (ano%100==0)
			{
				if (ano%400==0)
				{
					cout<<"S\n";
				}
				else
				{
					cout<<"N\n";	
				}
				
			}
			else
			{
				cout<<"S\n";
			}
		}
		else if ((ano%100==0)&&(ano%400==0))
		{
			cout<<"S\n";
		}
		else
		{
			cout<<"N\n";
		}
	}
	return 0;
}
