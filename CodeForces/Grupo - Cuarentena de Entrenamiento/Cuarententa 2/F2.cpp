#include<bits/stdc++.h> 
#define lli long long int
#define ll long long int
using namespace std; 

 
const lli MOD = 998244353;

bool igual(long double a, long double b){
    return abs(a - b) < 1e-9;
}

struct polinomio{
    vector<ll> coeficientes;
    polinomio(){
        coeficientes.push_back(0);
    }
    polinomio(vector<ll> coef){
        for(ll x : coef) coeficientes.push_back(x);
        quitar_ceros();
    }
    polinomio(ll x0){
        coeficientes.push_back(x0);
    }
    size_t grado() const{
        return coeficientes.size() - 1;
    }
    void quitar_ceros(){
        while(coeficientes.size() && coeficientes.back() == 0){
            coeficientes.pop_back();
        }
        if(coeficientes.size() == 0) coeficientes.push_back(0);
    }
    polinomio operator+(const polinomio& p) const{
        size_t g = max(grado(), p.grado());
        vector<ll> nuevos(g + 1, 0);
        for(size_t i = 0; i <= g; i++){
            if(i <= coeficientes.size() - 1) nuevos[i] += coeficientes[i];
            if(i <= p.coeficientes.size() - 1) nuevos[i] += p.coeficientes[i];
        }
        return polinomio(nuevos);
    }
    polinomio operator-() const{
        size_t g = grado();
        vector<ll> nuevos(g + 1);
        for(size_t i = 0; i <= g; i++) nuevos[i] = -coeficientes[i];
        return polinomio(nuevos);
    }
    polinomio operator-(const polinomio& p) const{
        return *this + (-p);
    }
    polinomio operator*(const polinomio& p) const{
        size_t g = grado() + p.grado();
        vector<ll> nuevos(g + 1, 0);
        for(size_t i = 0; i <= grado(); i++){
            for(size_t j = 0; j <= p.grado(); j++){
                nuevos[i + j] += coeficientes[i] * p.coeficientes[j];
            }
        }
        return polinomio(nuevos);
    }
    polinomio operator*(const ll& f) const{
        size_t g = grado();
        vector<ll> nuevos(g + 1);
        for(size_t i = 0; i <= g; i++) nuevos[i] = f * coeficientes[i];
        return polinomio(nuevos);
    }
    pair<polinomio, polinomio> operator/(const polinomio& B) const{
        polinomio Q, R;
        Q = 0;
        R = polinomio(coeficientes);
        while(R.grado() >= B.grado() && !(R.grado() == 0 && R.coeficientes[0] == 0)){
            ll q = R.coeficientes[R.grado()] / B.coeficientes[B.grado()];
            size_t g = R.grado() - B.grado();
            vector<ll> tmp(g + 1, 0);
            tmp[g] = q;
            polinomio nuevo(tmp);
            Q += nuevo;
            R -= B*nuevo;
        }
        return make_pair(Q, R);
    }
    polinomio operator+=(const polinomio& p){
        *this = *this + p;
        return *this;
    }
    polinomio operator-=(const polinomio& p){
        *this = *this - p;
        return *this;
    }
    polinomio operator*=(const polinomio& p){
        *this = *this * p;
        return *this;
    }
    polinomio operator*=(const ll& f){
        *this = *this * f;
        return *this;
    }
    ll evaluar(ll x0){
        ll ans = 0;
        for(auto it = coeficientes.rbegin(); it != coeficientes.rend(); ++it){
            ans = ans * x0 + (*it);
        }
        return ans;
    }
    
};

 
polinomio interpolar(vector< pair<lli, lli> > puntos){
    polinomio ans = 0;
    for(size_t i = 0; i < puntos.size(); i++){
        lli k = puntos[i].second;
        polinomio p = 1;
        for(size_t j = 0; j < puntos.size(); j++){
            if(i != j){
                p *= polinomio(vector<lli>{-puntos[j].first, 1});
                k /= puntos[i].first - puntos[j].first;
            }
        }
        ans += p * k;
    }
    return ans;
}
  
int main() 
{ 
    lli n; cin>>n;
    vector< pair<lli,lli> > points(n);
    for(int i = 0; i< n; i++)
    {
        points[i].first = i+1;
        cin>>points[i].second;
        //cin>>p.first>>p.second;
    }
    auto res = interpolar(points);
    cout<<res.evaluar(0)<<endl;
    /*
    for(int i = 1; i< n; i++)
    {
        if(res == interpolate(0,i))
        {
            cout<<i<<" "<<res<<endl;
            return 0;
        }
    }
    cout<<n<<" "<<res<<endl;
    */
    return 0; 
} 