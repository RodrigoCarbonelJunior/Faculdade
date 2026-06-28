#include <iostream>
#include <sstream>
using namespace std;

class Empregado {
protected:
    string nome;
    float salario;

public:
    Empregado(string n = "", float s = 0.0f) : nome(n), salario(s) {}

    string getNome() const { return nome; }
    void setNome(string n) { nome = n; }

    float getSalario() const { return salario; }
    void setSalario(float s) { salario = s; }

    virtual string toString() const {
        stringstream ss;
        ss << "Nome: " << nome << " | Salário: R$ " << salario;
        return ss.str();
    }
};

class Gerente : public Empregado {
private:
    string departamento;

public:
    Gerente(string n = "", float s = 0.0f, string d = "")
        : Empregado(n, s), departamento(d) {}

    string getDepartamento() const { return departamento; }
    void setDepartamento(string d) { departamento = d; }

    string toString() const override {
        stringstream ss;
        ss << Empregado::toString()
           << " | Departamento: " << departamento;
        return ss.str();
    }
};

class Vendedor : public Empregado {
private:
    float percentualComissao;

public:
    Vendedor(string n = "", float s = 0.0f, float p = 0.0f)
        : Empregado(n, s), percentualComissao(p) {}

    float getPercentualComissao() const { return percentualComissao; }
    void setPercentualComissao(float p) { percentualComissao = p; }

    float calcularSalario() const {
        return salario + (salario * percentualComissao);
    }

    string toString() const override {
        stringstream ss;
        ss << Empregado::toString()
           << " | Percentual de Comissão: " << (percentualComissao * 100) << "%"
           << " | Salário com Comissão: R$ " << calcularSalario();
        return ss.str();
    }
};

int main() {
    Empregado e1("João", 2500.0f);
    Gerente g1("Maria", 5000.0f, "Financeiro");
    Vendedor v1("Carlos", 3000.0f, 0.10f);

    cout << e1.toString() << endl;
    cout << g1.toString() << endl;
    cout << v1.toString() << endl;

    return 0;
}
