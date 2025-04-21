#include <iostream>
#include <string>
#include <cctype> 
#include <limits> // Para numeric_limits
using namespace std;

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

int main() {
    int k; // Deslocamento da cifra 
    
    cout << "Cifra de Deslocamento - codificação\n";
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