#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

vector<pair<char,char>> ExtractTable(string &encrypted) {
    vector<pair<char,char>> table;
    for (size_t i = 0; i < encrypted.size();) {
        if (encrypted[i] == '[' && i + 3 < encrypted.size() && encrypted[i+3] == ']') {
            char orig = encrypted[i+1];
            char code = encrypted[i+2];
            table.push_back({(unsigned char)orig, (unsigned char)code});
            encrypted.erase(i, 4); 
        } else {
            i++;
        }
    }
    return table;
}


string Decrypt(const vector<pair<char,char>> &table, const string &inputText) {
    string decoded;
    for (char c : inputText) {
        auto it = find_if(table.begin(), table.end(), [&](auto &p) {
            return p.second == c;
        });
        if (it != table.end()) {
            decoded += it->first;
        } else {
            decoded += c;
        }
    }
    return decoded;
}

int main() {
    ifstream fin("encrypted.txt");
    if (!fin.is_open()) {
        cerr << "Erro ao abrir encrypted.txt" << endl;
        return 1;
    }

    string encryptedText((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();

    vector<pair<char,char>> table = ExtractTable(encryptedText);


    ofstream fkeys("keys.txt");
    for (auto &p : table) {
        fkeys << p.first << " -> " << p.second << "\n";
    }
    fkeys.close();

    string decoded = Decrypt(table, encryptedText);

    ofstream fout("decrypted.txt");
    fout << decoded;
    fout.close();

    cout << "Texto decriptado salvo em decrypted.txt" << endl;
    cout << "Tabela salva em keys.txt" << endl;
    return 0;
}
