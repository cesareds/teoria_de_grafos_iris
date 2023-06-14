# teoria_de_grafos_iris

## O trabalho visa treinar um modelo que separe bases de dados em grupos, utilizando grafos.

- Autores: César Eduardo de Souza & Bruno Arndt
- Disciplina: Teoria de Grafos (TEG: 4º Fase do curso Bacharelado em Ciência da Computação na UDESC)
- Professor: Gilmário Barbosa dos Santos

## Pré-requisitos

- Clang

## Compilação

```console
    clang main.c iris.c -lm
```

## Grafo gerado a partir de lista de adjacências

![eita nois](https://github.com/cesareds/teoria_de_grafos_iris/blob/main/files/grafo.png?raw=true)

## Mais informações

O arquivo "iris.h" é usado para atribuir bibliotecas, declarar variáveis, constantes e funções (funciona usando CLang).
O tal é conectado ao "iris.c", que descreve as funções usadas pela main.
Tal qual executa o seguinte algoritmo: 
    abre os arquivos "IrisDataset.csv" e "output_grafo.txt";
    aloca espaços de memória para as matrizes;
    transfere os dados do csv para a matriz 150x4;
    calcula as dintâncias euclidianas entre os vértices, salvando-as numa matriz 150x150;
    normaliza as distâncias dessa matriz;
    define adjacência entre os vértices caso a tal seja menor que 0.3;
    escreve as tais num arquivo "output_grafo.txt" 
    executa uma chamada de sistema para executar o código Python (disponibilizado no Moodle pelo professor) para gerar e exibir o grafo;
    termina a execução;


