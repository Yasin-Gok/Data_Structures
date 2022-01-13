#ifndef _POLY_H_
#define _POLY_H_

#include "PolyNode.h"											// Yap�lacak i�lemler tan�mlan�r

PolyNode* CreatePoly(char* expr);								// 1 Polinom olu�turma			
void DeletePoly(PolyNode* poly);								// 2 Silme

PolyNode* AddNode(PolyNode* head, double coef, int exp);		// 3 Node ekleme
PolyNode* Add(PolyNode* poly1, PolyNode* poly2);				// 4 Polinom toplama
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2);			// 5 Polinom ��karma
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2);			// 6 Polinom �arpma

double Evaluate(PolyNode* poly, double x);						// 7 Polinom de�eri alma
PolyNode* Derivative(PolyNode *poly);							// 8 Polinom t�revi alma

void Plot(PolyNode* poly, int x1, int x2);						// 9 Polinomu �izme
void Print(PolyNode* poly);										// 10 Polinomu yazd�rma

#endif