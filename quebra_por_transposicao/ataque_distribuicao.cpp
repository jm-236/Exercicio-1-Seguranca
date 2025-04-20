#include <bits/stdc++.h>
using namespace std;

// Frequências esperadas de digrafos no português
static double frequencias_digrafos_matriz[26][26] = {
    {5.13, 2.35, 10.05, 14.80, 4.49, 2.27, 2.14, 0.48, 5.11, 0.57, 0.09, 9.03, 8.08, 11.62, 11.84, 5.84, 1.85, 14.89, 16.41, 5.01, 2.26, 3.04, 0.04, 0.15, 0.08, 0.84},
    {1.90, 0.02, 0.03, 0.02, 1.90, 0.00, 0.00, 0.00, 1.02, 0.10, 0.00, 0.83, 0.03, 0.00, 1.26, 0.02, 0.00, 1.83, 0.22, 0.07, 0.46, 0.02, 0.00, 0.00, 0.01, 0.00},
    {12.57, 0.01, 0.45, 0.07, 3.78, 0.01, 0.01, 1.12, 6.09, 0.00, 0.09, 0.80, 0.02, 0.15, 14.00, 0.10, 0.02, 1.38, 0.03, 1.62, 1.88, 0.00, 0.00, 0.00, 0.00, 0.00},
    {11.92, 0.02, 0.03, 0.05, 20.33, 0.01, 0.02, 0.02, 4.96, 0.04, 0.00, 0.02, 0.20, 0.03, 14.45, 0.05, 0.03, 0.50, 0.07, 0.02, 1.13, 0.07, 0.01, 0.00, 0.02, 0.00},
    {6.34, 0.95, 7.25, 5.77, 3.34, 2.17, 2.81, 0.44, 5.31, 0.89, 0.07, 5.97, 10.92, 14.94, 3.24, 3.99, 1.66, 13.33, 20.71, 3.53, 3.28, 2.35, 0.08, 1.52, 0.06, 0.73},
    {1.56, 0.00, 0.04, 0.01, 2.03, 0.04, 0.00, 0.00, 2.64, 0.00, 0.00, 0.21, 0.01, 0.01, 2.21, 0.02, 0.00, 0.81, 0.01, 0.03, 0.64, 0.00, 0.00, 0.00, 0.00, 0.00},
    {2.60, 0.01, 0.02, 0.03, 1.74, 0.01, 0.01, 0.04, 1.22, 0.00, 0.01, 0.13, 0.03, 0.21, 2.05, 0.02, 0.00, 1.56, 0.03, 0.05, 2.52, 0.00, 0.00, 0.00, 0.00, 0.00},
    {2.70, 0.00, 0.02, 0.02, 1.44, 0.01, 0.00, 0.02, 0.53, 0.00, 0.00, 0.02, 0.03, 0.06, 2.26, 0.01, 0.00, 0.03, 0.01, 0.04, 0.24, 0.00, 0.00, 0.00, 0.00, 0.00},
    {8.15, 0.67, 6.83, 5.54, 1.16, 0.85, 1.50, 0.02, 0.11, 0.05, 0.05, 2.52, 3.70, 8.22, 4.84, 1.07, 0.18, 4.50, 8.79, 4.90, 0.56, 2.50, 0.00, 0.45, 0.00, 1.31},
    {1.14, 0.00, 0.00, 0.00, 0.56, 0.00, 0.00, 0.00, 0.03, 0.00, 0.00, 0.00, 0.00, 0.00, 1.04, 0.00, 0.00, 0.00, 0.00, 0.00, 0.75, 0.00, 0.00, 0.00, 0.00, 0.00},
    {0.10, 0.00, 0.01, 0.01, 0.11, 0.01, 0.00, 0.02, 0.10, 0.00, 0.01, 0.02, 0.02, 0.01, 0.09, 0.01, 0.00, 0.02, 0.03, 0.01, 0.02, 0.00, 0.00, 0.00, 0.01, 0.00},
    {4.93, 0.15, 0.52, 1.32, 3.96, 0.18, 0.59, 1.92, 5.22, 0.06, 0.02, 0.31, 0.78, 0.24, 3.43, 0.45, 0.31, 0.10, 0.35, 1.39, 1.16, 0.56, 0.00, 0.00, 0.04, 0.00},
    {11.35, 1.48, 1.08, 1.29, 8.13, 0.37, 0.20, 0.12, 3.37, 0.16, 0.01, 0.30, 0.66, 0.54, 5.21, 3.49, 0.58, 0.38, 0.86, 0.54, 1.88, 0.27, 0.01, 0.00, 0.01, 0.00},
    {8.65, 0.04, 4.47, 5.27, 2.24, 0.72, 1.05, 1.91, 3.43, 0.14, 0.07, 0.04, 0.05, 0.13, 6.13, 0.06, 0.25, 0.10, 3.05, 13.27, 1.30, 0.64, 0.01, 0.00, 0.03, 0.06},
    {5.41, 2.08, 5.37, 9.58, 6.29, 1.89, 1.73, 0.47, 2.79, 0.83, 0.06, 3.66, 7.79, 10.14, 2.04, 6.30, 1.84, 11.85, 18.26, 2.55, 4.06, 2.24, 0.08, 0.25, 0.03, 0.16},
    {6.74, 0.00, 0.17, 0.05, 5.23, 0.02, 0.01, 0.04, 0.93, 0.01, 0.00, 0.86, 0.02, 0.03, 7.46, 0.10, 0.02, 6.02, 0.26, 0.21, 0.93, 0.01, 0.00, 0.00, 0.00, 0.00},
    {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
    {17.43, 0.28, 2.34, 2.41, 14.16, 0.31, 0.92, 0.07, 8.06, 0.10, 0.05, 0.41, 1.88, 1.61, 8.11, 0.85, 0.81, 1.84, 1.31, 3.73, 1.53, 0.66, 0.01, 0.00, 0.05, 0.02},
    {9.19, 0.66, 4.18, 6.33, 13.47, 1.19, 0.39, 0.57, 4.72, 0.38, 0.06, 0.65, 2.37, 1.82, 5.91, 5.20, 1.47, 1.05, 6.33, 9.80, 2.58, 0.63, 0.02, 0.00, 0.01, 0.03},
    {11.46, 0.01, 0.09, 0.03, 12.72, 0.01, 0.01, 0.15, 6.17, 0.01, 0.00, 0.07, 0.06, 0.04, 9.33, 0.07, 0.01, 5.83, 0.11, 0.12, 2.94, 0.03, 0.01, 0.00, 0.02, 0.02},
    {3.98, 1.01, 1.05, 1.22, 8.55, 0.14, 0.87, 0.03, 2.55, 0.15, 0.02, 2.15, 5.54, 3.20, 0.51, 0.96, 0.18, 2.72, 2.07, 2.17, 0.15, 0.26, 0.00, 0.07, 0.00, 0.24},
    {3.36, 0.00, 0.01, 0.01, 4.75, 0.00, 0.00, 0.00, 3.19, 0.00, 0.00, 0.01, 0.01, 0.00, 1.75, 0.01, 0.00, 0.17, 0.01, 0.00, 0.07, 0.00, 0.00, 0.00, 0.00, 0.00},
    {0.11, 0.00, 0.00, 0.00, 0.05, 0.00, 0.00, 0.01, 0.06, 0.00, 0.00, 0.00, 0.00, 0.01, 0.04, 0.00, 0.00, 0.00, 0.01, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
    {0.45, 0.00, 0.13, 0.01, 0.32, 0.00, 0.00, 0.00, 0.58, 0.00, 0.00, 0.00, 0.01, 0.00, 0.20, 0.42, 0.00, 0.00, 0.01, 0.24, 0.03, 0.01, 0.00, 0.01, 0.00, 0.00},
    {0.06, 0.01, 0.02, 0.02, 0.05, 0.01, 0.00, 0.00, 0.01, 0.00, 0.00, 0.02, 0.02, 0.02, 0.05, 0.01, 0.00, 0.01, 0.03, 0.01, 0.01, 0.00, 0.01, 0.00, 0.00, 0.00},
    {1.20, 0.01, 0.05, 0.15, 0.86, 0.02, 0.00, 0.01, 0.29, 0.01, 0.00, 0.01, 0.08, 0.05, 0.33, 0.07, 0.08, 0.02, 0.05, 0.02, 0.06, 0.01, 0.00, 0.00, 0.00, 0.02}
};

double calcularPontuacao(const string& texto) {
    // 1. Calcular pontuação para dígrafos
    vector<vector<int>> digrafos_contagem(26, vector<int>(26, 0));
    int total_digrafos = 0;
    
    for (size_t i = 0; i < texto.size() - 1; i++) {
        if (isalpha(texto[i]) && isalpha(texto[i+1])) {
            char c1 = toupper(texto[i]);
            char c2 = toupper(texto[i+1]);
            digrafos_contagem[c1 - 'A'][c2 - 'A']++;
            total_digrafos++;
        }
    }
    
    double pontuacao_di = 0.0;
    double pontuacao_penalidade = 0.0;
    
    if (total_digrafos > 0) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                if (digrafos_contagem[i][j] > 0) {
                    double freq_texto = (double)digrafos_contagem[i][j] / total_digrafos;
                    double freq_esperada = frequencias_digrafos_matriz[i][j] / 100.0;
                    
                    // Damos mais peso para dígrafos comuns
                    if (freq_esperada > 5.0) {
                        pontuacao_di += freq_texto * freq_esperada * 4.0; 
                    } else if (freq_esperada > 1.0) {
                        pontuacao_di += freq_texto * freq_esperada * 2.0;
                    } else if (freq_esperada > 0.5) {
                        pontuacao_di += freq_texto * freq_esperada * 1.5;
                    } else if (freq_esperada > 0.1) {
                        pontuacao_di += freq_texto * freq_esperada;
                    } else {
                        pontuacao_penalidade++;
                    }
                }
            }
        }
    }
    
    // 2. Adicionar verificação de palavras comuns em português
    double bonus_palavras = 0.0;
    vector<string> palavras_comuns = {"de", "do", "da", "em", "para", "com", "que", "os", "as", "por", 
                                     "uma", "ser", "tem", "estou", "como", "foi", "mas", "ou", "seu", "um",
                                    "meu", "minha", "nossa", "ele", "ela", "eles", "elas", "nao", "sim", "oi",
                                "ola", "adeus", "tchau"};
    
    string texto_lower = texto;
    transform(texto_lower.begin(), texto_lower.end(), texto_lower.begin(), ::tolower);
    
    for (const auto& palavra : palavras_comuns) {
        size_t pos = 0;
        while ((pos = texto_lower.find(palavra, pos)) != string::npos) {
            // Verificar se é uma palavra completa
            bool inicio_ok = (pos == 0 || !isalpha(texto_lower[pos-1]));
            bool fim_ok = (pos + palavra.length() == texto_lower.length() || 
                           !isalpha(texto_lower[pos + palavra.length()]));
            
            if (inicio_ok && fim_ok) {
                bonus_palavras += 50.0;
            }
            pos += palavra.length();
        }
    }
    
    // 3. Calcular pontuação final
    double pontuacao_final = pontuacao_di - pontuacao_penalidade + bonus_palavras;
    
    return pontuacao_final;
}

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


