#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
string simplif="";

int main ()
{
	string cadena;
	cin>>cadena;
	for (int i=1; i<cadena.length(); i++) 
	{
		cout<<cadena[i]<<" "<<cadena[i-1]<<endl;
		
		if ((cadena[i]=='v')&&(cadena[i-1]=='v'))
		{
			simplif+="w";
		}
		if (cadena[i]=='o')
		{
			simplif+="o";
		}
	}
	cout<<simplif<<endl;

	return 0;
}
