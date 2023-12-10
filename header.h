#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#define EPSILION 0.00001

extern int countOfData(char* filename);
extern float* arrayCreating(char* filename);
extern float Ex(float* arr, int size);
extern float cov(float* arr1, float* arr2, int size1, int size2);
extern float var(float* arr, int size);
extern float correlation(float* arr1, float* arr2, int size1, int size2);
extern float sigma(float* arr, int size);
extern void portfolioRisk(float* btc, float* aga, float* xrp, float* tron, float* bnb, float* vet, float* eth, int sizeBTC, int sizeAGA, int sizeXRP, int sizeTRON, int sizeBNB, int sizeVET, int sizeETH);

#endif