#include <bits/stdc++.h>
using namespace std;


stack<int> pila1;
stack<int> pila2;

void funcion1(int n)
{
	vector<int> numeros(n);
	for (int i=0; i<n; i++)
	{
		cin>>numeros[i];
	}
	
	for (int i=n-1; i>=0; i--)
	{
		if (pila1.empty())
		{
			pila1.push(numeros[i]);	
		}
		else
		{
			if ((numeros[i]) > pila1.top())
			{
				pila1.pop();
				pila1.push(numeros[i]);
			}
			else
			{
				pila1.push(numeros[i]);
			}
		}
	}
	int temp2;
	bool flag=false;
	
	while (!pila1.empty())
	{
		if (pila2.emtpy())
		{
			pila2.push(pila1.top());	
			pila1.pop();
		}
		else
		{
			
			if (flag)
			{
				if (temp2>pila1.top())
				{
					temp2=pila1.top();
					pila1.pop();
				}
				else
				{
					pila2.push(pila1.top);
					flag=false;
				}
				
			}
			else
			{
				if (pila1.top>pila2.top())
				{
					pila2.push(pila1.top());
					pila1.pop();
				}
				else
				{
					flag=true;
					temp2=pila1.top();
					pila1.pop();
				}	
			}
			
		}
		
		pila1.pop();
	}
	
	
	
}



int main()
{
	int n;
	cin>>n;
	funcion1(n);
	return 0;
}
