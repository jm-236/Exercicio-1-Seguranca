#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cctype>
#include <iomanip>
#include <cmath>

using namespace std;

// Frequências esperadas de letras no português
static vector<pair<char, double>> frequencias_esperadas = {
    {'A', 13.9}, {'E', 12.2}, {'O', 10.8}, {'S', 7.9}, {'R', 6.9},
    {'I', 6.9},  {'N', 5.3},  {'D', 5.4},  {'M', 4.2}, {'T', 4.9},
    {'U', 4.0},  {'C', 4.4},  {'L', 2.8},  {'P', 2.9}, {'V', 1.3},
    {'G', 1.2},  {'H', 0.8},  {'Q', 0.9},  {'B', 1.0}, {'F', 1.0},
    {'Z', 0.4},  {'J', 0.4},  {'X', 0.3},  {'K', 0.1}, {'W', 0.0},
    {'Y', 0.0}
};

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



// Função para aplicar uma chave de cifra de César a um texto
string aplicarCifraCesar(const string& texto, int chave) {
    string resultado;
    for (char c : texto) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            resultado.push_back((c - base + chave) % 26 + base);
        } else {
            resultado.push_back(c);
        }
    }
    return resultado;
}

// Função para calcular pontuação de uma decifragem baseada na proximidade com frequências esperadas
// incluindo análise de dígrafos com matriz completa
double calcularPontuacao(const string& texto) {
    // Contar frequências de monogramas
    vector<int> contagem(26, 0);
    int total = 0;
    
    for (char c : texto) {
        if (isalpha(c)) {
            contagem[toupper(c) - 'A']++;
            total++;
        }
    }
    
    // Calcular pontuação para monogramas
    double pontuacao_mono = 0.0;
    if (total > 0) {
        for (int i = 0; i < 26; i++) {
            double freq_texto = (contagem[i] * 100.0) / total;
            double freq_esperada = 0.0;
            
            // Encontrar a frequência esperada para esta letra
            for (const auto& par : frequencias_esperadas) {
                if (par.first == 'A' + i) {
                    freq_esperada = par.second;
                    break;
                }
            }
            
            double diff = fabs(freq_texto - freq_esperada);
            pontuacao_mono -= diff;
        }
    }
    
    // Contar dígrafos usando a matriz
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
    
    // Calcular pontuação para dígrafos
    double pontuacao_di = 0.0;
    if (total_digrafos > 0) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                if (digrafos_contagem[i][j] > 0) {
                    double freq_texto = (digrafos_contagem[i][j] * 100.0) / total_digrafos;
                    double freq_esperada = frequencias_digrafos_matriz[i][j];
                    
                    // Damos mais peso para dígrafos comuns
                    if (freq_esperada > 1.0) {
                        pontuacao_di += freq_texto * freq_esperada * 2.0;
                    } else if (freq_esperada > 0.5) {
                        pontuacao_di += freq_texto * freq_esperada * 1.5;
                    } else if (freq_esperada > 0.1) {
                        pontuacao_di += freq_texto * freq_esperada;
                    }
                }
            }
        }
    }
    
    // Combinar pontuações (dar mais peso aos dígrafos)
    return pontuacao_mono + (pontuacao_di * 3.0);
}