vector<pair<string, double>> atacarTransposicao(string texto) {
    vector<string> permutacoes;
    vector<pair<string, double>> top_5;
    vector<pair<string, double>> frases;
    string s = "abcde";
    sort(s.begin(), s.end()); // garante que começamos com a menor permutação

    do {
        permutacoes.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    
    // Exibir todas as permutações
    for (const auto& p : permutacoes) {
        string frase_decifrada = decifrarTransposicao(texto, p);
        frases.push_back(make_pair(frase_decifrada, calcularPontuacao(frase_decifrada)));
    }

    // ordenando as frases
    sort(frases.begin(), frases.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    for (int i = 0; i < 5; i++){
        top_5.push_back(frases[i]);
    }

    return top_5;
}

int main() {
    
    cout << "Cifra de Transposição - Ataque por distribuição de frequẽncias\n";
    cout << "--------------------\n";
    
    string texto;
    cout << "--------------------\n";
    cout << "Digite o texto: ";
    getline(cin, texto);
    cout << "--------------------\n";

    vector<pair<string, double>> frases = atacarTransposicao(texto);
    cout << "Exibindo possíveis textos de origem: " << endl;
    for (int i = 0; i < 5; i++){
        cout << "Frase n° " << i+1 << ": \"" << frases[i].first << "\"" << endl;
        cout << "pontuação: " << frases[i].second << "\n\n";
    }
   

    cout << "--------------------\n";
    return 0;
}