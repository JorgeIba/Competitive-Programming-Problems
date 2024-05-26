#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;



vector<string> chemical_element = {
    "__", "H", "He", 
    "Li", "Be", "B", "C", "N", "O", "F", "Ne",
    "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
    "K",  "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
    "Rb", "Sr", "Y",  "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe",
    "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb",
    "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn",
    "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No",
    "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og",
};


vector<string> ans;
string s;

void f(int idx, string &aux) {
    if(idx == (int) s.length()) {
        ans.push_back(aux);
        return;
    }
    
    for(int i = 1; i <= 3; i++) {
        if(idx + i - 1 >= (int)s.length()) continue;

        string sub = s.substr(idx, i);
        if(sub[0] == '0') continue;

        int idx_element = stoi(sub);
        if( idx_element < 1 || idx_element >= SZ(chemical_element) ) continue;

        string next = aux + chemical_element[idx_element];
        f(idx+i, next);
    }

}


int main () {
	// fastIO();

    while(cin>>s) {
        ans.clear();
        string aux;
        f(0, aux);

        if(SZ(ans)) {
            for(auto x: ans) cout << x << endl;
        }
        else {
            cout << "$" << endl;
        }
    }

	return 0;
}

