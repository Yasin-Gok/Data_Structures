#include <stdio.h>
#include "PolyNode.h"
#include "Poly.h"
#include <iostream>

using namespace std;

void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test7();
void Test8();

int main() {
	
	Test1();
	printf("========================================================\n");
	cout << endl;
	Test2();
	printf("========================================================\n");
	cout << endl;
	Test3();
	printf("========================================================\n");
	cout << endl;
	Test4();
	printf("========================================================\n");
	cout << endl;
	Test5();
	printf("========================================================\n");
	cout << endl;
	Test6();
	printf("========================================================\n");
	cout << endl;
	Test7();
	printf("========================================================\n");
	cout << endl;
	Test8();
	
	return 0;
}

//-------------------------------------------------
// Bir polinomu güzel biçimlendirilmiþ bir þekilde yazdýrýr.
//
void Print(PolyNode* poly) {
	if (poly == NULL) { printf("<NULL>\n"); return; }

	printf("<");
	PolyNode* p = poly;
	while (p != NULL) {

		if (p->exp == 0) {
			printf("%+-3.1f", p->coef);
		}

		else if (p->exp == 1) {
			if (p->coef == 1.0) printf("+x ");
			else if (p->coef == -1.0) printf("-x ");
			else printf("%+-3.1fx ", p->coef);
		}

		else {
			if (p->coef == 1.0) printf("+x^%-2d ", p->exp);
			else if (p->coef == -1.0) printf("-x^%-2d ", p->exp);
			else printf("%+-3.1fx^%-2d ", p->coef, p->exp);
		} 

		p = p->next;
	} 
	printf(">\n");
} 	

// ---------------------------------------------------------
// Test1
// 
void Test1() {
	printf("%40s", "******TEST1****** Adding\n");

	PolyNode* poly = NULL;
	printf("Initial poly: "); Print(poly);

	poly = AddNode(poly, -2, 5);
	printf("Adding -2x^5: "); Print(poly);

	poly = AddNode(poly, 4.4, 7);
	printf("Adding 4.4x^7: "); Print(poly);

	poly = AddNode(poly, 2, 3);
	printf("Adding 2x^3: "); Print(poly);

	poly = AddNode(poly, 1, 4);
	printf("Adding x^4: "); Print(poly);

	poly = AddNode(poly, 4, 4);
	printf("Adding 4x^4: "); Print(poly);

	poly = AddNode(poly, 2, 5);
	printf("Adding 2x^5: "); Print(poly);

	poly = AddNode(poly, -4.4, 7);
	printf("Adding 4.4x^7: "); Print(poly);

	poly = AddNode(poly, -2, 3);
	printf("Adding -2x^3: "); Print(poly);

	poly = AddNode(poly, -5, 4);
	printf("Adding -5x^4: "); Print(poly);
}

//----------------------------------------------------------------
// Test2: Ýfadelerden birkaç polinom oluþturur.
//
void Test2() {
	printf("%40s", "******TEST2****** CreatingPoly\n");

	PolyNode *poly = CreatePoly((char *)"-x^3  -  6x^2 + 4x + 22");
	printf("[-x^3  -  6x^2 + 4x + 22]: "); Print(poly);
	DeletePoly(poly);

	poly = CreatePoly((char*)"-x^2 +x - 5");
	printf("[-x^2 +x  -  5]: "); Print(poly);
	DeletePoly(poly);

	poly = CreatePoly((char*)"2.3x^4 + 5x^3 - 2.6x - 4");
	printf("[2.3x^4 + 5x^3 - 2.6x - 4]: "); Print(poly);
	DeletePoly(poly);

	poly = CreatePoly((char*)"-4.5x^10 - 45.44");
	printf("[-4.5x^10 - 45.44]: "); Print(poly);
	DeletePoly(poly);

	poly = CreatePoly((char*)"x^6 + 24.6x^4 - x^3 - 61.3x^1 + 4.2");
	printf("[x^6 + 24.6x^4 - x^3 - 61.3x^1 + 4.2]: "); Print(poly);
	DeletePoly(poly);

	poly = CreatePoly((char*)" -x^34+x^20 -34.3x^5  +   x -  55");
	printf("[ -x^34+x^20 -34.3x^5  +   x -  55]: "); Print(poly);
	DeletePoly(poly);

	poly = CreatePoly((char*)"x^6 + 24.6x^4 - x^3 - 61.3x + 4.2");
	printf("[x^6 + 24.6x^4 - x^3 - 61.3x + 4.2]: "); Print(poly);
	DeletePoly(poly);

	poly = CreatePoly((char*)"-33");
	printf("[-33]: "); Print(poly);
	DeletePoly(poly);
} 

