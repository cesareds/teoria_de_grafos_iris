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
        printf("%i\n", i);
        normalizadas[i] = malloc(sizeof(float)*L);
    }
    for (i = 0; i < L; ++i) {
        for (j = 0; j < L; ++j) {
            printf("%f\n", distancias[i][j]);
        }
    }

    for(i = 0; i<L; i++){
        for(j = 0; j<L; j++){
            normalizadas[i][j]= distancias[i][j] / maior;
        }
    }

    return normalizadas;
}