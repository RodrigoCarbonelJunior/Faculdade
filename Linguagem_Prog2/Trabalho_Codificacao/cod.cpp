#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

vector<pair<char,int>> CountFrequency(const string &text) {
    map<char,int> freq;
    for (char c : text) {
        freq[c]++;
    }
    
    vector<pair<char,int>> freqVec(freq.begin(), freq.end());
    vector<char> alpha;
    for(int c = 0; c <= 255; ++c){
        if(c == '[' || c == ']') continue;
        alpha.push_back((unsigned char)c);
    }
    return freqVec;
}
vector<pair<char,char>> CreateTable(const string &text) {
    vector<pair<char,int>> freqVec = CountFrequency(text);
    vector<pair<char,char>> table;

    char code = 'a';
    for (int i = 0; i < freqVec.size(); i++) {
        table.push_back({(unsigned char)freqVec.at(i).first, code});
        code++;
        if (code > 'z' && code < 'A') code = 'A'; 
    }
    return table;
}

string Encrypt(const vector<pair<char,char>> &table, const string &inputText) {
    string encrypted;
    for (char c : inputText) {
        auto it = find_if(table.begin(), table.end(), [&](auto &p) {
            return p.first == c;
        });
        if (it != table.end()) {
            encrypted += it->second;
        } else {
            encrypted += c;
        }
    }


    string hidden = encrypted;
    int step = 17; // passo inicial
    int pos = 0;
    for (auto &p : table) {
        pos = (pos + step) % (hidden.size() + 1);
        hidden.insert(pos, string("[") + p.first + p.second + "]");
        step = (step * 2 + 5) % 53 + 7;
    }
    return hidden;
}

int main() {
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Erro ao abrir input.txt" << endl;
        return 1;
    }

    string inputText((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();

    vector<pair<char,char>> table = CreateTable(inputText);
    string encryptedText = Encrypt(table, inputText);

    ofstream fout("encrypted.txt");
    fout << encryptedText;
    fout.close();

    cout << "Texto encriptado salvo em encrypted.txt" << endl;
    return 0;
}
