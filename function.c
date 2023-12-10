#include "header.h"

//Functions that are needed for creating linked lists

Node* createNode(float data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 
    if (newNode != NULL) {
        newNode->data = data; 
        newNode->next = NULL; 
    }
    return newNode;
}

void append(Node** head, float data) {
    Node* new_node = createNode(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* last_node = *head;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }
    last_node->next = new_node;
}

//Function to count the length of linked list
int sizeOfList(Node* head) {
    int count = 0;
    Node* current_node = head;
    while (current_node != NULL) {
        count++;
        current_node = current_node->next;
    }
    return count;
}

//Function to free linked lists
void freeLinkedList(Node* head) {
    Node* current = head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

//Function to fill the data into linked lists
Node* readDataFromFile(const char* filename) {
    Node* list = NULL;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file %s.\n", filename);
        return NULL;
    }

    float data;
    while (fscanf(file, "%f", &data) != EOF) {
        append(&list, data);
    }

    fclose(file);
    return list;
}

//Functions for counting the mean
float Ex(Node* list) {
    Node* current_node = list;
    float sum = 0;
    int count = 0;
    while (current_node != NULL) {
        sum += current_node->data;
        count++;
        current_node = current_node->next;
    }
    if (count == 0) {
        return 0;
    }
    freeLinkedList(current_node);
    return sum / count;
}

//Function to count the covariance between two cryptocurrencies
float cov(Node* list1, Node* list2) {
    float E1 = Ex(list1);
    float E2 = Ex(list2);
    int size1 = sizeOfList(list1);
    int size2 = sizeOfList(list2);
    int numOfData = (size1 <= size2) ? size1 : size2;
    float sum = 0;

    int i = 0;
    Node* x = list1;
    Node* y = list2;
    while (i<numOfData)
    {
        sum += (x->data-E1)*(y->data-E2);
        x = x->next;
        y = y->next;
        i++;
    }
    freeLinkedList(x);
    freeLinkedList(y);

    return  sum/(numOfData-1);
}   

//Function to count the variance
float var(Node* list) {
    float E = Ex(list);
    int numOfData = sizeOfList(list);
    float sum = 0;
    int i = 0;

    Node* x = list;

    while (i<numOfData)
    {
        sum += (x->data - E)*(x->data - E);
        x = x->next;
        i++;
    }
    freeLinkedList(x);
    return sum/(numOfData-1);
}

//Function to count the corelation
float corelation (Node* list1, Node* list2) {
    float E1 = Ex(list1);
    float E2 = Ex(list2);
    int size1 = sizeOfList(list1);
    int size2 = sizeOfList(list2);
    int numOfData = (size1 <= size2) ? size1 : size2;
    float upperSum = cov(list1, list2)*(numOfData-1);
    float sumOfChangeX = 0;
    float sumOfChangeY = 0;
    float corelation;

    Node* x = list1;
    int i = 0;
    while (i<numOfData)
    {
        sumOfChangeX += pow((x->data-E1), 2);
        x = x->next;
        i++;
    }
    
    Node* y = list2;
    i = 0;
    while (i<numOfData)
    {
        sumOfChangeY += pow((y->data-E2), 2);
        y = y->next;
        i++;
    }

    corelation = (upperSum)/sqrt(sumOfChangeX*sumOfChangeY);
    freeLinkedList(x);
    freeLinkedList(y);
    return corelation;
}

//Function to count the standard deviation
float sigma(Node* list) {
    return sqrt(var(list));
}

