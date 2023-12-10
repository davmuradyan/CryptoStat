#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846
#define Enumb 2.71828182845904523536
#define EPSILON 0.0001

struct Node {
    float data;
    struct Node* next;
};
typedef struct Node Node;

//For creating linked lists
extern Node* createNode(float data);
extern void append(Node** head, float data);
extern void freeLinkedList(Node* head);
extern Node* readDataFromFile(const char* filename);

//Functions for statistics
extern float Ex(Node* list);
extern float cov(Node* list1, Node* list2);
extern float var(Node* list);
extern float corelation (Node* list1, Node* list2);
extern float sigma(Node* list);
extern double normInv(double prob, double mean, double stdev);
extern double riskValue(Node* list, double p, int periodInWeeks, double currentPrice);
extern void portfolioRisk(Node* btc, Node* aga, Node* xrp, Node* tron, Node* bnb, Node* vet, Node* eth);

// Linked lists of data
extern Node* BTC;
extern Node* AGA;
extern Node* BNB;
extern Node* ETH;
extern Node* TRON;
extern Node* VET;
extern Node* XRP;

#endif