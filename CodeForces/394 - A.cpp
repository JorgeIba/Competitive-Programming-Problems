#include <bits/stdc++.h>
using namespace std;

int main()
{
	int cAI=0, cDI=0, cAM=0, cDM=0;
	string cadena;
	bool flag=false, flagM=false;
	cin>>cadena;
	for(int i=0; i<cadena.length()-1; i++)
	{
		if (cadena[i]=='=')
		{
			flag=true;
		}
		
		if (flag)
		{
			cDI++;
		}
		
		else
		{
			if (cadena[i]=='+')
			{
				flagM=true;
			}
			
			if (flagM)
			{
				if (cadena[i]=='|')
				{
					cDM++;
				}	
			}
			else
			{
				if (cadena[i]=='|')
				{
					cAM++;
				}	
			}
		}
	}
	
	
	
	if ((abs(( cAM + cDM ) - (cDI)))==2)
	{
		if ((cAM + cDM)<cDI)
		{
			for (int i=0; i<=cAM; i++)
			{
				cout<<"|";
			}			
			cout<<"+";
			for (int i=0; i<cDM; i++)
			{
				cout<<"|";
			}
			cout<<"=";
			for (int i=0; i<cDI-1; i++)
			{
				cout<<"|";
			}
		}
		else
		{
			if(cAM>1)
			{
				for (int i=0; i<cAM-1; i++)
				{
					cout<<"|";
				}			
				cout<<"+";
				for (int i=0; i<cDM; i++)
				{
					cout<<"|";
				}
				cout<<"=";
				for (int i=0; i<=cDI; i++)
				{
					cout<<"|";
				}
			}
			else if(cDM>1)
			{
				
				for (int i=0; i<cAM; i++)
				{
					cout<<"|";
				}			
				cout<<"+";
				for (int i=0; i<cDM-1; i++)
				{
					cout<<"|";
				}
				cout<<"=";
				for (int i=0; i<=cDI; i++)
				{
					cout<<"|";
				}
			}
			else if ((cDM<=1)and(cAM<=1))
			{
				cout<<"Impossible\n";
			}
		}
	}
	else if (cAM+cDM-cDI==0)
	{
		cout<<cadena;
	}
	else
	{
		cout<<"Impossible\n";
	}
	
	return 0;
}
