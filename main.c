#include "header.h"

int main() {
    //Declaring arrays
    char* btc = "Data/BTC.txt";
    char* aga = "Data/AGA.txt";
    char* xrp = "Data/XRP.txt";
    char* tron = "Data/TRON.txt";
    char* eth = "Data/ETH.txt";
    char* bnb = "Data/BNB.txt";
    char* vet = "Data/VET.txt";

    float* BTC = arrayCreating(btc);
    int sizeBTC = countOfData(btc);
    float* AGA = arrayCreating(aga);
    int sizeAGA = countOfData(aga);
    float* XRP = arrayCreating(xrp);
    int sizeXRP = countOfData(xrp);
    float* TRON = arrayCreating(tron);
    int sizeTRON = countOfData(tron);
    float* ETH = arrayCreating(eth);
    int sizeETH = countOfData(eth);
    float* BNB = arrayCreating(bnb);
    int sizeBNB = countOfData(bnb);
    float* VET = arrayCreating(vet);
    int sizeVET = countOfData(vet);

    //Counting the means
    float meanBTC = Ex(BTC, sizeBTC);
    float meanAGA = Ex(AGA, sizeAGA);
    float meanXRP = Ex(XRP, sizeXRP);
    float meanTRON = Ex(TRON, sizeTRON);
    float meanETH = Ex(ETH, sizeETH);
    float meanBNB = Ex(BNB, sizeBNB);
    float meanVET = Ex(VET, sizeVET);

    //Countiong the variances
    float varianceBTC = var(BTC, sizeBTC);
    float varianceAGA = var(AGA, sizeAGA);
    float varianceXRP = var(XRP, sizeXRP);
    float varianceTRON = var(TRON, sizeTRON);
    float varianceETH = var(ETH, sizeETH);
    float varianceBNB = var(BNB, sizeBNB);
    float varianceVET = var(VET, sizeVET);

    //Counting the correlation with Bitcoin
    float agaCorelationWithBtc = correlation(BTC, AGA, sizeBTC, sizeAGA);
    float xrpCorelationWithBtc = correlation(BTC, XRP, sizeBTC, sizeXRP);
    float tronCorelationWithBtc = correlation(BTC, TRON, sizeBTC, sizeTRON);
    float vetCorelationWithBtc = correlation(BTC, VET, sizeBTC, sizeVET);
    float ethCorelationWithBtc = correlation(BTC, ETH, sizeBTC, sizeETH);
    float bnbCorelationWithBtc = correlation(BTC, BNB, sizeBTC, sizeBNB);

    //Printing the result using ASCII codes
    printf("                        -----------------------------------------------------------------------------------------------------------------\n");
    printf("                        |\tBTC\t|\tAGA\t|\tXRP\t|\tTRON\t| \tBNB\t|\tVET \t| \tETH \t|\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| MEAN\t\t\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\n", 
        meanBTC, meanAGA, meanXRP, meanTRON, meanBNB, meanVET, meanETH);
    printf("| VARIANCE\t\t|    %0.2f\t|    %0.2f\t|    %0.2f\t|    %0.2f\t|    %0.2f\t|    %0.2f\t|    %0.2f\t|\n", 
        varianceBTC, varianceAGA, varianceXRP, varianceTRON, varianceBNB, varianceVET, varianceETH);
    printf("| CORELATION WITH BTC\t|\t\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\n", 
        agaCorelationWithBtc, xrpCorelationWithBtc, tronCorelationWithBtc, bnbCorelationWithBtc, vetCorelationWithBtc, ethCorelationWithBtc);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
    
    //Asking user if they want to count the portfolio risk
    printf("Do you want to count portfolio risk? (1=yes, 0=no)");

    int answer;
    scanf("%d", &answer);

    if (answer == 1)
    {
        portfolioRisk(BTC, AGA, XRP, TRON, BNB, VET, ETH, sizeBTC, sizeAGA, sizeXRP, sizeTRON, sizeBNB, sizeVET, sizeETH);
    } else if (answer != 0)
    {
        printf("Answer should be 1 or 0. Run the code again.");
    }

    //The end of program
    free(BTC);
    free(AGA);
    free(XRP);
    free(TRON);
    free(ETH);
    free(BNB);
    free(VET);

    return 0;
}
