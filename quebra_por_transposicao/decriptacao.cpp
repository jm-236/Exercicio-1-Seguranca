#include <bits/stdc++.h>
using namespace std;

// Função para decifrar uma string inteira
string decifrarTransposicao(const string& texto, const string& k) {
    int n_colunas = k.size();
    const int tamanho = texto.size();
    int base = tamanho / n_colunas;
    int extra = tamanho % n_colunas;        // colunas que terão uma letra a mais

    // inicializando o vetor de colunas
    vector<pair<char, pair<int, string>>> colunas;
    int i = 0;
    for (char c : k){
        colunas.push_back(make_pair(c, make_pair(i, "")));
        i++;
    }

    // ordenando o vetor em ordem alfabetica
    sort(colunas.begin(), colunas.end());

    // adicionando as letras ao vetor
    int inicio = 0;
    for(auto& p : colunas){

        int tamanho_coluna = base + (p.second.first < extra ? 1 : 0); // Colunas extras recebem +1 caractere
        p.second.second = texto.substr(inicio, tamanho_coluna);
        inicio += tamanho_coluna;
        
    }

    // debug
    for (pair<char, pair<int, string>> coluna : colunas) {
        cout << "Coluna " << coluna.first << ": " << coluna.second.second << endl;
    }
    
    // ordenando o vetor na ordem da chave
    sort(colunas.begin(), colunas.end(), [](const auto& a, const auto& b) {
        return a.second.first < b.second.first;
    });

    // Reconstruir o texto original lendo linha por linha
    string resultado;
    for (int i = 0; i < base + (extra > 0); i++) {
        for (int j = 0; j < n_colunas; j++) {
            if (i < colunas[j].second.second.size()) {
                resultado += colunas[j].second.second[i];
            }
        }
    }

    return resultado;
}

// Função para obter a chave k
string obter_k(){
    string k;
    
    while (true){
        cout << "Digite a chave k utilizada na cifra(5 caracteres): ";
        getline(cin, k);

        // verificacao do tamanho
        if (k.length() != 5) {
            cout << "K inválido! Digite uma chave de tamanho 5" << endl;
        } else {
            bool alfa = true;
            bool unicas = true;
            string repetidos = "";
            for (char c : k){
                // verificando se contem letras
                if (!isalpha(c)){
                    cout << "A chave deve conter somente letras!" << endl;
                    alfa = false;
                    break;
                }

                // letras unicas
                if (repetidos.find(c) != -1) {
                    cout << "A chave deve conter letras únicas!" << endl;
                    unicas = false;
                    break;
                } else {
                    repetidos += c;
                }
            }
            if (alfa && unicas) { break; };
        }
    }

    return k;
}

int main() {
    string k; 
    
    cout << "Cifra de Transposição - Decriptação\n";
    cout << "--------------------\n";
    k = obter_k();
    
    string texto;
    cout << "--------------------\n";
    cout << "Digite o texto: ";
    getline(cin, texto);
    cout << "--------------------\n";

    string texto_original = decifrarTransposicao(texto, k);
    cout << "Texto original: \"" << texto_original << "\""<< endl; 
    cout << "--------------------\n";
    
    return 0;
}