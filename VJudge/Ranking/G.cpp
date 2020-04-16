#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector< pair<string, lli> > cerouno;
    vector< pair<string, lli> > unocero;
    set<string> checkcerouno;
    set<string> checkunocero;
    bool unouno = false;
    bool cerocero = false;

    for(int i=0; i<n; i++)
    {
        string cadena; 
        cin>>cadena;
        char as = cadena[0];        
        char bs = cadena[cadena.length() - 1];
        string aux2  = "";
        aux2+=as;
        aux2+=bs;
        //string aux2 = as + bs;
        if(aux2 == "00")
        {
            cerocero = true;
        }
        else if(aux2 == "11")
        {
            unouno = true;
        }
        else if(aux2 == "01")
        {
            cerouno.push_back( make_pair(cadena, i+1) );
            checkcerouno.insert(cadena);
        }
        else
        {
            unocero.push_back( make_pair(cadena, i+1)    );
            checkunocero.insert(cadena);
        }
        //cout<<aux2<<endl;
    }
    lli size1 = cerouno.size();
    lli size2 = unocero.size();
    if((cerocero == true) and (unouno == true) and (size1 ==0) and (size2==0) )
    {
        cout<<-1<<endl;
        return;
    }
   
    lli diff = abs(size1 - size2) - 1;
    if(diff > 0)
    {
        
        if(size1 > size2)
        {
            
            lli necesito = (size1 - size2)/2;
            vector<lli> res;
            lli llevo = 0;
            for(int i=0; i<size1; i++)
            {
                string aux = cerouno[i].first;
                reverse(aux.begin(), aux.end());
                //cout<<aux<<" ";
                if(checkunocero.find(aux) == checkunocero.end())
                {
                    checkunocero.insert(aux);
                    res.push_back(cerouno[i].second);
                    llevo++;
                }
                if(llevo == necesito)
                {
                    cout<<llevo<<endl;
                    for(auto x: res)
                    {
                        cout<<x<<" ";
                    }
                    cout<<endl;
                    return;
                }
            }
            cout<<-1<<endl;
            //cout<<llevo<<" "<<necesito<<endl;
            
            return;
        }
        else
        { 
            lli necesito = (size2 - size1)/2;
            vector<lli> res;
            lli llevo = 0;
            for(int i=0; i<size2; i++)
            {
                string aux = unocero[i].first;
                reverse(aux.begin(), aux.end());
                //cout<<aux<<" ";
                if(checkcerouno.find(aux) == checkcerouno.end())
                {
                    checkcerouno.insert(aux);
                    res.push_back(unocero[i].second);
                    llevo++;
                }
                if(llevo == necesito)
                {
                    cout<<llevo<<endl;
                    for(auto x: res)
                    {
                        cout<<x<<" ";
                    }
                    cout<<endl;
                    return;
                }
            }
            cout<<-1<<endl;
            //cout<<llevo<<" "<<necesito<<endl;
            
            return;
        }
        
    }

    else
    {
        cout<<0<<endl<<endl;
    }
    

}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}