int main() {
    cout << "Ataque à Cifra de César usando frequência de letras e dígrafos\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Digite o texto cifrado: ";
    string texto_cifrado;
    getline(cin, texto_cifrado);
    cout << "-----------------------------------------------------------\n";
    
    // Calcular frequências no texto cifrado
    vector<pair<char, double>> frequencia_texto(26);
    int total_letras = 0;
    set<char> letras_unicas;
    
    for (int i = 0; i < 26; i++) {
        frequencia_texto[i].first = 'A' + i;
        frequencia_texto[i].second = 0;
    }
    
    for (char c : texto_cifrado) {
        if (isalpha(c)) {
            char letra_upper = toupper(c);
            frequencia_texto[letra_upper - 'A'].second++;
            letras_unicas.insert(letra_upper);
            total_letras++;
        }
    }
    
    int num_letras_distintas = letras_unicas.size();
    cout << "Número de letras distintas no texto: " << num_letras_distintas << endl;
    
    // Normalizar para porcentagens
    for (auto& par : frequencia_texto) {
        if (total_letras > 0) {
            par.second = (par.second * 100.0) / total_letras;
        }
    }
    
    // Ordenar por frequência (maior pro menor)
    sort(frequencia_texto.begin(), frequencia_texto.end(),
         [](const pair<char, double>& a, const pair<char, double>& b) {
             return a.second > b.second;
         });
    
    // Ordenar frequências esperadas (maior pro menor)
    sort(frequencias_esperadas.begin(), frequencias_esperadas.end(),
         [](const pair<char, double>& a, const pair<char, double>& b) {
             return a.second > b.second;
         });
    
    cout << "Letras mais frequentes no texto cifrado:\n";
    for (int i = 0; i < min(5, (int)frequencia_texto.size()); i++) {
        if (frequencia_texto[i].second > 0) {
            cout << frequencia_texto[i].first << ": " << fixed << setprecision(2) 
                 << frequencia_texto[i].second << "%\n";
        }
    }
    cout << "-----------------------------------------------------------\n";
    
    cout << "Letras mais frequentes esperadas no português:\n";
    for (int i = 0; i < min(5, (int)frequencias_esperadas.size()); i++) {
        cout << frequencias_esperadas[i].first << ": " << fixed << setprecision(2) 
             << frequencias_esperadas[i].second << "%\n";
    }
    cout << "-----------------------------------------------------------\n";
    
    // Determinar possíveis chaves baseadas nas frequências
    vector<pair<int, double>> chaves_pontuadas;
    
    // Usar as 5 letras mais frequentes para determinar possíveis chaves
    for (int i = 0; i < min(5, (int)frequencia_texto.size()); i++) {
        if (frequencia_texto[i].second > 0) {
            char letra_texto = frequencia_texto[i].first;
            
            // Comparar com as 5 letras mais frequentes em português
            for (int j = 0; j < min(5, (int)frequencias_esperadas.size()); j++) {
                char letra_esperada = frequencias_esperadas[j].first;
                
                // Calcular a possível chave 
                int chave = (letra_texto - letra_esperada + 26) % 26;
                
                // Testar a decifragem com esta chave
                string texto_decifrado = aplicarCifraCesar(texto_cifrado, (26 - chave) % 26);
                double pontuacao = calcularPontuacao(texto_decifrado);
                
                // Adicionar à lista de chaves pontuadas
                chaves_pontuadas.push_back({chave, pontuacao});
            }
        }
    }
    
    // Ordenar chaves por pontuação (melhor primeiro)
    sort(chaves_pontuadas.begin(), chaves_pontuadas.end(),
         [](const pair<int, double>& a, const pair<int, double>& b) {
             return a.second > b.second;  // Maior pontuação primeiro
         });
    
    // Remover duplicatas mantendo a ordem
    vector<int> chaves_ordenadas;
    set<int> chaves_vistas;
    
    for (const auto& [chave, _] : chaves_pontuadas) {
        if (chaves_vistas.find(chave) == chaves_vistas.end()) {
            chaves_ordenadas.push_back(chave);
            chaves_vistas.insert(chave);
        }
    }
    
    // Sempre limitar para as 5 melhores chaves
    const int max_chaves = 5;
    int num_chaves = min(max_chaves, (int)chaves_ordenadas.size());
    
    cout << "Apresentando as " << num_chaves << " melhores decifragens:\n";
    cout << "-----------------------------------------------------------\n";
    
    // Testar cada chave e mostrar os resultados
    cout << "Textos decifrados com as melhores chaves:\n";
    for (int i = 0; i < num_chaves; i++) {
        int chave = chaves_ordenadas[i];
        string texto_decifrado = aplicarCifraCesar(texto_cifrado, (26 - chave) % 26);
        
        double pontuacao = 0.0;
        for (const auto& [k, p] : chaves_pontuadas) {
            if (k == chave) {
                pontuacao = p;
                break;
            }
        }
        
        cout << "Chave " << setw(2) << chave << " (Pontuação: " << fixed << setprecision(2) 
             << pontuacao << "): " << texto_decifrado << endl;
    }
    cout << "-----------------------------------------------------------\n";
    
    // Sempre destacar a primeira opção como a escolhida
    if (!chaves_ordenadas.empty()) {
        string melhor_decifrado = aplicarCifraCesar(texto_cifrado, (26 - chaves_ordenadas[0]) % 26);
        cout << "A frase decodificada é: \"" << melhor_decifrado << "\"\n";
        cout << "-----------------------------------------------------------\n";
    } else {
        cout << "Não foi possível determinar uma decodificação confiável.\n";
        cout << "-----------------------------------------------------------\n";
    }
    
    return 0;
}