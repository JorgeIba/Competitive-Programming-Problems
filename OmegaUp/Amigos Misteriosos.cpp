#include <bits/stdc++.h>
using namespace std;
int main()
{
    string bi;
    bool flag=true;
    while (getline(cin,bi))
    {
    	    
	    for(int i=0; i<bi.length(); i++)
	    {
	        if(bi[i]==97)
			{
	        bi[i]=120;
	        }
	        else if(bi[i]==101)
			{
	        bi[i]=119;
	        }
	        else if(bi[i]==105)
			{
	        bi[i]=121;
	        }
	        else if(bi[i]==111)
			{
	        bi[i]=107;
	        }
	        else if(bi[i]==117)
			{
	        bi[i]=122;
	        }
	        else if (bi[i]=='.')
	        {
	        	flag=false;
			}
		}
	cout<<bi<<endl;
	}
   return 0;
}
