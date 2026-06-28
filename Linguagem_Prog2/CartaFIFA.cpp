#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Time;

class Jogador 
{
protected:
    string nome;
    int idade;
    char posicao;
    int forca;
    int velocidade;
    int habilidade;
    Time* clube;
public:
    Jogador(const string& nome_, int idade_, char posicao_, int forca_, int velocidade_, int habilidade_)
        : nome(nome_), idade(idade_), posicao(toupper(posicao_)), forca(forca_), velocidade(velocidade_), habilidade(habilidade_), clube(nullptr) {}
    virtual ~Jogador() {}
    string GetNome() const { return nome; }
    int GetIdade() const { return idade; }
    char GetPosicao() const { return posicao; }
    int GetForca() const { return forca; }
    int GetVelocidade() const { return velocidade; }
    int GetHabilidade() const { return habilidade; }
    Time* GetClube() const { return clube; }
    void SetClube(Time* t) { clube = t; }
    string PosicaoTexto() const 
    {
        switch (posicao) 
        {
            case 'G': return "Goleiro";
            case 'D': return "Defesa";
            case 'M': return "Meio";
            case 'A': return "Atacante";
            default: return "Desconhecida";
        }
    }
    virtual void Mostrar() const 
    {
        cout << nome << " - " << idade << " anos - " << PosicaoTexto()
             << " - Força: " << forca << " - Velocidade: " << velocidade
             << " - Habilidade: " << habilidade << "\n";
    }
};

class Goleiro : public Jogador 
{
public:
    Goleiro(const string& n, int id, int f, int v, int h) : Jogador(n, id, 'G', f, v, h) {}
};
class Defesa : public Jogador 
{
public:
    Defesa(const string& n, int id, int f, int v, int h) : Jogador(n, id, 'D', f, v, h) {}
};
class Meio : public Jogador 
{
public:
    Meio(const string& n, int id, int f, int v, int h) : Jogador(n, id, 'M', f, v, h) {}
};
class Atacante : public Jogador 
{
public:
    Atacante(const string& n, int id, int f, int v, int h) : Jogador(n, id, 'A', f, v, h) {}
};

class Time 
{
private:
    string nome;
    int anoFundacao;
    vector<Jogador*> elenco;
public:
    Time(const string& nome_, int ano_) : nome(nome_), anoFundacao(ano_) {}
    ~Time() { elenco.clear(); }
    string GetNome() const { return nome; }
    int GetAno() const { return anoFundacao; }
    void AdicionarJogador(Jogador* j) 
    {
        if (!j) return;
        auto it = find(elenco.begin(), elenco.end(), j);
        if (it == elenco.end()) 
        {
            elenco.push_back(j);
            j->SetClube(this);
        }
    }
    void RemoverJogador(Jogador* j) 
    {
        if (!j) return;
        auto it = find(elenco.begin(), elenco.end(), j);
        if (it != elenco.end()) 
        {
            elenco.erase(it);
            j->SetClube(nullptr);
        }
    }
    void MostrarJogadores() const 
    {
        for (auto j : elenco) {
            if (j) 
            {
                j->Mostrar();
                cout << "\n";
            }
        }
    }
};

int LerInteiro(const string& prompt) 
{
    int x;
    while (true) 
    {
        cout << prompt;
        if (cin >> x) 
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        } else 
        {
            cin.clear();
            string dummy;
            getline(cin, dummy);
            cout << "Entrada invalida. Tente novamente.\n";
        }
    }
}