//Function to count the portfolio risk
void portfolioRisk(Node* btc, Node* aga, Node* xrp, Node* tron, Node* bnb, Node* vet, Node* eth) {
    
    float w1, w2, w3, w4, w5, w6, w7;
    printf("Enetr the weights of following cryptocurrencies: BTC, AGA, XRP, TRON, BNB, VET, ETH\n");
    printf("BTC (0.00/1.00)");
    scanf("%f", &w1);
    printf("\nAGA (%.2f/1.00)", w1);
    scanf("%f", &w2);
    printf("\nXRP (%f/1.00)", w1+w2);
    scanf("%f", &w3);
    printf("\nTRON (%f/1.00)", w1+w2+w3);
    scanf("%f", &w4);
    printf("\nBNB (%f/1.00)", w1+w2+w3+w4);
    scanf("%f", &w5);
    printf("\nVET (%f/1.00)", w1+w2+w3+w4+w5);
    scanf("%f", &w6);
    printf("\nETH (%f/1.00)", w1+w2+w3+w4+w5+w6);
    scanf("%f", &w7);

    if ((w1+w2+w3+w4+w5+w6+w7 > 1 + EPSILON)||(w1+w2+w3+w4+w5+w6+w7 < 1-EPSILON)) 
    {
        printf("Error, the sum of weights should be equals to 1. The entered weight is %f\n", w1+w2+w3+w4+w5+w6+w7);
        exit(1);
    }
    

    float o = sqrt(w1*w2*sigma(btc)*sigma(aga)*cov(btc, aga) + w1*w3*sigma(btc)*sigma(xrp)*cov(btc, xrp) + w1*w4*sigma(btc)*sigma(tron)*cov(btc, tron) +
    w1*w5*sigma(btc)*sigma(bnb)*cov(btc, bnb) + w1*w6*sigma(btc)*sigma(vet)*cov(btc, vet) + w1*w7*sigma(btc)*sigma(eth)*cov(btc, eth) +
    w1*w1*sigma(btc)*sigma(btc)*cov(btc, btc) + w2 * w1 * sigma(aga) * sigma(btc) * cov(aga, btc) +
    w2 * w3 * sigma(aga) * sigma(xrp) * cov(aga, xrp) +
    w2 * w4 * sigma(aga) * sigma(tron) * cov(aga, tron) +
    w2 * w5 * sigma(aga) * sigma(bnb) * cov(aga, bnb) +
    w2 * w6 * sigma(aga) * sigma(vet) * cov(aga, vet) +
    w2 * w7 * sigma(aga) * sigma(eth) * cov(aga, eth) +
    w2 * w2 * sigma(aga) * sigma(aga) * cov(aga, aga) + w3 * w1 * sigma(xrp) * sigma(btc) * cov(xrp, btc) +
    w3 * w2 * sigma(xrp) * sigma(aga) * cov(xrp, aga) +
    w3 * w4 * sigma(xrp) * sigma(tron) * cov(xrp, tron) +
    w3 * w5 * sigma(xrp) * sigma(bnb) * cov(xrp, bnb) +
    w3 * w6 * sigma(xrp) * sigma(vet) * cov(xrp, vet) +
    w3 * w7 * sigma(xrp) * sigma(eth) * cov(xrp, eth) +
    w3 * w3 * sigma(xrp) * sigma(xrp) * cov(xrp, xrp) + w4 * w1 * sigma(tron) * sigma(btc) * cov(tron, btc) +
    w4 * w2 * sigma(tron) * sigma(aga) * cov(tron, aga) +
    w4 * w3 * sigma(tron) * sigma(xrp) * cov(tron, xrp) +
    w4 * w5 * sigma(tron) * sigma(bnb) * cov(tron, bnb) +
    w4 * w6 * sigma(tron) * sigma(vet) * cov(tron, vet) +
    w4 * w7 * sigma(tron) * sigma(eth) * cov(tron, eth) +
    w4 * w4 * sigma(tron) * sigma(tron) * cov(tron, tron) + w5 * w1 * sigma(bnb) * sigma(btc) * cov(bnb, btc) +
    w5 * w2 * sigma(bnb) * sigma(aga) * cov(bnb, aga) +
    w5 * w3 * sigma(bnb) * sigma(xrp) * cov(bnb, xrp) +
    w5 * w4 * sigma(bnb) * sigma(tron) * cov(bnb, tron) +
    w5 * w6 * sigma(bnb) * sigma(vet) * cov(bnb, vet) +
    w5 * w7 * sigma(bnb) * sigma(eth) * cov(bnb, eth) +
    w5 * w5 * sigma(bnb) * sigma(bnb) * cov(bnb, bnb) +  w6 * w1 * sigma(vet) * sigma(btc) * cov(vet, btc) +
    w6 * w2 * sigma(vet) * sigma(aga) * cov(vet, aga) +
    w6 * w3 * sigma(vet) * sigma(xrp) * cov(vet, xrp) +
    w6 * w4 * sigma(vet) * sigma(tron) * cov(vet, tron) +
    w6 * w5 * sigma(vet) * sigma(bnb) * cov(vet, bnb) +
    w6 * w7 * sigma(vet) * sigma(eth) * cov(vet, eth) +
    w6 * w6 * sigma(vet) * sigma(vet) * cov(vet, vet) +  w7 * w1 * sigma(eth) * sigma(btc) * cov(eth, btc) +
    w7 * w2 * sigma(eth) * sigma(aga) * cov(eth, aga) +
    w7 * w3 * sigma(eth) * sigma(xrp) * cov(eth, xrp) +
    w7 * w4 * sigma(eth) * sigma(tron) * cov(eth, tron) +
    w7 * w5 * sigma(eth) * sigma(bnb) * cov(eth, bnb) +
    w7 * w6 * sigma(eth) * sigma(vet) * cov(eth, vet) +
    w7 * w7 * sigma(eth) * sigma(eth) * cov(eth, eth));

    printf("------------------------------------------------------------------------------------------\n");
    printf("|    BTC    |    AGA    |    XRP    |    TRON    |     BNB    |    VET     |     ETH     |\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("|    %.2f   |    %.2f   |    %.2f   |    %.2f    |     %.2f   |    %.2f    |     %.2f    |\n", w1, w2, w3, w4, w5, w6, w7);
    printf("------------------------------------------------------------------------------------------\n");
    printf("Portfolio risk is %f\n", o);
    printf("-------------------------\n");

}