#include "funcionario.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<Funcionario*> qpessoal;
    qpessoal.push_back(new Gerente("Tobias Teixeira", 18000, 2));
    qpessoal.push_back(new Crediario("Anelise Vicente", 6200, 3));
    qpessoal.push_back(new Vendedor("Roberto Pacheco", 2500, 0));
    qpessoal.push_back(new Vendedor("Andreia Macedo", 2500, 1));
    qpessoal.push_back(new Vendedor("Pedro Silva", 2500, 0));

    // 3% de comissão somados no salário bruto - somente vendedores
    qpessoal.at(4)->SetVendas(135400);
    qpessoal.at(3)->SetVendas(256900);
    qpessoal.at(2)->SetVendas(81250);

    // pagamento de bônus somados no salário bruto
    qpessoal.at(4)->SetBonus(300); // bonus de funcionário feliz - qualquer funcionário
    qpessoal.at(3)->SetBonus(250); // bonus de matador de baratas - qualquer funcionário
    qpessoal.at(1)->SetBonus(473550*0.0025); // bonus vendas loja (0.25%) - somente crediário
    qpessoal.at(0)->SetBonus(473550*0.01);   // bonus vendas loja (1%) - somente gerente

    // rodando folha de pagamento
    for (size_t i = 0; i < qpessoal.size(); i++)
        qpessoal.at(i)->CalcularSalario();

    // imprimindo contra-cheques
    for (size_t i = 0; i < qpessoal.size(); i++)
        cout << qpessoal.at(i)->ImprimirFolhaPagamento() << endl;

    for (size_t i = 0; i < qpessoal.size(); i++)
        delete qpessoal.at(i);

    return 0;
}
