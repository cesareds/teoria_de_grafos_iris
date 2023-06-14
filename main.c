#include "iris.h"

int main() 
{
    //decalração do arquivo input csv:
    FILE *csv_input_vertices_dataset; 
    csv_input_vertices_dataset = fopen("./files/IrisDataset.csv", "r");
    if (csv_input_vertices_dataset == NULL) 
    {
        printf("Erro ao abrir o csv_input_vertices_dataset\n");
        return 1;
    }
    //declaração de txt de output para lista de adjacências:
    FILE *output_grafo;    
    output_grafo = fopen("./files/output_grafo.txt", "w");
    if(output_grafo == NULL)
    {
        printf("Erro ao criar csv_input_vertices_dataset de texto\n");
        exit(EXIT_FAILURE);
        return 1;
    }
    //declaração com alocação de matriz 150x150 de distâncias entre pontos:
    float **matriz_distancias = malloc(sizeof(float*) * L);
    for(i = 0; i < L; i++)
    {
        matriz_distancias[i] = malloc(sizeof(float) * L);
    }
    //declaração com alocação de matriz 150x150 binária que indica relações entre vértices:
    int **adjacencias = malloc(sizeof (int*) * L);
    for(i = 0; i < L; i++)
    {
        adjacencias[i] = malloc(sizeof (int) * L);
    }



    //copiando dados do csv para a matriz
    for (i = 0; i < L; i++) 
    {
        if (fgets(linha, 100, csv_input_vertices_dataset) != NULL) 
        {
            valor = strtok(linha, ",");
            for (j = 0; j < C; j++) 
            {
                matriz[i][j] = atof(valor);
                valor = strtok(NULL, ",");
            }
        }
    }
    fclose(csv_input_vertices_dataset);



    //preenchendo matriz de distâncias euclidianas entre vértices
    for(i =0; i < L; i++)
    {
        for(j = 0; j < L; j++)
        {
            float x1 = matriz[i][0];
            float x2 = matriz[j][0];
            float y1 = matriz[i][1];
            float y2 = matriz[j][1];
            float z1 = matriz[i][2];
            float z2 = matriz[j][2];
            float w1 = matriz[i][3];
            float w2 = matriz[j][3];
            float distancia_ij = distancia(x1, x2, y1, y2, z1, z2, w1, w2);
            matriz_distancias[i][j] = distancia_ij;
        }
    }



    //distancias normalizadas com suas respectivas arestas
    float maior_distancia = maior(matriz_distancias);
    float **distancias_normalizadas = normalizadas(matriz_distancias, maior_distancia);
    for(i = 0; i < L; i++)
    {
        for(j = i; j < L; j++)
        {
            printf("\n%f", distancias_normalizadas[i][j]);
            if(distancias_normalizadas[i][j]<=0.3)
            {
                adjacencias[i][j]=1;
                printf(" Liga por aresta os vértices %i e %i.\n", i, j);
            } else
            {
                adjacencias[i][j]=0;
            }
        }
    }



    //escreve no arquivo txt
    for(i = 0; i < L; i++)
    {
        for(j = 0; j < L; j++)
        {
            if(adjacencias[i][j])
            {
                fprintf(output_grafo,  "%i,%i\n", i, j);
            }
        }
    }
    fclose(output_grafo);

    converte_txt_para_dot("./files/output_grafo.txt", "./files/output.dot");

    // descomentar para exibir gráfico da maneira como foi idealizada pelo monitor da disciplina e gerar o .dot por meio de código python
    // system("./legacy/python3 txt_to_dot.py");
    // system("python3 ./legacy/displayGrafo.py");

    printf("\nO output_grafo será exibido: \n");
    
    system("neato -x -Goverlap=scale -Tpng ./files/output.dot > ./files/grafo.png");


    //fim
    printf("\n----FIM----\n");
    return 0;
}