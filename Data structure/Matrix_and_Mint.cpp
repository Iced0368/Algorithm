#include <iostream>
#include <cstring>
#define ll long long

using namespace std;

const int mod = 998244353;
int K;

template<int MOD>
struct MINT{
    int v;
    MINT() : v(0) {}
    MINT(ll x) { 
        v = x % MOD;
        if(v < 0) v += MOD;
    }
    friend istream& operator>>(istream &in, MINT& x) { ll t; in >> t; x = MINT(t); return in; }
    friend ostream& operator<<(ostream &out, const MINT& x) { out << x.v; return out; }
    bool operator==(const MINT& b) { return v == b.v; }
    bool operator!=(const MINT& b) { return v != b.v; }
    MINT operator+(const MINT& b) { return v + b.v; }
    MINT operator*(const MINT& b) { return (ll)v * b.v; }
    MINT operator-() { return -v; }
    MINT operator-(const MINT& b) { return v - b.v; }
    MINT& operator+=(const MINT& b) { v = (v+b.v)%MOD; return *this; }
    MINT& operator*=(const MINT& b) { v = ((ll)v*b.v)%MOD; return *this; }
    MINT& operator-=(const MINT& b) { v = (v-b.v)%MOD; if(v < 0) v += MOD; return *this; }
    friend MINT pow(MINT a, ll n){
        MINT res = 1;
        while(n){
            if(n % 2) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }
    friend MINT inv(const MINT& a){ return pow(a, MOD-2); }
    MINT operator/(const MINT& b) { return (ll)v * inv(b).v; }
    MINT operator/=(MINT& b) { v = ((ll)v*inv(b).v)%MOD; return *this; }
};

#define mint MINT<mod>

class Matrix;
Matrix identity();

class Matrix{
public:
    mint m[100][100];

    Matrix() {
        memset(m, 0, sizeof(m));
    }
    
    Matrix operator*(const Matrix& b){
        Matrix output;

        for(int k = 0; k < K; k++)
            for(int i = 0; i < K; i++){
                mint temp = m[i][k];
                for(int j = 0; j < K; j++)
                    output.m[i][j] += temp * b.m[k][j];
            }
        return output;
    }

    Matrix operator*(mint n){
        Matrix output;
        for(int i = 0; i < K; i++)
            for(int j = 0; j < K; j++)
                output.m[i][j] = n*this->m[i][j];
        return output;
    }

    Matrix operator+(const Matrix& b){
        Matrix output;

        for(int i = 0; i < K; i++)
            for(int j = 0; j < K; j++)
                output.m[i][j] = this->m[i][j] + b.m[i][j];
        return output;
    }

    Matrix& operator+=(const Matrix& b){
        for(int i = 0; i < K; i++)
            for(int j = 0; j < K; j++)
                this->m[i][j] += b.m[i][j];
        return *this;
    }
    friend Matrix mpow(Matrix A, ll n){
        Matrix res = identity();
        while(n){
            if(n % 2)
                res = res * A;
            A = A * A;
            n >>= 1;
        }
        return res;
    }

    void print(){
        for(int i = 0; i < K; i++){
            for(int j = 0; j < K; j++)
                cout << this->m[i][j] << ' ';
            cout << '\n';
        }
    }
};


Matrix identity(){
    Matrix output;
    for(int i = 0; i < K; i++)
        output.m[i][i] = 1;
    return output;
}
