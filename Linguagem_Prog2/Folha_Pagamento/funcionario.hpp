#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Funcionario
{
protected:
    string nome;
    double salarioBase;
    int dependentes;
    double bonus;
    double salarioBruto;
    double descontos;
    double salarioLiquido;

public:
    Funcionario(const string& n, double s, int d)
        : nome(n), salarioBase(s), dependentes(d), bonus(0.0),
          salarioBruto(0.0), descontos(0.0), salarioLiquido(0.0) {}
    virtual ~Funcionario() {}

    void SetBonus(double b) { bonus = b; }
    virtual void SetVendas(double) {}

    virtual void CalcularSalario() = 0;
    virtual string ImprimirFolhaPagamento() const = 0;

protected:
    static double desconto(double bruto)
    {
        if (bruto > 20000) return 0.35;
        if (bruto > 10000) return 0.20;
        if (bruto > 5000)  return 0.10;
        return 0.05;
    }
};

class Gerente : public Funcionario
{
public:
    Gerente(const string& n, double s, int d) : Funcionario(n,s,d) {}

    void CalcularSalario() override
    {
        salarioBruto = salarioBase + bonus + dependentes*500;
        descontos = salarioBruto * desconto(salarioBruto);
        salarioLiquido = salarioBruto - descontos;
    }

    string ImprimirFolhaPagamento() const override
    {
        ostringstream oss;
        oss<<fixed<<setprecision(2);
        oss<<"Funcionario: "<<nome
           <<" Salario Bruto: "<<salarioBruto
           <<" Descontos: "<<descontos
           <<" Salario Liquido: "<<salarioLiquido;
        return oss.str();
    }
};

class Crediario : public Funcionario
{
public:
    Crediario(const string& n, double s, int d) : Funcionario(n,s,d) {}

    void CalcularSalario() override
    {
        salarioBruto = salarioBase + bonus + dependentes*300;
        descontos = salarioBruto * desconto(salarioBruto);
        salarioLiquido = salarioBruto - descontos;
    }

    string ImprimirFolhaPagamento() const override
    {
        ostringstream oss;
        oss<<fixed<<setprecision(2);
        oss<<"Funcionario: "<<nome
           <<" Salario Bruto: "<<salarioBruto
           <<" Descontos: "<<descontos
           <<" Salario Liquido: "<<salarioLiquido;
        return oss.str();
    }
};

class Vendedor : public Funcionario
{
private:
    double vendas;
public:
    Vendedor(const string& n, double s, int d) : Funcionario(n,s,d), vendas(0.0) {}

    void SetVendas(double v) override { vendas = v; }

    void CalcularSalario() override
    {
        salarioBruto = salarioBase + bonus + dependentes*300 + vendas*0.03;
        descontos = salarioBruto * desconto(salarioBruto);
        salarioLiquido = salarioBruto - descontos;
    }

    string ImprimirFolhaPagamento() const override
    {
        ostringstream oss;
        oss<<fixed<<setprecision(2);
        oss<<"Funcionario: "<<nome
           <<" Salario Bruto: "<<salarioBruto
           <<" Descontos: "<<descontos
           <<" Salario Liquido: "<<salarioLiquido;
        return oss.str();
    }
};
