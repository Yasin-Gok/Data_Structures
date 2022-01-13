#include <stdio.h>							// Yasin Gök 152120191048
#include <iostream>															
#include "Poly.h"
#include <string>
#include <iomanip>  
#include <conio.h>
#include <cstdlib>
#include <cctype>
#include <algorithm>

using namespace std;

#define MAX_DEGER 100	// Max polinom derecesi

void remove(PolyNode**, int);

string bosluk_silme(string str) {				// Boþluk silme
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

//-------------------------------------------------
// Bir ifadeden bir polinom oluþturur. 
// Listedeki ilk PolyNode'a (listenin baþý) bir pointer döndürür.
//
// Ýfade aþaðýdaki türden olacaktýr:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode *CreatePoly(char *expr){
	string str(expr);
	str = bosluk_silme(str);
	int exprSize = str.size();
	
	int k = 1;
	for (int i = 1; i < exprSize; ++i) {	// iþaret ayarý
		if (str[i] == '+' || str[i] == '-') {
			k++;
		}
	}
	int isaret_sayaci = k;

	if (isdigit(str[0])) str.insert(0, "+");	
	if (str[0] == 'x') str.insert(0, "+");
	str.append("+");
	exprSize = str.size();

	k = 0;
	int j = 0;
	string artiEksiStr[MAX_DEGER];		// diziye ekleniyo
	for (int i = 1; i < exprSize; ++i) {
		if (str[i] == '+' || str[i] == '-') {
			artiEksiStr[k++] = str.substr(j, i - j);
			j = i;
		}
	}

	for (int i = 0; i < isaret_sayaci; ++i)	{		// Terimlere göre yazým
		if (artiEksiStr[i][1] == 'x') {	
			artiEksiStr[i].insert(1, "1");	
		}

		bool flag = false;	// x'in olmama durumu
		int len = artiEksiStr[i].size();

		for (int j = 1; j < len; ++j) {
			if (artiEksiStr[i][j] == 'x') {// x'in kontrolü
				flag = true;	
				if (j == len - 1) {	
					artiEksiStr[i].append("^1");	
				}
				break;
			}
		}

		if (!flag)	// sabit terim
			artiEksiStr[i].append("x^0");
	}

	// Terimleri ayarlama
	int us[MAX_DEGER] = { 0 };
	double katsayi[MAX_DEGER] = { 0 };

	for (int i = 0; i < isaret_sayaci; ++i){
		int artiEksiSize = artiEksiStr[i].size();
		for (int j = 0; j < artiEksiSize; ++j){
			if (artiEksiStr[i][j] == '^'){
				us[i] = stoi(artiEksiStr[i].substr(j + 1, artiEksiSize - j));
				katsayi[i] = stod(artiEksiStr[i].substr(0, j));
				break;
			}
		}
	}
		
	int maxUs = 0;
	for (int k : us) {
		if (k >= maxUs) {
			maxUs = k;
		}
	}

	string newArtiEksi[MAX_DEGER];
	for (int i = maxUs; i >= 0; i--) {
		newArtiEksi[i] = "+0x^" + to_string(i);
	}

	// 2 polinomun karýþmasý
	for (int i = isaret_sayaci; i >= 0; i--) {
		newArtiEksi[us[i]] = artiEksiStr[i];
	}

	std::string finalStr;
	for (int i = maxUs; i >= 0; i--)
		finalStr += newArtiEksi[i];
	
	int finalSize = finalStr.size();	// Terimleri çýkarýyoruz, SON
	int baslangic[MAX_DEGER] = { 0 };
	int bitis[MAX_DEGER] = { 0 };
	k = 0;

	for (int i = 0; i < finalSize; ++i) {
		if (finalStr.substr(i, 1) == "+" || finalStr.substr(i, 1) == "-") {
			baslangic[k] = i;
		}
		if (finalStr.substr(i, 1) == "x") {
			bitis[k++] = i;
		}
	}

	for (int i = 0; i < k; ++i) {
		katsayi[i] = stod(finalStr.substr(baslangic[i], bitis[i] - baslangic[i]));
		us[i] = maxUs - i;
	}

	int yeni_us[MAX_DEGER];		// Add node iþlemi
	double yeni_katsayi[MAX_DEGER];
	int z = 0;
	for (int i = 0; i < MAX_DEGER; i++) {
		if (katsayi[i] != 0) {
			yeni_us[z] = us[i];
			yeni_katsayi[z] = katsayi[i]; 
			z++;
		}
	}

	PolyNode* head = NULL;
	for (int i = 0; i < z; i++) {
		head = AddNode(head, yeni_katsayi[i], yeni_us[i]);
	}
	return head;
} 

