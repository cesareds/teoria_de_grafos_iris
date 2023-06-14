#include "iris.h"

float distancia(float x1, float  x2, float y1, float y2, float z1, float z2, float w1, float w2){
    return sqrt(pow((x1-x2), 2) + pow((y1-y2), 2) + pow((z1-z2), 2) + pow((w1-w2), 2));
}
float maior(float **lista){
    float maior = lista[0][0];

    for(i = 1; i<L; i++){
        for(j = 0; j<L; j++){
            if(lista[i][j]>maior){
                maior = lista[i][j];
            }
        }
    }
    return maior;
}
float **normalizadas(float **distancias, float maior){
    float **normalizadas = malloc(sizeof(float*)*L);
    for(i = 0; i<L; i++){
        //printf("%i\n", i);
        normalizadas[i] = malloc(sizeof(float)*L);
    }
    for (i = 0; i < L; ++i) {
        for (j = 0; j < L; ++j) {
            //printf("%f\n", distancias[i][j]);
        }
    }

    for(i = 0; i<L; i++){
        for(j = 0; j<L; j++){
            normalizadas[i][j]= distancias[i][j] / maior;
        }
    }

    return normalizadas;
}

void limiarizacao(int **adjacencias, float **distancias_normalizadas, float limiar){
    for(i = 0; i < L; i++)
    {
        for(j = 0; j < L; j++)
        {
            //printf("\n%f", distancias_normalizadas[i][j]);
            if(i!=j && distancias_normalizadas[i][j]<=limiar)
            //cria varios grafos
            //calcula limiar com grafo separado com cluster contendo entre 5 e 50
            {
                adjacencias[i][j]=1;
                //printf(" Liga por aresta os vértices %i e %i.\n", i, j);
            } else
            {
                adjacencias[i][j]=0;
            }
        }
    }
}


void separarClusters(int grafo[][MAX_VERTICES], int numVertices, Cluster clusters[], int *numClusters) {
    int i, j, k;
    int visitados[MAX_VERTICES] = {0};

    *numClusters = 0;

    for (i = 0; i < numVertices; i++) {
        if (!visitados[i]) {
            // Inicializar um novo cluster
            clusters[*numClusters].numVertices = 0;

            // Marcar o vértice atual como visitado
            visitados[i] = 1;

            // Adicionar o vértice atual ao cluster
            clusters[*numClusters].vertices[clusters[*numClusters].numVertices++] = i;

            // Percorrer o grafo em busca de vértices não visitados conectados ao atual
            for (j = 0; j < numVertices; j++) {
                if (grafo[i][j] && !visitados[j]) {
                    visitados[j] = 1;
                    clusters[*numClusters].vertices[clusters[*numClusters].numVertices++] = j;
                }
            }

            (*numClusters)++;
        }
    }
}

void dfs_call(int vertex,int** adjacencias, int* visitado){
    visitado[vertex] = 1;
    for(int vizinho = 0; vizinho < L; vizinho++){
        if(vizinho != vertex && adjacencias[vertex][vizinho] == 1 && visitado[vizinho] == 0){
            dfs_call(vizinho, adjacencias, visitado);
        }
    }
}

void dfs(int vertex, int** adjacencias){
    int* visitado = calloc(L, sizeof(int));
    dfs_call(vertex, adjacencias, visitado);
    free(visitado);
}

void dfs_group(int vertex, int group, int** adjacencias, int* groups){
    groups[vertex] = group;
    for(int vizinho = 0; vizinho < L; vizinho++){
        if(vizinho != vertex && adjacencias[vertex][vizinho] == 1 && groups[vizinho] == -1){
            dfs_group(vizinho, group, adjacencias, groups);
        }
    }
}

int cnt_conected_components(int** adjacencias){
    int cnt = 0;
    int* groups = calloc(L, sizeof(int));
    for(int i = 0; i < L; i++){
        groups[i] = -1;
    }
    for(int origin = 0; origin < L; origin++){
        if(groups[origin] == -1){
            cnt++;
            dfs_group(origin, origin, adjacencias, groups);
        }
    }
    free(groups);

    return cnt;
}

void converte_txt_para_dot(const char* txt_file, const char* dot_file) {
    FILE* txt_fp = fopen(txt_file, "r");
    if (txt_fp == NULL) {
        printf("Erro ao abrir o arquivo txt.\n");
        return;
    }

    FILE* dot_fp = fopen(dot_file, "w");
    if (dot_fp == NULL) {
        printf("Erro ao carregar o arquivo dot.\n");
        fclose(txt_fp);
        return;
    }

    fprintf(dot_fp, "graph G{\n");

    char line[100];
    while (fgets(line, sizeof(line), txt_fp) != NULL) {
        char* token = strtok(line, ",");
        int first = atoi(token);

        token = strtok(NULL, ",");
        int second = atoi(token);

        fprintf(dot_fp, "%d--%d;\n", first, second);
    }

    fprintf(dot_fp, "}");

    fclose(txt_fp);
    fclose(dot_fp);

    printf("Arquivo convertido de .txt para .dot\n");
}