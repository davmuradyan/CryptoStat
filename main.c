#include "header.h"

int main() {

    //Names of the files, that contain the data
    char* btcName = "Data/BTC.txt";
    char* agaName = "Data/AGA.txt";
    char* xrpName = "Data/XRP.txt";
    char* bnbName = "Data/BNB.txt";
    char* ethName = "Data/ETH.txt";
    char* tronName = "Data/TRON.txt";
    char* vetName = "Data/VET.txt";

    //Declaring linked lists that contain data from files
    Node* BTC = readDataFromFile(btcName);
    Node* AGA = readDataFromFile(agaName);
    Node* XRP = readDataFromFile(xrpName);
    Node* BNB = readDataFromFile(xrpName);
    Node* ETH = readDataFromFile(ethName);
    Node* TRON = readDataFromFile(tronName);
    Node* VET = readDataFromFile(vetName);

    //Counting means of the data of linked lists
    float meanBTC = Ex(BTC);
    float meanAGA = Ex(AGA);
    float meanXRP = Ex(XRP);
    float meanTRON = Ex(TRON);
    float meanBNB = Ex(BNB);
    float meanVET = Ex(VET);
    float meanETH = Ex(ETH);

    //Counting variances of the data of linked lists
    float varianceBTC = var(BTC);
    float varianceAGA = var(AGA);
    float varianceXRP = var(XRP);
    float varianceTRON = var(TRON);
    float varianceBNB = var(BNB);
    float varianceVET = var(VET);
    float varianceETH = var(ETH); 

    //Counting linear corelation with Bitcoin
    float agaCorelationWithBtc = corelation(BTC, AGA);
    float xrpCorelationWithBtc = corelation(BTC, XRP);
    float tronCorelationWithBtc = corelation(BTC, TRON);
    float bnbCorelationWithBtc = corelation(BTC, BNB);
    float vetCorelationWithBtc = corelation(BTC, VET);
    float ethCorelationWithBtc = corelation(BTC, ETH);

    //Printing the results using ASCII codes
    printf("                        -----------------------------------------------------------------------------------------------------------------\n");
    printf("                        |\tBTC\t|\tAGA\t|\tXRP\t|\tTRON\t| \tBNB\t|\tVET \t| \tETH \t|\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| MEAN\t\t\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\n", 
        meanBTC, meanAGA, meanXRP, meanTRON, meanBNB, meanVET, meanETH);
    printf("| VARIANCE\t\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|\n", 
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
        portfolioRisk(BTC, AGA, XRP, TRON, BNB, VET, ETH);
    } else if (answer != 0)
    {
        printf("Answer should be 1 or 0. Run the code again.");
    }

    //End of the program
    freeLinkedList(BTC);
    freeLinkedList(AGA);
    freeLinkedList(XRP);
    freeLinkedList(TRON);
    freeLinkedList(BNB);
    freeLinkedList(VET);
    freeLinkedList(ETH);

    return 0;
}