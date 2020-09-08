#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli izq1,aba1,der1,arr1;
lli izq2, aba2, der2, arr2;
lli izq3, aba3, der3, arr3;

bool cubrirTotal2()
{
	if( izq2 <= izq1 && aba2 <= aba1 && der2 >= der1 && arr2 >= arr1   )
	{
		cout<<"NO\n";
		return false;
	}
	return true;
}

bool cubrirTotal3()
{
	if( izq3 <= izq1 && aba3 <= aba1 && der3 >= der1 && arr3 >= arr1   )
	{
		cout<<"NO\n";
		return false;
	}
	return true;
}

int main()
{
	
	cin>>izq1>>aba1>>der1>>arr1;
	
	cin>>izq2>>aba2>>der2>>arr2;
	
	cin>>izq3>>aba3>>der3>>arr3;
	
	
	
	lli contador2=0;
	if ( izq2 > izq1)
	{
		contador2++;
	}
	if( aba2 > aba1 )
	{
		contador2++;
	}
	if ( der2 < der1 )
	{
		contador2++;
	}
	if (arr2 < arr1)
	{
		contador2++;
	}
	
	if(contador2>1)
	{
		if(!cubrirTotal3())
		{
			return 0;
		}
	}
	
	///////////////
	
	lli contador3=0;
	if ( izq3 > izq1)
	{
		contador2++;
	}
	if( aba3 > aba1 )
	{
		contador2++;
	}
	if ( der3 < der1 )
	{
		contador2++;
	}
	if (arr3 < arr1)
	{
		contador2++;
	}
	
	if(contador3>1)
	{
		if(!cubrirTotal2())
		{
			return 0;
		}
	}
	
	////////////////////
	
	if(  )
	
	
	
	
	
	
	
	
	
	return 0;
}
