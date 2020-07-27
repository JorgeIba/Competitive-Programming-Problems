#include<bits/stdc++.h>
using namespace std;
struct node{
	int to,nex,d;
}e[20010];
int n;
int dp[10010][22],dep[10010];
int dis[10010];
int head[10010],len;
void add(int x,int y,int d)
{
	e[len].to=y;
	e[len].d=d;
	e[len].nex=head[x];
	head[x]=len++;
}
void dfs(int u,int fa)
{
	for(int i=0;i<20;i++)
		if(dp[u][i])
			dp[u][i+1]=dp[dp[u][i]][i];
		else
			break;
	for(int i=head[u];i!=-1;i=e[i].nex)
	{
		int to=e[i].to;
		if(to==fa) continue;
		
		dep[to]=dep[u]+1;
		dp[to][0]=u;
		dis[to]=dis[u]+e[i].d;
	//	cout<<to<<" "<<dis[to]<<endl;
		dfs(to,u);
	}
}
int res1,res2;
int solve(int x,int y)
{
	int flag=1;
	if(dep[x]<dep[y]) swap(x,y),flag=0;
	int cnt=dep[x]-dep[y];
//	cout<<cnt<<endl;
	for(int i=0;i<20;i++)
	{
		if(cnt&(1<<i))
			x=dp[x][i];
	}
//	cout<<x<<" "<<y<<endl;
	int res=0;
	for(int i=20;i>=0;i--)
	{
		if(dp[x][i] != dp[y][i])
		{
			x=dp[x][i];
			y=dp[y][i];
			res+=(1<<i);
		}
	}
	if(x!=y)res++;
	if(flag)
	{
		res1=res+cnt;
		res2=res;
	}
	else
	{
		res1=res;
		res2=res+cnt;
	}
//	cout<<x<<" "<<y<<endl;
	if(x==y) return x;
	return dp[x][0];
}
int sol(int x,int l)
{
//	cout<<x<<" "<<l<<endl;
	for(int i=20;i>=0;i--)
	{
		if(l&(1<<i))
		{
			x=dp[x][i];
		}
	}
	return x;
}
int main()
{
	int T;
	int x,y,d;
	string s;
	int l,r,pos;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		len=0;
		for(int i=0;i<=n;i++)
		{
			for(int j=0;j<=20;j++)
				dp[i][j]=0;
			head[i]=-1;
		}
		for(int i=1;i<=n-1;i++)
		{
			scanf("%d%d%d",&x,&y,&d);
			add(x,y,d);
			add(y,x,d);
		}
		dep[1]=1;
		dis[1]=0;
		dfs(1,0);
		while(cin>>s)
		{
			if(s=="DONE") break;
			if(s=="DIST")
			{
				scanf("%d%d",&l,&r);
				int p=solve(l,r);
//				cout<<dis[l]<<" "<<dis[r]<<" "<<p<<" "<<dis[p]<<endl;
				printf("%d\n",dis[l]+dis[r]-dis[p]*2);
			}
			else
			{
				scanf("%d%d%d",&l,&r,&pos);
				int p=solve(l,r);
				if(res1+1>=pos) printf("%d\n",sol(l,pos-1));
				else printf("%d\n",sol(r,res2+1-(pos-res1)));
			}
		}
		printf("\n");
		
	}
	return 0;
 } 