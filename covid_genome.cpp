// Trabalho de Computação Molecular - SI
// Nome: Caio Lima
// Prof. Rodrigo Nonamor - UFRPE
// Abril de 2025

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Estrutura para armazenar cada bloco e sua contagem
struct Bloco {
    string seq;
    int cont;
    Bloco* prox;

    Bloco(const string& s) : seq(s), cont(1), prox(nullptr) {}
};

// Implementação da tabela de espalhamento com encadeamento externo
class TabelaHash {
private:
    vector<Bloco*> tabela;
    size_t tam;

    // Função de hash baseada em base 4 (A, C, G, T → 0, 1, 2, 3)
    size_t funcaoHash(const string& chave) const {
        size_t valor = 0;
        for (char c : chave) {
            int base;
            switch (c) {
                case 'A': base = 0; break;
                case 'C': base = 1; break;
                case 'G': base = 2; break;
                case 'T': base = 3; break;
                default:  base = 0; // Se encontrar caractere inesperado, trata como A
            }
            valor = valor * 4 + base;
        }
        return valor % tam;
    }

public:
    TabelaHash(size_t tamanho) : tabela(tamanho, nullptr), tam(tamanho) {}

    ~TabelaHash() {
        // Libera a memória alocada nos nós
        for (auto head : tabela) {
            while (head) {
                Bloco* apagar = head;
                head = head->prox;
                delete apagar;
            }
        }
    }

    // Insere um novo bloco ou incrementa a contagem se já existir
    void inserir(const string& bloco) {
        size_t i = funcaoHash(bloco);
        Bloco* atual = tabela[i];

        while (atual) {
            if (atual->seq == bloco) {
                atual->cont++;
                return;
            }
            atual = atual->prox;
        }

        // Bloco novo: adiciona no início da lista
        Bloco* novo = new Bloco(bloco);
        novo->prox = tabela[i];
        tabela[i] = novo;
    }

    // Escreve todos os blocos e contagens no arquivo de saída
    void salvarResultado(ofstream& out) {
        for (auto head : tabela) {
            while (head) {
                out << head->seq << " " << head->cont << "\n";
                head = head->prox;
            }
        }
    }
};

int main() {
    ifstream entrada("genome.txt");
    ofstream saida("result.txt");

    if (!entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo genome.txt\n";
        return 1;
    }

    if (!saida.is_open()) {
        cerr << "Erro ao criar result.txt\n";
        return 1;
    }

    TabelaHash tabela(4096); // 4^6 = 4096, ideal para blocos de 6 letras ACGT
    string linha;
    int linhasProcessadas = 0;

    cout << "Lendo genoma e processando blocos de 6 bases...\n";

    while (getline(entrada, linha)) {
        if (linha.length() < 60) break; // Ignora a última linha se for incompleta

        // Pega os blocos nas posições 0, 6, 12, ..., 54
        for (size_t i = 0; i + 6 <= linha.length(); i += 6) {
            string bloco = linha.substr(i, 6);
            tabela.inserir(bloco);
        }

        linhasProcessadas++;
    }

    cout << "Linhas processadas: " << linhasProcessadas << endl;
    cout << "Gravando resultados em result.txt...\n";

    tabela.salvarResultado(saida);

    entrada.close();
    saida.close();

    cout << "Finalizado.\n";
    return 0;
}
