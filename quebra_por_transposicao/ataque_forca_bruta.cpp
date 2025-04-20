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


vector<string> atacarTransposicao(string texto) {
    vector<string> permutacoes;
    vector<string> frases;
    string s = "abcde";
    sort(s.begin(), s.end()); // garante que começamos com a menor permutação

    do {
        permutacoes.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    
    // Exibir todas as permutações
    for (const auto& p : permutacoes) {
        string frase_decifrada = decifrarTransposicao(texto, p);
        frases.push_back(frase_decifrada);
    }

    return frases;
}

int main() {
    
    cout << "Cifra de Transposição - Ataque por força bruta\n";
    cout << "--------------------\n";
        
    string texto;
    cout << "--------------------\n";
    cout << "Digite o texto: ";
    getline(cin, texto);
    cout << "--------------------\n";

    vector<string> frases = atacarTransposicao(texto);
    cout << "Exibindo possíveis textos de origem: " << endl;
    int i = 1;
    for (string frase : frases){
        cout << "Texto n°" << i << ": \"" << frase << "\";"<< endl; 
        i++;
    }

    cout << "--------------------\n";
    return 0;
}