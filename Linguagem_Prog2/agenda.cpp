#include <iostream>
#include <string>
using namespace std;

struct pessoa {
    string nome;
    string telefone;
};

void inserirRegistro(pessoa* agenda, int &total, int capacidade) {
    if (total >= capacidade) {
        cout << "Agenda cheia!" << endl;
        return;
    }
    cin.ignore(); 
    cout << "Digite o nome: ";
    getline(cin, agenda[total].nome);

    cout << "Digite o telefone: ";
    getline(cin, agenda[total].telefone);

    total++;
    cout << "Registro inserido com sucesso!" << endl;
}

void removerRegistro(pessoa* agenda, int &total) {
    if (total == 0) {
        cout << "Agenda vazia!" << endl;
        return;
    }

    int indice;
    cout << "Digite o indice (1 ate " << total << ") para remover: ";
    cin >> indice;

    if (indice < 1 || indice > total) {
        cout << "Indice invalido!" << endl;
        return;
    }

    for (int i = indice - 1; i < total - 1; i++) {
        agenda[i] = agenda[i + 1];
    }

    total--;
    cout << "Registro removido com sucesso!" << endl;
}

void pesquisar(pessoa* agenda, int total) {
    if (total == 0) {
        cout << "Agenda vazia!" << endl;
        return;
    }

    cin.ignore();
    string termo;
    cout << "Digite parte do nome para buscar: ";
    getline(cin, termo);

    cout << "--- Resultados da busca ---" << endl;
    bool achou = false;
    for (int i = 0; i < total; i++) {
        if (agenda[i].nome.find(termo) != string::npos) {
            cout << i + 1 << ". " << agenda[i].nome << " - " << agenda[i].telefone << endl;
            achou = true;
        }
    }
    if (!achou) cout << "Nenhum registro encontrado!" << endl;
}

void listarRegistros(pessoa* agenda, int total) {
    if (total == 0) {
        cout << "Agenda vazia!" << endl;
        return;
    }

    cout << "--- Lista de Contatos ---" << endl;
    for (int i = 0; i < total; i++) {
        cout << i + 1 << ". " << agenda[i].nome << " - " << agenda[i].telefone << endl;
    }
}

int main() {
    int capacidade = 100;
    pessoa* agenda = new pessoa[capacidade];
    int total = 0;
    int opcao;

    do {
        cout << "\nAgenda de Contatos" << endl;
        cout << "1. Inserir registro" << endl;
        cout << "2. Remover registro por índice" << endl;
        cout << "3. Pesquisar registros" << endl;
        cout << "4. Listar registros" << endl;
        cout << "5. Sair" << endl;
        cout << "Digite uma das opções acima: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                inserirRegistro(agenda, total, capacidade);
                break;
            case 2:
                removerRegistro(agenda, total);
                break;
            case 3:
                pesquisar(agenda, total);
                break;
            case 4:
                listarRegistros(agenda, total);
                break;
            case 5:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 5);

    delete[] agenda;
    return 0;
}
