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
    float limiar = 0.2;
    

    
    // while(limiar<0.3)
    // {
    //     int *grafo_final[2];
    //     int count;
    //     limiarizacao(adjacencias, distancias_normalizadas, limiar);
    //     //escreve no arquivo txt
    //     for(i = 0; i < L; i++)
    //     {
    //         for(j = 0; j < L; j++)
    //         {
    //             if(adjacencias[i][j])
    //             {
    //                 fprintf(output_grafo,  "%i,%i\n", i, j);
    //                 grafo_final[0] = realloc(sizeof(int) * count);
    //                 grafo_final[1] = realloc(sizeof(int) * count);
    //                 grafo_final[0][count] = i;
    //                 grafo_final[1][count] = j;
    //                 count++;
    //             }
    //         }
    //     }


    //     //incrementa o limiar
    //     limiar=limiar+0.0005;
    // }

    limiar = 0;
    while(limiar<=1)
    {
        limiarizacao(adjacencias, distancias_normalizadas, limiar);

        if(cnt_conected_components(adjacencias) <= 3) break;

        //incrementa o limiar
        limiar=limiar+0.0001;
    }
    printf("Limiar: %f\n", limiar);
    printf("Qnt Grupos: %d\n", cnt_conected_components(adjacencias));


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

    printf("\nO output_grafo será gerado: \n");
    system("neato -x -Goverlap=scale -Tpng ./files/output.dot > ./files/grafo.png");
    printf("dfs:\n");
    system("python3 dfs.py");


    //fim
    printf("\n----FIM----\n");
    return 0;
}