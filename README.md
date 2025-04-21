# Relatório - Exercício 1 - Segurança Computacional

**Aluno:** João Marcelo Costa de Santana

**Matrícula:** 232023790

**Professora:** Lorena Borges

**Disciplina:** Segurança computacional

---

## 1. Contextualização Teórica

### 1.1 Cifra de César (Deslocamento)

- A cifra de César é uma técnica de substituição monoalfabética onde cada letra do texto é deslocada um número fixo de posições no alfabeto.
- Com um deslocamento de 3 posições, 'A' torna-se 'D', 'B' torna-se 'E', e assim por diante.
- É uma das cifras mais antigas e simples, mas também uma das mais vulneráveis a ataques, especialmente de força bruta e análise de frequência.

### 1.2 Cifra por Transposição

- Diferente das cifras de substituição, as cifras por transposição reorganizam a ordem dos caracteres no texto sem alterar os próprios caracteres.
- Um exemplo comum é a transposição de colunas, onde o texto é escrito em linhas sob uma chave e depois lido em uma ordem específica das colunas.
- Embora mais segura que a cifra de César, ainda é suscetível a ataques, especialmente quando combinada com outras técnicas.

---

## 2. Análise dos Códigos Desenvolvidos

- Para não tornar o relatório tão longo, algumas partes dos códigos não foram totalmente exibidas
- Aqui está o [link para o repositório com os códigos completos](https://github.com/jm-236/Exercicio-1-Seguranca)

### 2.1 Cifra de César

### a) Criptografia e Decriptografia

- Os códigos implementam as funções de criptografia e decriptografia utilizando um deslocamento fixo (k).
- Cada caractere do texto é convertido para seu equivalente deslocado no alfabeto.
- **Complexidade de tempo**: Em ambos os códigos, **O(n)**, onde n é o tamanho do texto.

```cpp
// Função para cifrar um caractere usando César com deslocamento k
char cifrarCaractere(char c, int k) {
    if (!isalpha(c)) return c; // Mantém caracteres não alfabéticos
    
    // Converte para maiúsculo para facilitar
    char maiusculo = toupper(c);
    
    // Aplica o deslocamento (A=0, B=1, ..., Z=25)
    int original = maiusculo - 'A';
    int cifrado = (original + k) % 26;
    
    // Converte de volta para o caso original
    return islower(c) ? ('A' + cifrado) + 32 : 'A' + cifrado;
}

// Função para cifrar uma string inteira
string cifrarCesar(const string& texto, int k) {
    string resultado;
    for (char c : texto) {
        resultado += cifrarCaractere(c, k);
    }
    return resultado;
}

char decifrarCaractere(char c, int k) {
    if (!isalpha(c)) return c; // Mantém caracteres não alfabéticos
    
    // Converte para maiúsculo para facilitar
    char maiusculo = toupper(c);
    
    // Aplica o deslocamento (A=0, B=1, ..., Z=25)
    int original = maiusculo - 'A';
    int cifrado = (original - k + 26) % 26; // Adiciona 26 para evitar valores negativos
    
    // Converte de volta para o caso original
    return islower(c) ? ('A' + cifrado) + 32 : 'A' + cifrado;
}

string decifrarCesar(const string& texto, int k) {
    string resultado;
    for  (char c : texto){
        resultado+= decifrarCaractere(c, k);
    }
    return resultado;
}
```

### b) Ataque por Força Bruta

- Este método testa todas as 26 possíveis chaves de deslocamento, decifrando o texto com cada uma e apresentando os resultados.
- É eficaz devido ao pequeno espaço de chaves da cifra de César.
- **Complexidade de tempo**: **O(1)**, pois existem apenas 26 chaves para serem decifradas.

```cpp
// Função para quebrar a cifra por força bruta
void quebrarCifra(const string& texto_cifrado) {
cout << "Tentativas de quebra por força bruta:\n";
cout << "-------------------------------------\n";
for (int k = 1; k <= 25; ++k) {
string tentativa = decifrarCesar(texto_cifrado, k);
cout << "Chave " << k << ": " << tentativa << endl;
}
cout << "-------------------------------------\n";
}
```

### c) Ataque por Análise de Frequência

- Utiliza a distribuição de frequência das letras na língua portuguesa para identificar prováveis chaves.
- Ao comparar a frequência das letras e dígrafos no texto cifrado com a frequência esperada, é possível ranquear as chaves selecionadas e inferir a chave utilizada.
- **Complexidade de tempo**: **O(n)**, onde n é o tamanho do texto.
    - **Pré-processamento do texto**: → **O(n).**
    - **Geração de combinações de chaves baseadas em frequências mais comuns: O(k × n)**, onde **k ≤ 25** → tratável como **O(n)** no total, porque **k é constante**. (5 letras mais frequentes).
    - **Cálculo de pontuação com dígrafos:** Percorre todos os pares consecutivos de letras → **O(n).**

```cpp
// Frequências esperadas de letras no português
static vector<pair<char, double>> frequencias_esperadas = {
    {'A', 13.9}, {'E', 12.2}, {'O', 10.8}, {'S', 7.9}, {'R', 6.9},
    ...
    {'Y', 0.0}
};

// Frequências esperadas de digrafos no português
static double frequencias_digrafos_matriz[26][26] = {
    {5.13, 2.35, 10.05, 14.80, 4.49, 2.27, 2.14, 0.48, 5.11, 0.57, 0.09, 9.03, 8.08, 11.62, 11.84, 5.84, 1.85, 14.89, 16.41, 5.01, 2.26, 3.04, 0.04, 0.15, 0.08, 0.84},
   ...
   {1.20, 0.01, 0.05, 0.15, 0.86, 0.02, 0.00, 0.01, 0.29, 0.01, 0.00, 0.01, 0.08, 0.05, 0.33, 0.07, 0.08, 0.02, 0.05, 0.02, 0.06, 0.01, 0.00, 0.00, 0.00, 0.02}
};

// Função para calcular pontuação de uma decifragem baseada na proximidade com frequências esperadas
// incluindo análise de dígrafos com matriz completa
double calcularPontuacao(const string& texto) {
    // Contar frequências de monogramas
    }
    
    // Calcular pontuação para monogramas
    double pontuacao_mono = 0.0;
    if (total > 0) {
        for (int i = 0; i < 26; i++) {
            double freq_texto = (contagem[i] * 100.0) / total;
            double freq_esperada = 0.0;
            
            // Encontrar a frequência esperada para esta letra
        }
    }
    
    // Contar dígrafos usando a matriz
    vector<vector<int>> digrafos_contagem(26, vector<int>(26, 0));
    int total_digrafos = 0;
    
    for (size_t i = 0; i < texto.size() - 1; i++) {
        if (isalpha(texto[i]) && isalpha(texto[i+1])) {
            ...
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
    ...
    int num_letras_distintas = letras_unicas.size();
    cout << "Número de letras distintas no texto: " << num_letras_distintas << endl;
    
    // Normalizar para porcentagens
    }
    
    // Ordenar por frequência no texto (maior pro menor)
    
    // Ordenar frequências esperadas (maior pro menor)
    
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
                
                // Calcular a possível chave 
                
                // Testar a decifragem com esta chave
                
                // Adicionar à lista de chaves pontuadas
            }
        }
    }
    
    // Ordenar chaves por pontuação (melhor primeiro)
    
    // Remover duplicatas mantendo a ordem
    }
    
    // Sempre limitar para as 5 melhores chaves
    const int max_chaves = 5;
    int num_chaves = min(max_chaves, (int)chaves_ordenadas.size());
    
    cout << "Apresentando as " << num_chaves << " melhores decifragens:\n";
    cout << "-----------------------------------------------------------\n";
    
    // Testar cada chave e mostrar os resultados
    cout << "Textos decifrados com as melhores chaves:\n";
    ...
    cout << "-----------------------------------------------------------\n";
    
    // Sempre destaca a primeira opção como a escolhida
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
```

### 2.2 Cifra por Transposição

### a) Criptografia e Decriptografia

- A implementação utiliza uma chave para determinar a ordem das colunas na transposição.
- A chave tem **tamanho fixo de 5 caracteres**, onde **cada caractere é único**.
- O texto é escrito em linhas sob a chave e depois lido em uma ordem específica das colunas para formar o texto cifrado.

```cpp
// Função para cifrar uma string inteira por transposição
string cifrarTransposicao(const string& texto, string k) {
    string resultado;
    vector<pair<char, string>> colunas;

    // Inicializa as colunas

    // Distribui os caracteres do texto nas colunas
    for (size_t i = 0; i < texto.length(); i++) {
        char c = texto[i];
        // Usar o índice do caractere na chave para determinar a coluna
    }

    // ordena as colunas em ordem alfabetica

    // Concatena as colunas para formar o texto cifrado

    return resultado;
}

string decifrarTransposicao(const string& texto, const string& k) {
    int n_colunas = k.size();
    const int tamanho = texto.size();
    int base = tamanho / n_colunas;
    int extra = tamanho % n_colunas;        // colunas que terão uma letra a mais

    // inicia o vetor de colunas

    // ordenando o vetor em ordem alfabetica

    // adiciona as letras ao vetor
    
    // ordena o vetor na ordem da chave

    // Reconstruir o texto original lendo linha por linha

    return resultado;
}

// Função para obter a chave k
string obter_k(){
    string k;
    
    while (true){
        cout << "Digite a chave k utilizada na cifra(5 caracteres): ";
        getline(cin, k);

        // verificacao do tamanho
        // verificacao se contem somente letras
        // letras unicas

    return k;
}
```

### b) Ataque por Força Bruta

- Este método tenta todas as possíveis permutações das colunas para decifrar o texto.
- Devido ao crescimento fatorial do número de permutações com o tamanho da chave, este método torna-se rapidamente inviável para chaves maiores.
- A complexidade desse ataque numa cifra de transposição pode mudar de acordo com o contexto:
    - Quando a chave **não é conhecida**, a complexidade depende da quantidade de permutações possíveis para a ordem das colunas.
        - Com **chave de tamanho `k`**, existem `k!` (fatorial de k) permutações possíveis.
        - Complexidade: **O(k! × n)**, onde n é o tamanho do texto.
    - Mas **se a chave está fixa e conhecida (ex: 5):**
        - Em vez de testar todas as possíveis permutações, só **aplica-se diretamente** uma lista de candidatas.(no caso onde o tamanho é igual a 5, aplica-se **5! = 120 chaves**).
        - Complexidade: **O(n).**

```cpp
vector<string> atacarTransposicao(string texto) {
    vector<string> permutacoes;
    vector<string> frases;
    string s = "abcde";
    sort(s.begin(), s.end()); // garante que começamos com a menor permutação

		// criando as todas as chaves de tamanho = 5
    do {
        permutacoes.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    
    // Exibir todas as permutações
    for (const auto& p : permutacoes) {
        // exibe as permutações e adiciona no array
    }

    return frases; // retorna todas as possiveis decodificações do texto
}
```

### c) Ataque por Análise de Frequência

- Semelhante ao ataque na cifra de César, este método analisa a frequência dos dígrafos e de palavras comuns da língua portuguesa no texto cifrado e tenta identificar padrões que correspondam à língua portuguesa, auxiliando na identificação da chave correta ou de possíveis chaves corretas.
- Nesse código, somente a análise de frequência de dígrafos foi insuficiente para ranquear possíveis chaves, por isso, foi utilizada uma lista com palavras comuns na língua portuguesa para auxiliar na identificação da frase correta.
- A análise de monogramas não foi feita pois **as letras não são substituídas, apenas rearranjadas.**
- Também há penalidade caso o texto possua muitos **dígrafos incomuns**.
- Ao analisar as possíveis frases e ranqueá-las, **o código exibe as 5 mais bem ranqueadas**, pois algumas delas provavelmente **será a frase original.**
- Complexidade:
    - Assim como no ataque por força bruta, a complexidade desse código varia de acordo com o tamanho da **chave k.**
    - Com **chave de tamanho `k`**, existem `k!` (fatorial de k) permutações possíveis.
    - Mas se a chave for de tamanho fixo, pode cair para **O(n)** ou **O(m × n)**, onde m ≪ k!

```cpp
double calcularPontuacao(const string& texto) {
    // 1. Calcular pontuação para dígrafos
    vector<vector<int>> digrafos_contagem(26, vector<int>(26, 0));
    int total_digrafos = 0;
    // contagem da frequencia de digrafos
    
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
    vector<string> palavras_comuns = {"de", "do", ... "tchau"};
    
    string texto_lower = texto;
    transform(texto_lower.begin(), texto_lower.end(), texto_lower.begin(), ::tolower);
    
    for (const auto& palavra : palavras_comuns) {
        // verifica se a palavra está no texto
            
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

vector<pair<string, double>> atacarTransposicao(string texto) {
    vector<string> permutacoes;
    vector<pair<string, double>> top_5;
    vector<pair<string, double>> frases;
    string s = "abcde";
    sort(s.begin(), s.end()); // garante que começamos com a menor permutação

		// criando as permutacoes possiveis das colunas
    do {
        permutacoes.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    
    // Exibir todas as permutações e salva as frases num array
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
		// retorna somente as 5 melhores frases para exibi-las
    return top_5;
}
```

---

## 3. Saídas dos códigos

### 3.1 Cifra de César

![Saída do código de criptografia da cifra de deslocamento](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image.png)

Saída do código de criptografia da cifra de deslocamento

![Saída do código de descriptografia da cifra de deslocamento](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image%201.png)

Saída do código de descriptografia da cifra de deslocamento

![Saída do código de quebra por força bruta da cifra por deslocamento](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image%202.png)

Saída do código de quebra por força bruta da cifra por deslocamento

![Saída do código de quebra por análise de frequências contra a cifra de deslocamento](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image%203.png)

Saída do código de quebra por análise de frequências contra a cifra de deslocamento

### 3.2 Cifra de transposição

![Saída do código de criptografia da cifra de transposição](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image%204.png)

Saída do código de criptografia da cifra de transposição

![Saída do código de decriptografia da cifra de transposição](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image%205.png)

Saída do código de decriptografia da cifra de transposição

![Saída do código de ataque por força bruta contra a cifra por transposição](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image%206.png)

Saída do código de ataque por força bruta contra a cifra por transposição

![Saída do código de ataque por força bruta contra a cifra por transposição](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image%207.png)

Saída do código de ataque por força bruta contra a cifra por transposição

![Saída do código de ataque por frequências contra a cifra por transposição](Relato%CC%81rio%20-%20Exerci%CC%81cio%201%20-%20Seguranc%CC%A7a%20Computacion%201dc4f9ea465280a7bbfcdefcde4213c9/image%208.png)

Saída do código de ataque por frequências contra a cifra por transposição

---

## 4. Comparativo de Estratégias e Complexidade

| Técnica | Complexidade | Tempo de Execução | Aplicabilidade |
| --- | --- | --- | --- |
| Força Bruta (César) | O(1) | Rápido | Pequeno espaço de chaves |
| Análise de Frequência (César) | O(n) | Rápido | Textos mais longos |
| Força Bruta (Transposição) | O(n), mas poderia ser O(n!) | Rápido com chave fixa, lento com chave de tamanho variável | Apenas para chaves pequenas |
| Análise de Frequência (Transp.) | O(n) | Moderado | Requer conhecimento da língua original |

---

## 5. Considerações Finais

- Os códigos desenvolvidos demonstram uma compreensão sólida das técnicas clássicas de criptografia e dos métodos básicos de criptoanálise.
- A cifra de César, embora simples, serve como uma introdução eficaz aos conceitos de criptografia e análise de segurança.
- A cifra por transposição adiciona uma camada de complexidade, destacando a importância de considerar a estrutura do texto ao desenvolver ou quebrar cifras.
- Para aprimorar a segurança, é recomendável combinar múltiplas técnicas de criptografia e considerar métodos modernos que oferecem maior resistência a ataques e elevam a complexidade dos códigos de ataque.
