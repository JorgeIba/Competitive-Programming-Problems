#include <bits/stdc++.h>
#define lli long long int

using namespace std;


bool check( vector< pair<int,int> > divs, lli num  )
{
    for(auto par: divs)
    {
        unordered_map<char, int> checkSet;
        string div1 = to_string(par.first);
        string div2 = to_string(par.second);
        string numS = to_string(num);
        bool cero = false;
        for(auto c: div1)
        {
            if(c=='0') cero = true;
            checkSet[c]++;
        }
        for(auto c: div2)
        {
            if(c=='0') cero = true;
            checkSet[c]++;
        }
        for(auto c: numS)
        {
            if(c=='0') cero = true;
            checkSet[c]++;
        }
        if(checkSet.size() == 9 and !cero)
        {
            bool flag = true;
            for(auto x: checkSet)
            {
                if(x.second > 1)
                {
                    flag=false;
                    break;
                }
            }
            if(flag) 
            {
                return true;
            }
        }
    }
    return false;
}


vector< pair<int,int> > desc(lli n)
{
    vector< pair<int,int> > res;
    for(lli i = 2; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            res.emplace_back(i, n/i);
        }
    }
    return res;
}



int main()
{
    vector< vector< pair<int,int> > > divisores(50005);
    for(int i = 1000; i< 10000; i++)
    {
        divisores[i] = desc(i);
    }
    lli contador = 0;
    for(int i = 1000; i<10000; i++)
    {
        if(check(divisores[i], i))
        {
            contador+= i;
        }
    }
    cout<<contador<<endl;

    return 0;
}