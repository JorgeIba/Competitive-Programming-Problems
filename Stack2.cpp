#include <bits/stdc++.h>
using namespace std;

bool isMatch(char current, char topStack)
{
    if( (current == ']') and (topStack == '[') )
    {
        return true;
    }
    else if ( (current == '}') and (topStack == '{') )
    {
        return true;
    }
    else if ( (current == ')') and (topStack == '(') )
    {
        return true;
    }
    else
    {
        return false;
    }
    
        

}

string checkBrackets(string stringToCheck)
{
    stack<char> openBrackets;
    for(int i=0; i<stringToCheck.length(); i++)
    {
        char current = stringToCheck[i];
        if( (current == '[') or (current == '{') or (current == '('))
        {
            openBrackets.push(current);
        }
        else
        {
            if(!openBrackets.empty() and  isMatch(current, openBrackets.top()))
            {
                openBrackets.pop();
            }
            else
            {
                return "NO";
            }
        }
    }


    if(openBrackets.empty())
    {
        return "YES";
    }
    else
    {
        return "NO";
    }
    



}




int main()
{
    int n; cin>>n;
    while(n--)
    {
        string stringToCheck; cin>>stringToCheck;
        string res =  checkBrackets(stringToCheck);
        cout<<res<<endl;
    }


    return 0;
}