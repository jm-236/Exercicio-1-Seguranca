# Exercicio 1 - Seguranca Computacional

## Introdução
Neste exercício, foram desenvolvidos os seguintes códigos:
* **Cifra por deslocamento**
  1. **Criptação**: código que recebe um texto e uma chave e retorna o texto codificado na chave k fornecida por meio da operação de deslocamento
  2. **Decriptação**: código que recebe um texto codificado e uma chave e retorna o texto decodificado na chave k fornecida por meio da operação de deslocamento
  3. **Ataque por força bruta**: código que recebe um texto codificado e testa todas as 26 possibilidades de decodificação dele pela operação de deslocamento
  4. **Ataque por distribuição de frequências**: código que recebe um texto codificado e, pela análise da distribuição de frequências dos caracteres e dígrafos na frase, infere qual a chave e qual a mensagem original

* **Cifra por transposição**   
  1. **Criptação**: código que recebe um texto e uma chave e retorna o texto codificado na chave k fornecida por meio da operação de transposição
  2. **Decriptação**: código que recebe um texto codificado e uma chave e retorna o texto decodificado na chave k fornecida por meio da operação de transposição
  3. **Ataque por força bruta**: código que recebe um texto codificado e testa todas as possibilidades de decodificação dele pela operação de transposição
  4. **Ataque por distribuição de frequências**: código que recebe um texto codificado e, pela análise da distribuição de frequências dos caracteres e dígrafos na frase, infere quais são as possíveis chaves e textos originais
  * **OBS**: para fins de desempenho, esses códigos foram feitos considerando um tamanho de chave fixo de 5 caracteres

## Cifra por deslocamento

### Criptação
* **main**: Código principal do programa
  ```c++  
    int main() {
    
        int k; // Deslocamento da cifra 
        
        cout << "Cifra de Deslocamento\n";
        cout << "--------------------\n";
        
        while (true){
            cout << "Digite a chave k utilizada na cifra(1 a 25): ";
            cin >> k;
            if (k < 1 || k > 25) {
                cout << "K inválido!" << endl;
            } else {
                break;
            }
        }
    
        // Limpa o buffer do cin antes de usar getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        string texto;
        cout << "--------------------\n";
        cout << "Digite o texto: ";
        getline(cin, texto);
        cout << "--------------------\n";
    
    
        string texto_cifrado = cifrarCesar(texto, k);
        cout << "Texto cifrado: " << texto_cifrado << endl; 
        cout << "--------------------\n";
        
        return 0;
    }
  ```
