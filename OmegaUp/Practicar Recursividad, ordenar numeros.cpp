#include <bits/stdc++.h>

using namespace std;

void swap (vector <int> &arreglo, int posicionMayor, int liminf)
{
	int temp=arreglo[posicionMayor];
	arreglo[posicionMayor]=arreglo[liminf];
	arreglo[liminf]=temp;
	return;
}

void ordenarArreglo(vector<int> &arreglo, int liminf, int limsup)
{
	int mayor=0;
	int posicionMayor=0;
	for (int i=liminf; i<limsup; i++)
	{
		if (arreglo[i]>mayor)
		{
			mayor=arreglo[i];
			posicionMayor=i;
		}
	}
	swap(arreglo, posicionMayor, liminf);
	
	if (liminf<(limsup-1))		
	{
		ordenarArreglo(arreglo, liminf+1, limsup);
	}
	else
	{
		return;
	}
}

int main()
{
	int n=0, num=0;
	cin>>n;
	vector <int> array;
	for (int i=0; i<n; i++)
	{
		cin>>num;
		array.push_back(num);
	}
	
	ordenarArreglo(array,0,n);
	
	for (int x=0; x<n; x++)
	{
		cout<<array[x]<<" ";
	}
	
	return 0;
}