// -------------------------------------------------
// Çoklu düðümlerin üzerinde yürüyün ve silin.
//
void DeletePoly(PolyNode* poly) {
	if (poly && poly->next){
		PolyNode* p, *q;
		p = poly;
		while (p){
			q = p->next;
			free(p);
			p = q;
		}
	}
	poly = NULL;
} 
	
//-------------------------------------------------
// Polinoma bir düðüm (katsayý, üs) ekler. Ayný üslü bir düðüm zaten varsa, o zaman katsayýyý mevcut katsayýya eklemeniz yeterlidir.
// Deðilse, polinoma yeni bir düðüm eklersiniz.
// Polinomun olasý yeni baþlýðýna bir pointer döndürür.
//
PolyNode* AddNode(PolyNode *head, double coef, int exp){
	PolyNode* poly = new PolyNode();
	poly->coef = coef; poly->exp = exp;
	poly->next = NULL;

	PolyNode* q = NULL;
	PolyNode* p = head;
	while (p != NULL && exp <= p->exp){
		if (exp == p->exp){
			p->coef += coef;
		}
		q = p;
		p = p->next;
	}

	if (q == NULL){
		poly->next = head;
		head = poly;
	}

	else if (exp != q->exp){
		poly->next = q->next;
		q->next = poly;
	}
	remove(&head, 0);
	return head;
} 

void remove(PolyNode** head, int num){
	PolyNode* temp = *head;
	PolyNode* prev = NULL;
	if (temp != NULL && temp->coef == num){
		*head = temp->next;
		delete temp;
		return;
	}

	while (temp != NULL && temp->coef != num){
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL){
		return;
	}
	prev->next = temp->next;
	delete temp;
}

//-------------------------------------------------
// Ýki polinom ekler ve sonucu içeren yeni bir polinom döndürür.
// Hesaplar: poly3 = poly1 + poly2 ve poly3'ü return eder
//
PolyNode *Add(PolyNode *poly1, PolyNode *poly2){
	PolyNode* poly3 = NULL;
	while (poly1 && poly2){
		if (poly1->exp > poly2->exp){
			poly3 = AddNode(poly3, poly1->coef, poly1->exp);
			poly1 = poly1->next;
		}

		else if (poly1->exp < poly2->exp){
			poly3 = AddNode(poly3, poly2->coef, poly2->exp);
			poly2 = poly2->next;
		}

		else{
			poly3 = AddNode(poly3, poly1->coef + poly2->coef, poly1->exp);
			poly1 = poly1->next;
			poly2 = poly2->next;
		}
	}

	while (poly1 || poly2){
		if (poly1->next) {
			poly3 = AddNode(poly3, poly1->coef, poly1->exp);
			poly1 = poly1->next;
		}

		if (poly2->next){
			poly3 = AddNode(poly3, poly2->coef, poly2->exp);
			poly2 = poly2->next;
		}
	}
	return poly3;
} 

