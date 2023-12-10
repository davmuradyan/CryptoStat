#include "header.h"

//Function to count the amount of data
int countOfData(char* filename) {
    float data;
    int count = 0;
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("File could not be opened.");
        return 1;
    }
    while (fscanf(file, "%f", &data) == 1) {
        count++;
    }
    fclose(file);
    
    return count;
}

//Function to create an array
float* arrayCreating(char* filename) {
    int dataCount = countOfData(filename);

    if (dataCount == -1) {
        return NULL; // Error in opening file
    }

    float* crypto = (float*)malloc(sizeof(float) * dataCount);
    if (crypto == NULL) {
        printf("Memory allocation failed.");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("The file %s could not be opened.", filename);
        free(crypto); // Free allocated memory before exiting
        return NULL;
    }

    for (int i = 0; i < dataCount; i++) {
        fscanf(file, "%f", &crypto[i]);
    }

    fclose(file);
    return crypto;
}

//Function to count the mean
float Ex(float* arr, int size) {
    float sum = 0;
    int count = 0;
    int i = 0;
    while (i != size)
    {
        sum += *(arr+i);
        count++;
        i++;
    }
    
    return sum/count;
}

//Function to count the covariance
float cov(float* arr1, float* arr2, int size1, int size2) {
    float E1 = Ex(arr1, size1);
    float E2 = Ex(arr2, size2);
    int numOfData = (size1 <= size2) ? size1 : size2;
    float sum = 0;

    int i;
    for (i = 0; i < numOfData; i++) {
        sum += (arr1[i] - E1) * (arr2[i] - E2);
    }

    return sum / (numOfData - 1);
}

//Function to count the variance
float var(float* arr, int size) {
    float E = Ex(arr, size);
    int numOfData = size;
    float sum = 0;

    for (int i = 0; i < numOfData; i++) {
        sum += (arr[i] - E) * (arr[i] - E);
    }

    return sum / (numOfData - 1);
}

//Function to count the linear correlation
float correlation(float* arr1, float* arr2, int size1, int size2) {
    float covXY = cov(arr1, arr2, size1, size2);
    float varX = var(arr1, size1);
    float varY = var(arr2, size2);

    return covXY / sqrt(varX * varY);
}

//Function to count the standard deviation
float sigma(float* arr, int size) {
    float varA  = var(arr, size);
    return sqrt(varA);
}

//Function to count the portfolio risk
void portfolioRisk(float* btc, float* aga, float* xrp, float* tron, float* bnb, float* vet, float* eth, int sizeBTC, int sizeAGA, int sizeXRP, int sizeTRON, int sizeBNB, int sizeVET, int sizeETH) {
    float w[7]; // Array to store weights for cryptocurrencies
    printf("Enter the weights of the following cryptocurrencies: BTC, AGA, XRP, TRON, BNB, VET, ETH\n");
    
    // Input weights for each cryptocurrency
    float totalWeight = 0.0;
    for (int i = 0; i < 7; i++) {
        printf("%s (%.2f/1.00): ", (i == 0) ? "BTC" : (i == 1) ? "AGA" : (i == 2) ? "XRP" : (i == 3) ? "TRON" : (i == 4) ? "BNB" : (i == 5) ? "VET" : "ETH", totalWeight);
        scanf("%f", &w[i]);
        totalWeight += w[i];
    }

    if (totalWeight > 1.0 + EPSILION || totalWeight < 1.0 - EPSILION) {
        printf("Error: The sum of weights should be equal to 1.00. The entered total weight is %.2f\n", totalWeight);
        return;
    }

    float o = sqrt(sqrt(pow(
    w[0] * w[1] * sigma(btc, sizeBTC) * sigma(aga, sizeAGA) * cov(btc, aga, sizeBTC, sizeAGA) +
    w[0] * w[2] * sigma(btc, sizeBTC) * sigma(xrp, sizeXRP) * cov(btc, xrp, sizeBTC, sizeXRP) +
    w[0] * w[3] * sigma(btc, sizeBTC) * sigma(tron, sizeTRON) * cov(btc, tron, sizeBTC, sizeTRON) +
    w[0] * w[4] * sigma(btc, sizeBTC) * sigma(bnb, sizeBNB) * cov(btc, bnb, sizeBTC, sizeBNB) +
    w[0] * w[5] * sigma(btc, sizeBTC) * sigma(vet, sizeVET) * cov(btc, vet, sizeBTC, sizeVET) +
    w[0] * w[6] * sigma(btc, sizeBTC) * sigma(eth, sizeETH) * cov(btc, eth, sizeBTC, sizeETH) +
    w[1] * w[2] * sigma(aga, sizeAGA) * sigma(xrp, sizeXRP) * cov(aga, xrp, sizeAGA, sizeXRP) +
    w[1] * w[3] * sigma(aga, sizeAGA) * sigma(tron, sizeTRON) * cov(aga, tron, sizeAGA, sizeTRON) +
    w[1] * w[4] * sigma(aga, sizeAGA) * sigma(bnb, sizeBNB) * cov(aga, bnb, sizeAGA, sizeBNB) +
    w[1] * w[5] * sigma(aga, sizeAGA) * sigma(vet, sizeVET) * cov(aga, vet, sizeAGA, sizeVET) +
    w[1] * w[6] * sigma(aga, sizeAGA) * sigma(eth, sizeETH) * cov(aga, eth, sizeAGA, sizeETH) +
    w[2] * w[3] * sigma(xrp, sizeXRP) * sigma(tron, sizeTRON) * cov(xrp, tron, sizeXRP, sizeTRON) +
    w[2] * w[4] * sigma(xrp, sizeXRP) * sigma(bnb, sizeBNB) * cov(xrp, bnb, sizeXRP, sizeBNB) +
    w[2] * w[5] * sigma(xrp, sizeXRP) * sigma(vet, sizeVET) * cov(xrp, vet, sizeXRP, sizeVET) +
    w[2] * w[6] * sigma(xrp, sizeXRP) * sigma(eth, sizeETH) * cov(xrp, eth, sizeXRP, sizeETH) +
    w[3] * w[4] * sigma(tron, sizeTRON) * sigma(bnb, sizeBNB) * cov(tron, bnb, sizeTRON, sizeBNB) +
    w[3] * w[5] * sigma(tron, sizeTRON) * sigma(vet, sizeVET) * cov(tron, vet, sizeTRON, sizeVET) +
    w[3] * w[6] * sigma(tron, sizeTRON) * sigma(eth, sizeETH) * cov(tron, eth, sizeTRON, sizeETH) +
    w[4] * w[5] * sigma(bnb, sizeBNB) * sigma(vet, sizeVET) * cov(bnb, vet, sizeBNB, sizeVET) +
    w[4] * w[6] * sigma(bnb, sizeBNB) * sigma(eth, sizeETH) * cov(bnb, eth, sizeBNB, sizeETH) +
    w[5] * w[6] * sigma(vet, sizeVET) * sigma(eth, sizeETH) * cov(vet, eth, sizeVET, sizeETH)
, 2)));


    // Print portfolio weights
    printf("------------------------------------------------------------------------------------------\n");
    printf("|    BTC    |    AGA    |    XRP    |    TRON    |     BNB    |    VET     |     ETH     |\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("|    %.2f   |    %.2f   |    %.2f   |    %.2f    |     %.2f   |    %.2f    |     %.2f    |\n",
           w[0], w[1], w[2], w[3], w[4], w[5], w[6]);
    printf("------------------------------------------------------------------------------------------\n");
    printf("Portfolio risk is %.2f\n", o);
    printf("-------------------------\n");
}