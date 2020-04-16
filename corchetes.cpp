#include <bits/stdc++.h>
using namespace std;

int main()
{
	stack<char> pila;
	string entrada;
	long long int acumulador=0;
	getline(cin, entrada);
	char letra;
	for (long long int i=0; i<entrada.length(); i++)
	{
		letra=entrada[i];
		if ((letra=='(')or(letra=='{')or(letra=='[')or(letra=='<'))
		{
			pila.push(letra);
		}
		else if ((letra==')')or(letra=='}')or(letra==']')or(letra=='>'))
		{
			if (pila.empty())
			{
				cout<<"imposible\n";
				return 0;
			}
			if ((pila.top()=='(')and(letra==')'))
			{
				pila.pop();
			}
			else if ((pila.top()=='[')and(letra==']'))
			{
				pila.pop();
			}
			else if ((pila.top()=='{')and(letra=='}'))
			{
				pila.pop();
			}
			else if ((pila.top()=='<')and(letra=='>'))
			{
				pila.pop();
			}
			else
			{
				pila.pop();
				acumulador+=1;
			}
		}
	}
	if (pila.empty())
	{
		cout<<acumulador<<endl;
	}
	else
	{
		cout<<"imposible\n";
	}	
	return 0;
}
