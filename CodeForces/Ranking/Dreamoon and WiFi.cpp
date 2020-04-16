#include <bits/stdc++.h>
#define lli long long int 
using namespace std;

lli pos1=0,neg1=0;
string s1, s2;
lli contadorSig=0;

lli solve(lli contPos, lli contNeg, lli indice)
{
	//cout<<"contPos "<<contPos<<" contNeg "<<contNeg<<" indice "<<indice<<endl;
	if((contPos == pos1)and(contNeg==neg1)and(indice==s2.length()))
	{
		return 1;
	}
	if(indice>=s2.length())
	{
		return 0;
	}
	switch(s2[indice])
	{
		case '+':
			return solve(contPos+1, contNeg, indice+1);
			break;
		case '-':
			return solve(contPos, contNeg+1, indice+1);
			break;
		default:
			return solve(contPos, contNeg+1, indice+1) + solve(contPos+1, contNeg, indice+1);
			break;
	}
	
}

int main()
{
	cin>>s1>>s2;
	for(int i=0; i<s1.length(); i++)
	{
		if(s1[i]=='+')
		{
			pos1++;
		}
		else if (s1[i]=='-')
		{
			neg1++;
		}
	}
	
	for(int i=0; i<s2.length(); i++)
	{
		if(s2[i]=='?')
		{
			contadorSig++;
		}
	}
	long double res = solve(0,0,0)/(pow(2,contadorSig));
	
	cout<<fixed<<setprecision(13)<<res<<endl;


	
	
	return 0;
}
