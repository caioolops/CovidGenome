# CovidGenome

Este projeto tem como objetivo **processar sequências de DNA** (ou sequências de qualquer tipo) e **contar blocos consecutivos de 6 caracteres**. Utilizando **hash table**, ele lê o arquivo de entrada, divide-o em blocos e conta quantas vezes cada bloco de 6 caracteres se repete, gerando um arquivo de resultado.

## O que foi feito:

- O código lê um arquivo de entrada contendo sequências de texto (como o genoma do coronavírus ou outras sequências alfanuméricas).
- Ele **processa a sequência em blocos de 6 caracteres** e usa uma **tabela de hash manual** com **encadeamento externo** para contar quantas vezes cada bloco aparece.
- O resultado é gravado no arquivo **`result.txt`**, que contém os **blocos de 6 caracteres** e a **quantidade de repetições** de cada bloco.

## Estrutura do Projeto:

O código está dividido da seguinte maneira:

- **`main.cpp`**: Este é o arquivo principal, que contém a implementação da lógica de contagem dos blocos de 6 caracteres.
- **`TabelaHash`**: A classe que implementa a **tabela de hash** com encadeamento externo para contar as repetições de blocos.

## Como Usar:

1. **Compilar o Código**:
   - O projeto foi desenvolvido utilizando **Code::Blocks**. Se você estiver usando o Code::Blocks, basta abrir o arquivo **`main.cpp`**, compilar e rodar o programa.
   - Caso queira compilar manualmente no terminal, utilize o comando:
     ```bash
     g++ -o CovidGenome main.cpp
     ```
   - O arquivo **`result.txt`** será gerado automaticamente após a execução.

2. **Alterar o Diretório para Testes**:
   - O programa tenta abrir o arquivo **`genome.txt`** no mesmo diretório do executável. Caso queira usar um arquivo de entrada diferente ou se ele estiver em outro diretório, altere o caminho do arquivo no código:
     ```cpp
     ifstream entrada("C:/caminho/genome.txt");
     ```

3. **Erro Comum (Espaços no Caminho)**:
   - Se o diretório onde está o seu arquivo contiver **espaços** (como "Sistemas de Informação"), o programa pode não funcionar corretamente. (sofri bastante com isso aqui)