int main() 
{
    vector<Jogador*> Jogadores;
    vector<Time*> Times;

    while (true) 
    {
        cout << "\nUFSC SOCCER MANAGER SYSTEM\n";
        cout << "1. Criar Jogador\n";
        cout << "2. Criar Time\n";
        cout << "3. Associar Jogadores a um Time\n";
        cout << "4. Relatorios\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";

        int opc;
        if (!(cin >> opc)) 
        {
            cin.clear();
            string dummy;
            getline(cin, dummy);
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opc == 0) 
        {
            break;
        } else if (opc == 1) 
        {
            string nome;
            cout << "\nNome do jogador: ";
            getline(cin, nome);
            int idade = LerInteiro("Idade: ");
            char pos;
            cout << "Posicao (G,D,M,A): ";
            cin >> pos;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int forca = LerInteiro("Força: ");
            int velocidade = LerInteiro("Velocidade: ");
            int habilidade = LerInteiro("Habilidade: ");
            Jogador* novo = nullptr;
            char P = toupper(pos);
            if (P == 'G') novo = new Goleiro(nome, idade, forca, velocidade, habilidade);
            else if (P == 'D') novo = new Defesa(nome, idade, forca, velocidade, habilidade);
            else if (P == 'M') novo = new Meio(nome, idade, forca, velocidade, habilidade);
            else if (P == 'A') novo = new Atacante(nome, idade, forca, velocidade, habilidade);
            else novo = new Jogador(nome, idade, P, forca, velocidade, habilidade);
            Jogadores.push_back(novo);
            cout << "\nJogador criado com indice [" << (int)Jogadores.size()-1 << "].\n";
        } else if (opc == 2) 
        {
            string nomeTime;
            cout << "\nNome do time: ";
            getline(cin, nomeTime);
            int ano = LerInteiro("Ano de fundacao: ");
            Time* t = new Time(nomeTime, ano);
            Times.push_back(t);
            cout << "\nTime criado com indice [" << (int)Times.size()-1 << "].\n";
        } else if (opc == 3) 
        {
            if (Jogadores.empty() || Times.empty()) 
            {
                cout << "\nNenhum jogador ou time cadastrado.\n";
                continue;
            }
            while (true) 
            {
                cout << "\nJogadores:\n";
                for (size_t i = 0; i < Jogadores.size(); ++i)
                    cout << "[" << i << "] " << Jogadores[i]->GetNome() << "\n";
                cout << "\nTimes:\n";
                for (size_t i = 0; i < Times.size(); ++i)
                    cout << "[" << i << "] " << Times[i]->GetNome() << "\n";
                cout << "\nDigite o indice do jogador (-1 para voltar): ";
                int pIdx;
                if (!(cin >> pIdx)) 
                {
                    cin.clear();
                    string dummy;
                    getline(cin, dummy);
                    continue;
                }
                if (pIdx == -1) 
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Digite o indice do time: ";
                int tIdx;
                if (!(cin >> tIdx)) 
                {
                    cin.clear();
                    string dummy;
                    getline(cin, dummy);
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (pIdx < 0 || pIdx >= (int)Jogadores.size() || tIdx < 0 || tIdx >= (int)Times.size()) 
                {
                    cout << "Índices inválidos.\n";
                    continue;
                }
                Jogador* jogador = Jogadores[pIdx];
                Time* novoTime = Times[tIdx];
                Time* antigo = jogador->GetClube();
                if (antigo) antigo->RemoverJogador(jogador);
                novoTime->AdicionarJogador(jogador);
                cout << "Jogador associado com sucesso.\n";
            }
        } else if (opc == 4) 
        {
            cout << "RELATORIO DE JOGADORES E TIMES\n";
            cout << "Jogadores cadastrados:\n";
            if (Jogadores.empty()) 
            {
                cout << "(nenhum jogador)\n";
            } else {
                for (size_t i = 0; i < Jogadores.size(); ++i) 
                {
                    cout << "[" << i << "] ";
                    Jogadores[i]->Mostrar();
                    cout << "\n";
                }
            }
            cout << "----------------------------------------\n";
            cout << "Times cadastrados:\n";
            if (Times.empty()) {
                cout << "(nenhum time)\n";
            } else 
            {
                for (size_t i = 0; i < Times.size(); ++i) 
                {
                    cout << "Time: [" << i << "] " << Times[i]->GetNome() << " – fundado em " << Times[i]->GetAno() << "\n\n";
                }
            }
            cout << "Pressione ENTER para voltar ao menu...";
            string espera;
            getline(cin, espera);
        } else {
            cout << "\nOpcao invalida.\n";
        }
    }

    for (auto j : Jogadores) delete j;
    Jogadores.clear();
    for (auto t : Times) delete t;
    Times.clear();
    cout << "Encerrando.";
    return 0;
}
