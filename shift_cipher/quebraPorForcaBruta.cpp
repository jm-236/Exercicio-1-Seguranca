#include <iostream>
#include <string>
#include <cctype> 
#include <limits> // Para numeric_limits
using namespace std;

const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

int main() {
    int k; // Deslocamento da cifra 
    
    cout << "Ataque por força bruta contra a cifra de deslocamento\n";
    cout << "--------------------\n";
    
    string texto;
    cout << "Digite o texto cifrado: ";
    getline(cin, texto);
    cout << "--------------------\n";

    // Quebra da cifra por força bruta
    cout << "-------------------------------------\n";
    quebrarCifra(texto);

    return 0;
}