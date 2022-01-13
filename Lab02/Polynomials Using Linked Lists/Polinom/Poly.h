#ifndef _POLY_H_
#define _POLY_H_

#include "PolyNode.h"											// Yapýlacak iþlemler tanýmlanýr

PolyNode* CreatePoly(char* expr);								// 1 Polinom oluþturma			
void DeletePoly(PolyNode* poly);								// 2 Silme

PolyNode* AddNode(PolyNode* head, double coef, int exp);		// 3 Node ekleme
PolyNode* Add(PolyNode* poly1, PolyNode* poly2);				// 4 Polinom toplama
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2);			// 5 Polinom çýkarma
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2);			// 6 Polinom çarpma

double Evaluate(PolyNode* poly, double x);						// 7 Polinom deðeri alma
PolyNode* Derivative(PolyNode *poly);							// 8 Polinom türevi alma

void Plot(PolyNode* poly, int x1, int x2);						// 9 Polinomu çizme
void Print(PolyNode* poly);										// 10 Polinomu yazdýrma

#endif