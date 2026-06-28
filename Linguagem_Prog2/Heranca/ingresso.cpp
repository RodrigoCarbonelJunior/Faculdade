#include <iostream>
#include <sstream>
using namespace std;

class Ingresso {
protected:
    float valor;

public:
    Ingresso(float v = 0.0) : valor(v) {}

    virtual string toString() const {
        stringstream ss;
        ss << "Valor do ingresso: R$ " << valor;
        return ss.str();
    }
};

class IngressoVIP : public Ingresso {
private:
    float valorAdicional;

public:
    IngressoVIP(float v = 0.0, float adicional = 0.0)
        : Ingresso(v), valorAdicional(adicional) {}

    string toString() const override {
        stringstream ss;
        ss << "Valor do ingresso VIP: R$ " << (valor + valorAdicional);
        return ss.str();
    }
};

int main() {
    Ingresso normal(20.0);
    IngressoVIP vip(20.0, 15.0);

    cout << normal.toString() << endl;
    cout << vip.toString() << endl;

    return 0;
}
