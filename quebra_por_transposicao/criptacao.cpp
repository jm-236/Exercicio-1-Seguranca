#include <bits/stdc++.h>
using namespace std;

// Função para cifrar uma string inteira por transposição
string cifrarTransposicao(const string& texto, string k) {
    string resultado;
    vector<pair<char, string>> colunas;

    // Inicializa as colunas
    for (char c : k) {
        colunas.push_back(make_pair(c, ""));
    }

    // Distribui os caracteres do texto nas colunas
    for (size_t i = 0; i < texto.length(); i++) {
        char c = texto[i];
        // Usar o índice do caractere na chave para determinar a coluna
        size_t coluna_idx = i % k.length();
        colunas[coluna_idx].second += c;
    }

    // Debug para mostrar o conteúdo das colunas
    for (const auto& coluna : colunas) {
        cout << "Coluna " << coluna.first << ": \"" << coluna.second << "\"" << endl;
    }

    sort(colunas.begin(), colunas.end());

    // Concatena as colunas para formar o texto cifrado
    for (const auto& coluna : colunas) {
        resultado += coluna.second;
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
    string k; // Deslocamento da cifra 
    
    cout << "Cifra de Transposição - criptação\n";
    cout << "--------------------\n";
    
    k = obter_k();
    string texto;
    cout << "--------------------\n";
    cout << "Digite o texto: ";
    getline(cin, texto);
    cout << "--------------------\n";

    string texto_cifrado = cifrarTransposicao(texto, k);
    cout << "Chave utilizada: \"" << k << "\"" << endl; 
    cout << "Texto cifrado: \"" << texto_cifrado << "\""<< endl; 
    cout << "--------------------\n";
    
    return 0;
}