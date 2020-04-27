#include <bits/stdc++.h>
#define lli long long int
using namespace std;

char contrario(char a)
{
    if(a=='0') return '1';
    if(a=='1') return '0';
}



int main()
{
    lli t; cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        lli n = s.length();
        bool cero = false;
        bool uno = false;
        for(char c: s)
        {
            if(c=='0') cero =true;
            else uno = true;
        }

        if( !(cero && uno) )
        {
            cout<<s<<endl;
        }
        else
        {
            string res(2*n, '0');
            //cout<<res<<endl;
            for(int i = 0; i<2*n; i++)
            {
                if(i==0)
                {
                    res[i] = s[i];
                } 
                else
                {
                    res[i] = contrario(res[i-1]);
                }
            }
            cout<<res<<endl;
        }


    }
    return 0;
}