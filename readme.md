# PAA - Trabalho 4

## Especificação

**Tarefa**: 

1. Implementar o algoritmo de Dijkstra de forma que todos os vértices sejam o ponto de origem.
2. Implementar o método de Floyd-Warshall.

**Como**:

* Linguagem utilizada no desenvolvimento é de vossa escolha.
* A forma com que os métoos serão implementados é determinada pelo grupo. No entanto, deve-se adotar a mesma abordagem para ambos os métodos.
* Os dados a serem empregados na construção dos grafos estão disponiveis no endereço a seguir:
  * [Arquivos de teste](https://drive.google.com/file/d/1Nww_7s6a4Q6k6XtNqJ0O4fMp5UpOMifB/view?usp=sharing)

Critérios que devem ser analisados:

* Tempo cronológico para execução de Floyd-Warshall;
* Tempo cronológico para V execuções do algoritmo ed Dijkstra;
* Número de testes para checar se o novo caminho é melhor ou pior que o já conhecido;

### Relatório

* Descrição de como foi realizado o processo empírico dos custos
  * Cenário de realização dos experimentos e como foram tomadas as métricas exigidas.
  * Detalhar a configuração utilizada nos testes (processador, SO, IDE...).
* Gráficos evidenciando o comportamento dos métodos perante todos os cenários considerando o tamanho dos conjuntos de entrada.
* Análize do comportamento dos métodos durante a execução dos testes.
* O formato do relatório deve seguir o padrão [SBC](https://www.sbc.org.br/documentos-da-sbc/summary/169-templates-para-artigos-e-capitulos-de-livros/878-modelosparapublicaodeartigos).

## Projeto

Código fonte da implementação se encontra em `/src`.

Configurações de projeto geradas a partir de `premake5`.

Automatização de testes utilizando o script `run_tests.py`.

### GMAKE

```sh
premake5 gmake
make
```
