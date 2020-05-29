#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

struct Node{
  lli value;
  Node *l, *r; //l->0, r->1
};

void insert(Node *root, lli num)
{
	Node *tmp = root;
	for(int i = 50; i>=0; i--)
	{
		bool val = num & (i<<i);
		if(!val)
		{
			if(!tmp->l)
				tmp->l = new Node();
			
			tmp = tmp->l;
		}
		else
		{
			if(!tmp->r)
				tmp->r = new Node();

			tmp = tmp->r;
		}
	}
	tmp->value = num;
}


lli query(Node *root, lli n)
{
	Node *tmp = root;
	for(int i = 50; i>=0; i--)
	{
		bool val = n & (1<<i);
		if(val) //val == 1
		{
			if(tmp->l)
				tmp = tmp->l;
			else
				tmp = tmp->r;
		}
		else
		{
			if(tmp->r)
				tmp = tmp->r;
			else
				tmp = tmp->l;
		}
	}
	return n ^ (tmp->value);
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	lli n; cin>>n;
	vector<lli> nums(n);
	for(auto &x: nums)
	{
		cin>>x;
	}
	Node *root = new Node();
	lli res = 0;
	for(auto x: nums)
	{
		insert(root, x);
	}
	for(auto x: nums)
	{
		res = max(res, query(root,x));
	}

	cout<<res<<endl;


  return 0;
}