//----------------------------------------------------------------
// Ýki polinom oluþturur ve bunlarý toplar.
//
void Test3() {
	printf("%40s", "******TEST3******Addpoly\n");

	PolyNode *poly1 = CreatePoly((char*)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly1[-x^3-6x^2+4x+22]: "); Print(poly1);

	PolyNode *poly2 = CreatePoly((char*)"-x^2 +x  -  5");
	printf("%25s", "Poly2[-x^2+x-5]: "); Print(poly2);

	PolyNode *poly3 = Add(poly1, poly2);
	printf("--------------------------------------------------- +\n");
	printf("%25s", "Poly1+Poly2: "); Print(poly3);

	DeletePoly(poly1);
	DeletePoly(poly2);
	DeletePoly(poly3);
} 

//----------------------------------------------------------------
// Ýki polinom oluþturur ve birini diðerinden çýkarýr.
//
void Test4() {
	printf("%40s", "******TEST4****** Subtractingpoly\n");

	PolyNode *poly1 = CreatePoly((char*)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly1[-x^3-6x^2+4x+22]: "); Print(poly1);

	PolyNode *poly2 = CreatePoly((char *)"-x^2 +x  -  5");
	printf("%25s", "Poly2[-x^2+x-5]: "); Print(poly2);

	PolyNode *poly3 = Subtract(poly1, poly2);
	printf("------------------------------------------------------- -\n");
	printf("%25s", "Poly1-Poly2: "); Print(poly3);
} 

//----------------------------------------------------------------
// Ýki polinom oluþturur ve bunlarý çarpar.
//
void Test5() {
	printf("%40s", "******TEST5****** MultiplyPoly\n");

	PolyNode* poly1 = CreatePoly((char *)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly1[-x^3-6x^2+ 4x+22]: "); Print(poly1);

	PolyNode* poly2 = CreatePoly((char *)"-x^2 +x  -  5");
	printf("%25s", "Poly2[-x^2+x-5]: "); Print(poly2);

	PolyNode* poly3 = Multiply(poly1, poly2);
	printf("------------------------------------------------------- *\n");
	printf("%25s", "Poly1*Poly2: "); Print(poly3);
} 

//----------------------------------------------------------------
// Bir polinom oluþturur ve onun deðerini alýr.
//
void Test6() {
	printf("%40s", "******TEST6****** EvaluatePoly\n");

	PolyNode* poly = CreatePoly((char *)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly[-x^3-6x^2+ 4x+22]: "); Print(poly);
	printf("Evaluate(2): %4.2f\n", Evaluate(poly, 2.0));
} 

//----------------------------------------------------------------
// Bir polinomun türevini alýr.
//
void Test7() {
	printf("%40s", "******TEST7******DerivativePoly\n");

	PolyNode* poly = CreatePoly((char *)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly[-x^3-6x^2+ 4x+22]: "); Print(poly);

	PolyNode* deriv = Derivative(poly);
	printf("%25s", "Deriv[-x^3-6x^2+ 4x+22]: "); Print(deriv);
} 

//----------------------------------------------------------------
// Ekranda bir polinom çizer.
//
void Test8() {
	printf("%40s", "******TEST8****** PlotPoly\n");
	printf("%40s\n\n", "Plot of the function 0.004x^3+0.04x^2-1.5x-4.3");

	PolyNode* poly = CreatePoly((char *)"0.004x^3+0.04x^2-1.5x-4.3");
	Plot(poly, -30, 30);
} 