# Resolvendo o jogo 8Puzzle usando BFS em C
Este programa é uma implementação em liguagem C para resolver o jogo [8puzzle][1] usando o algoritmo de Breadth-First Search. A partir do estado inicial, digitado pelo usuário, o programa expande os possíveis casos derivados desse estado enquanto realiza uma busca em largura na arvore. Dessa forma, o programa consegue achar um caminho para a solução.

Ao rodar o programa teremos:
* As sequências de movimentos no tabuleiro até chegar na solução, sempre considerando o número 0 como o espaço em branco.
* O número de nós colocados na árvore (nós gerados)
* Número de estados enfileirados
* Quantidade de passos necessários para a solução,

O código foi feito da maneira mais manual possível para investigar o funcionamento do algoritmo e das estruturas de dados utilizadas. Dessa maneira, criei TAD's (Tipos Abstratos de Dados) para cada uma das estruturas utilizadas como a Lista, Fila (derivada da Lista) e Árvore (que são árvores genéricas que contém até 4 filhos e armazenam uma matriz, representando o tabuleiro do jogo).

##Compilação:
No linux, você pode compilar e executar na pasta do projeto usando:
```shell
make
./cliente
```

[1]: https://www.artbylogic.com/puzzles/numSlider/numberShuffle.htm?rows=3&cols=3&sqr=1
