#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	vector<int> num1;
	vector<int> num2;
	vector<int> num3;
	int num=0, n=0, acarreo=0, suma=0, decimal=0, acumulador=0;
	cin>>n;
	for (int i=n; i>0; --i)
	{
		cin>>num;
		num1.push_back(num);
		num3.push_back(num);
	}
	
	for (int x=n; x>0; --x)
	{
		cin>>num;
		num2.push_back(num);
	}
	
	for (int q=n-1; q>=0; q--)
	{
		suma=num1[q] + num2[q] + acarreo;
		acarreo=0;
		decimal=suma%10;
		suma>=10?acarreo=1:acarreo=0;
		
		if (q!=0)
		{
			num3[q]=decimal;
			suma=0;
		}
		else
		{
			cout<<suma;
		}
		
	}
	for (int a=1; a<n; a++)
	{
		cout<<num3[a];
	}
	
	return 0;
}
