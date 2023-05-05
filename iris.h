//César Eduardo de Souza & Bruno Arndt
#ifndef IRIS_H_ 
#define IRIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define L 150
#define C 4

int i, j;
float matriz[L][C];
char linha[100];
char *valor;


float distancia(float x1, float x2, float y1, float y2, float z1, float z2, float w1, float w2);
float maior(float **lista);
float **normalizadas(float **distancias, float maior);

#endif 
