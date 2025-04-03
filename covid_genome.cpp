#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Estrutura para armazenar cada bloco e sua contagem
// A estrutura armazena o bloco de 6 caracteres e sua respectiva contagem
struct Bloco {
    string seq;  // A sequência do bloco
    int cont;    // A quantidade de vezes que esse bloco apareceu
    Bloco* prox; // Ponteiro para o próximo bloco (encadeamento externo)

    // Construtor para inicializar a sequência e a contagem
    Bloco(const string& s) : seq(s), cont(1), prox(nullptr) {}
};

// Implementação da tabela de espalhamento com encadeamento externo
class TabelaHash {
private:
    vector<Bloco*> tabela;  // A tabela onde armazenam-se os blocos
    size_t tam;  // Tamanho da tabela, idealmente 4^6 para blocos de 6 caracteres (4096 posições)

    // Função de hash que transforma a sequência de 6 caracteres em um índice
    // Baseada em ACGT -> 0, 1, 2, 3
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
        // Usa o módulo para garantir que o valor final esteja dentro do limite da tabela
        return valor % tam;
    }

public:
    // Construtor que inicializa a tabela com o tamanho desejado
    TabelaHash(size_t tamanho) : tabela(tamanho, nullptr), tam(tamanho) {}

    // Destruidor que limpa a memória alocada para os nós da tabela
    ~TabelaHash() {
        for (auto head : tabela) {
            while (head) {
                Bloco* apagar = head;
                head = head->prox;
                delete apagar;
            }
        }
    }

    // Função para inserir um bloco na tabela de hash
    // Caso o bloco já exista, incrementa a contagem, caso contrário, insere um novo bloco
    void inserir(const string& bloco) {
        size_t i = funcaoHash(bloco);  // Calcula o índice para o bloco
        Bloco* atual = tabela[i];

        // Percorre a lista de blocos para encontrar se já existe um bloco igual
        while (atual) {
            if (atual->seq == bloco) {
                atual->cont++;  // Se o bloco já existe, apenas incrementa a contagem
                return;
            }
            atual = atual->prox;  // Se não encontrou, vai para o próximo
        }

        // Bloco novo: cria o novo bloco e o adiciona no início da lista
        Bloco* novo = new Bloco(bloco);
        novo->prox = tabela[i];
        tabela[i] = novo;
    }

    // Função para salvar os resultados no arquivo de saída
    void salvarResultado(ofstream& out) {
        // Percorre a tabela e escreve cada bloco e sua contagem no arquivo de saída
        for (auto head : tabela) {
            while (head) {
                out << head->seq << " " << head->cont << "\n";  // Salva o bloco e a contagem
                head = head->prox;
            }
        }
    }
};

int main() {
    // Abre o arquivo de entrada (genoma) e o arquivo de saída (onde serão salvos os resultados)
    ifstream entrada("C:/Users/caiol/OneDrive/Documentos/CovidGenome/genome.txt");  // Caminho para o arquivo de entrada
    ofstream saida("result.txt");  // Caminho para o arquivo de saída

    // Verifica se o arquivo de entrada foi aberto corretamente
    if (!entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo genome.txt\n";
        return 1;
    }

    // Verifica se o arquivo de saída foi aberto corretamente
    if (!saida.is_open()) {
        cerr << "Erro ao criar result.txt\n";
        return 1;
    }

    // Inicializa a tabela de hash com o tamanho adequado para blocos de 6 caracteres (4096)
    TabelaHash tabela(4096);

    string linha;
    int linhasProcessadas = 0;  // Contador para saber quantas linhas de entrada foram processadas

    cout << "Lendo genoma e processando blocos de 6 bases...\n";

    // Processa o arquivo de entrada linha por linha
    while (getline(entrada, linha)) {
        // Ignora linhas menores que 6 caracteres, pois não podem formar um bloco completo
        if (linha.length() < 6) continue;

        // Ignora linhas de cabeçalho (que começam com '>')
        if (linha[0] == '>') continue;

        // Pega os blocos de 6 caracteres e os insere na tabela de hash
        for (size_t i = 0; i + 6 <= linha.length(); i++) {
            string bloco = linha.substr(i, 6);  // Extrai o bloco de 6 caracteres
            tabela.inserir(bloco);  // Insere o bloco na tabela
        }

        linhasProcessadas++;
    }

    // Exibe quantas linhas foram processadas
    cout << "Linhas processadas: " << linhasProcessadas << endl;
    cout << "Gravando resultados em result.txt...\n";

    // Salva os resultados no arquivo de saída
    tabela.salvarResultado(saida);

    // Fecha os arquivos de entrada e saída
    entrada.close();
    saida.close();

    cout << "Finalizado.\n";
    return 0;
}
