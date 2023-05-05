# teoria_de_grafos_iris
05/05/2023
Nomes: César Eduardo de Souza & Bruno Arndt
Disciplina: Teoria de Grafos
Professor: Gilmário Barbosa dos Santos


O arquivo "iris.h" é usado para atribuir bibliotecas, declarar variáveis, constantes e funções.
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


