# TP 1 Estrutura de Dados 25 2

Este projeto é a implementação do Trabalho Prático 1 (TP1) da disciplina de Estruturas de Dados (DCC205/DCC221) da UFMG, com o tema **Identificação de Objetos Oclusos**.

---

## O Problema

O objetivo do trabalho é desenvolver um programa em C/C++ para simular a apresentação de objetos unidimensionais em uma cena, aplicando o algoritmo de **oclusão** para exibir apenas os segmentos visíveis dos objetos, otimizando o desempenho de renderização.

A entrada é um arquivo contendo instruções sobre a criação, movimentação e geração de cenas dos objetos, que são segmentos de reta paralelos ao eixo X. A oclusão é determinada pela **profundidade (coordenada Y)**: objetos com maior valor de `Y` estão em primeiro plano e ocluem aqueles com menor `Y`.

### Formato de Entrada

| Tipo | Descrição | Formato | Exemplo |
| :--- | :--- | :--- | :--- |
| **Objeto** (`O`) | Cria um objeto, definindo ID, posição inicial (centro) e largura. | `O <id> <x> <y> <largura>` | `O 1 4.0 2.5 3` |
| **Movimento** (`M`) | Move um objeto para uma nova posição em uma marca de tempo. | `M <tempo> <id> <novo_x> <novo_y>` | `M 5 2 2.5 5` |
| **Cena** (`C`) | Gera a cena no tempo especificado. | `C <tempo>` | `C 10` |

### Formato de Saída

Para cada linha do tipo `Cena` na entrada, o programa deve gerar uma série de linhas de saída, cada uma representando um segmento visível de um objeto.

| Tipo | Descrição | Formato | Exemplo |
| :--- | :--- | :--- | :--- |
| **Saída** (`S`) | Segmento visível do objeto, com ID e a posição inicial e final da visualização. | `S <tempo> <id_obj> <inicio> <fim>` | `S 10 2 2 3` |

---

## Solução e Funcionalidades

A solução foi implementada em linguagem **C**, utilizando uma abordagem modular com o código organizado em diretórios para cabeçalhos (`include`), fontes (`src`) e executáveis (`bin`), e utiliza **Tipos Abstratos de Dados (TADs)** para gerenciar a lógica do programa.

### Estruturas de Dados (TADs)

As principais estruturas de dados foram definidas como `structs` e armazenadas em **vetores estáticos** para garantir a contiguidade dos dados:

* **`Objeto_t`:** Armazena `id`, as coordenadas do centro (`x`, `y`), `largura` e os limites horizontais (`inicioX`, `fimX`). A posição inicial e final no eixo X são calculadas como `x ± (largura/2.0f)`.
* **`Cena_t`:** Representa um segmento visível, contendo `num_cena` (tempo), `id_obj`, e as coordenadas de `inicio` e `fim` desse segmento.
* **`Intervalo_t`:** Uma estrutura auxiliar com `inicio` e `fim`, utilizada para gerenciar os intervalos do eixo X que estão **oclusos** (já cobertos por objetos de primeiro plano).

### Algoritmo Principal de Oclusão

A lógica de geração de cena é encapsulada na função `GeraCena`, que tem como base o algoritmo descrito no documento do trabalho:

1.  **Ordenação:** O vetor de objetos (`vetorObjs`) é ordenado pelo seu valor de `y` (profundidade), garantindo que os objetos mais próximos ao observador (maior `y`) sejam processados primeiro. O algoritmo utilizado é o **QuickSort** (`QuickSort`).
2.  **Identificação e Adição de Segmentos:** Para cada objeto, a função `AddObjeto` percorre sua extensão horizontal, verifica se o segmento atual está contido em algum intervalo ocluso existente, e adiciona os segmentos não oclusos (visíveis) ao vetor de cena (`vetorCena`).
3.  **Atualização e Mesclagem de Oclusão:** Após o processamento de um objeto, sua extensão horizontal (`inicioX` a `fimX`) é adicionada à lista de intervalos oclusos pela função `AdicionarIntervaloOclusao`. Esta função utiliza o `QuickSortIntervalo` para ordenar os intervalos e, em seguida, **mescla** intervalos sobrepostos ou adjacentes para manter o conjunto de áreas oclusas otimizado.
4.  **Ordenação Final da Cena:** Ao final, o vetor `vetorCena` é ordenado por `id_obj` e `inicio` usando `QuickSortCena` para produzir a saída final organizada.

### Estratégias de Ordenação de Objetos

O projeto investiga o compromisso entre a frequência de ordenação e a geração de cenas. Três estratégias foram implementadas e comparadas experimentalmente, controladas por diretivas `#define` em `src/main.c`:

* **Ordena na Cena** (`#define ORDENAR_NA_CENA`): A ordenação é executada **apenas** quando uma cena é solicitada (`C`). Ideal para cenários com baixa frequência de renderização.
* **Ordena com Limiar** (`#define ORDENAR_COM_LIMIAR`): A ordenação é realizada a cada movimento (`M`) **somente** se uma métrica de "desordem" (`contador_desorganizacao`) atingir um limiar pré-definido (`LIMIAR_DESORGANIZACAO`). Representa um equilíbrio eficiente.
* **Ordena Sempre** (`#define ORDENAR_SEMPRE`): A ordenação é executada a **cada** operação de movimento (`M`), mantendo o vetor constantemente ordenado.

O código-fonte (`src/main.c`) utiliza a estratégia **Ordena na Cena** como padrão, baseada nos resultados da análise experimental que a consideraram a mais eficiente ou de desempenho similar à "Ordena com Limiar".

---

## Instruções de Uso

Para compilar e executar o programa, você precisará ter o **GCC** e o utilitário **Make** instalados em um ambiente Linux (ou compatível).

### 1. Estrutura do Projeto

O projeto segue a estrutura de diretórios padrão exigida:  

├── src/ (Arquivos fonte *.c)  
├── include/ (Arquivos de cabeçalho *.h)  
├── bin/ (Executável tp1.out)  
├── obj/ (Arquivos objeto *.o)  
└── Makefile (Script de compilação)

### 2. Compilação

1.  Acesse o diretório raiz do projeto (onde está o `Makefile`).
2.  Execute o comando para compilar o projeto:

    ```bash
    make all
    ```

    Este comando irá compilar o código-fonte, gerar os arquivos objeto (`.o`) na pasta `obj/` e criar o executável **`tp1.out`** na pasta **`bin/`**.

### 3. Execução

O programa lê as instruções a partir da entrada padrão (`stdin`).

1.  Para executar o programa, redirecionando o conteúdo de um arquivo de entrada:

    ```bash
    ./bin/tp1.out < caminho/para/seu/arquivo_de_entrada.txt
    ```

    *Exemplo:*
    ```bash
    ./bin/tp1.out < testes/inputs5.txt
    ```

2.  Para salvar a saída (as cenas geradas) em um arquivo, use o redirecionamento de saída:

    ```bash
    ./bin/tp1.out < caminho/para/seu/arquivo_de_entrada.txt > arquivo_de_saida.txt
    ```

    *As mensagens de **"Aviso"** e o **"Tempo de execucao"** são impressas na saída de erro padrão (`stderr`) e aparecerão no terminal, não sendo salvas no arquivo de saída.*