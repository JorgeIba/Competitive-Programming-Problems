#include <bits/stdc++.h>
using namespace std;

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n=0;
	vector<int> vector1;
	vector<int> vector2;
	for (int i=0; i<3; i++)
	{
		cin>>n;
		vector1.push_back(n);
	}

	for (int i=0; i<3; i++)
	{
		cin>>n;
		vector2.push_back(n);
	}	
	sort(vector1.begin(), vector1.end());
	sort(vector2.begin(), vector2.end());
	for (int i=0; i<3; i++)
	{
		if (vector1[i]>vector2[i])
		{
			cout<<0;
			return 0;
		}
	}
	cout<<1;
	return 0;
}
