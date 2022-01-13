#include "Deque.h"							// Yasin G�k 152120191048												
#include <iostream>							

using namespace std;

//------------------------------------------------------
// Varsay�lan yap�c� fonksiyon
// 
Deque::Deque() {			// head ve tail k�sm�n� null yap�p say�y� s�f�rl�yoruz
	this->head = NULL;
	this->tail = NULL;
	this->noOfItems = 0;
}

//------------------------------------------------------
// Y�k�c� Fonksiyon
// 
Deque::~Deque() {
	while (this->head) {
		DequeNode* node = this->head;		// node olu�turuyo
		this->head = this->head->next;		// head ilerliyo
		delete node;						// siliyo
	}
} 

//------------------------------------------------------
// Deque �n�ne yeni eleman ekleme
// 
void Deque::AddFront(int item) {
	DequeNode* new_node = new DequeNode(item);			// Girilen parametre ile bi node olu�turuluyor
	
	if (this->head == NULL) {			// Bo� mu kontrol�
		this->tail = this->head = new_node;	// Olu�turuyoruz
	}
	else {								// De�ilse ekliyoruz
		new_node->next = this->head;		// Yeni node next'i �nceki head'i i�aret ediyo
		this->head->prev = new_node;		// �nceki head'in previous k�sm� yeni node'u i�aret ediyo
		this->head = new_node;				// Art�k yeni node, head oluyo
	}
	this->noOfItems += 1;				// En sonda da say�y� artt�r�yoruz
}

//------------------------------------------------------
// Deque sonuna yeni eleman ekleme
// 
void Deque::AddRear(int item) {
	DequeNode* new_node = new DequeNode(item);

	if (this->tail == NULL) {			// Bo� mu kontrol�
		this->head = this->tail = new_node;	// Olu�turuyoruz
	}
	else {
		new_node->prev = this->tail;
		this->tail->next = new_node;
		this->tail = new_node;
	}
	this->noOfItems += 1;
} 

//------------------------------------------------------
// �ndeki eleman� al�p siler ve e�er deque bo� ise hata verir(throw an exception)
// 
int Deque::RemoveFront() {
	if (this->head == NULL) {
		throw exception("Error: You can't remove first element because deque is empty!");
	}
	
	int value;
	value = this->head->item;				// De�eri ge�ici bir yere at�yoruz

	DequeNode* old_node = this->head;
	this->head = this->head->next;			// Head'i ilerletiyoruz

	if (this->head == NULL) {				// E�er 1 d���m var ise her �eyi null yap�yoruz
		this->tail = NULL;
	}
	else {
		this->head->prev = NULL;
	}

	delete old_node;						// En son d���m siliniyor
	this->noOfItems -= 1;
	return value;
}

//------------------------------------------------------
// Sondaki eleman� al�p siler ve e�er deque bo� ise hata verir(throw an exception)
// 
int Deque::RemoveRear() {
	if (this->head == NULL) {
		throw exception("Error: You can't remove last element because deque is empty!");
	}

	int value;
	value = this->tail->item;

	DequeNode* old_node = this->tail;
	this->tail = this->tail->prev;			// Tail bir �nceki d���me i�aret ediyor art�k

	if (this->tail == NULL) {
		this->head = NULL;
	}
	else {
		this->tail->next = NULL;
	}

	delete old_node;					
	this->noOfItems -= 1;
	return value;
} 

//------------------------------------------------------
// �ndeki eleman� silmeden al�r ve e�er deque bo� ise hata verir(throw an exception)
// 
int Deque::Front() {
	if (this->head == NULL) {
		throw exception("Error: Deque is empty!");
	}

	int first_value;
	first_value = this->head->item;
	return first_value;
}

//------------------------------------------------------
// Sondaki eleman� silmeden al�r ve e�er deque bo� ise hata verir(throw an exception)
// 
int Deque::Rear() {
	if (this->head == NULL) {
		throw exception("Error: Deque is empty!");
	}

	int last_value;
	last_value = this->tail->item;
	return last_value;
} 