//-------------------------------------------------
// Polinom 2'yi polinom 1'den çýkarýr ve elde edilen polinomu döndürür.
// Hesaplar: poly3 = poly1 - poly2 ve poly3'ü return eder
//
PolyNode *Subtract(PolyNode *poly1, PolyNode *poly2){
	PolyNode* poly3 = NULL;
	while (poly1 && poly2){
		if (poly1->exp > poly2->exp){
			poly3 = AddNode(poly3, poly1->coef, poly1->exp);
			poly1 = poly1->next;
		}

		else if (poly1->exp < poly2->exp){
			poly3 = AddNode(poly3, poly2->coef, poly2->exp);
			poly2 = poly2->next;
		}

		else{
			poly3 = AddNode(poly3, poly1->coef - poly2->coef, poly1->exp);
			poly1 = poly1->next;
			poly2 = poly2->next;
		}
	}

	while (poly1 || poly2){
		if (poly1->next){
			poly3 = AddNode(poly3, poly1->coef, poly1->exp);
			poly1 = poly1->next;
		}

		if (poly2->next){
			poly3 = AddNode(poly3, poly2->coef, poly2->exp);
			poly2 = poly2->next;
		}
	}
	return poly3;
} 

//-------------------------------------------------
// Polinom 1 ve polinom 2'yi çarpar ve elde edilen polinomu döndürür.
// Hesaplar: poly3 = poly1 * poly2 ve poly3'ü return eder
//
PolyNode *Multiply(PolyNode *poly1, PolyNode *poly2){
	PolyNode* poly3 = NULL;
	PolyNode* temp_poly1, *temp_poly2;
	temp_poly1 = poly1;
	temp_poly2 = poly2;

	while (temp_poly1 != NULL) {
		while (temp_poly2 != NULL) {
			int coeff, power;
			coeff = temp_poly1->coef * temp_poly2->coef;
			power = temp_poly1->exp + temp_poly2->exp;
			poly3 = AddNode(poly3, coeff, power);
			temp_poly2 = temp_poly2->next;
		}
		temp_poly2 = poly2;
		temp_poly1 = temp_poly1->next;
	}
	return poly3;
} 

//-------------------------------------------------
// Polinomu belirli bir "x" deðerinde deðerlendirir ve sonucu döndürür.
//
double Evaluate(PolyNode *poly, double x){
	PolyNode* tmp = poly;
	double sonuc = 0;
	while (tmp != NULL){
		sonuc += tmp->coef * pow(x, tmp->exp);
		tmp = tmp->next;
	}
	return sonuc;
} 

//-------------------------------------------------
// Polinomun türevini hesaplar ve döndürür.
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode *Derivative(PolyNode *poly){
	PolyNode* head = poly;
	PolyNode* result = NULL;

	while (head != NULL){
		head->coef = head->coef * head->exp;
		head->exp = head->exp - 1;
		result = AddNode(result, head->coef, head->exp);
		head = head->next;
	}
	return result;
} 

//-------------------------------------------------
// [x1, x2] aralýðýnda polinomu çizer.
// -39<=x1<x2<=39
// -12<=y<=12
// Ekranýn ortasýnda x & y ekseni çizilmiþ olmalý
// Deðerlendirme sýrasýnda "y" deðeri ekrana sýðmýyorsa atlayýnýz. 
// Aksi takdirde, eðriyi gösteren bir '*' karakteri koyun.
//
void Plot(PolyNode *poly, int x1, int x2){
	char command_line[25][80];

	if (-39 <= x1 && x2 <= 39){
		for (int i = 24; i >= 0; i--){
			for (int j = 0; j <= 78; j++){

				if (round(Evaluate(poly, j - 39)) == i - 12){
					command_line[i][j] = '*';
				}
				else{
					command_line[i][j] = ' ';
				}

				if (j == 39){
					command_line[i][j] = '|';
					if (i % 5 == 2){
						command_line[i][j] = '+';
					}
				}

				if (i == 12){
					command_line[i][j] = '-';
					if (j % 5 == 4){
						command_line[i][j] = '+';
					}
				}
				cout << command_line[i][j];
			}
			cout << endl;
		}
	}
	else{
		cout << "Error: Variables index out of range!" << endl << endl;
	}
} 