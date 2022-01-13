#include "Deque.h"							// Yasin Gök 152120191048												
#include <iostream>							

using namespace std;

//------------------------------------------------------
// Varsayýlan yapýcý fonksiyon
// 
Deque::Deque() {			// head ve tail kýsmýný null yapýp sayýyý sýfýrlýyoruz
	this->head = NULL;
	this->tail = NULL;
	this->noOfItems = 0;
}

//------------------------------------------------------
// Yýkýcý Fonksiyon
// 
Deque::~Deque() {
	while (this->head) {
		DequeNode* node = this->head;		// node oluþturuyo
		this->head = this->head->next;		// head ilerliyo
		delete node;						// siliyo
	}
} 

//------------------------------------------------------
// Deque önüne yeni eleman ekleme
// 
void Deque::AddFront(int item) {
	DequeNode* new_node = new DequeNode(item);			// Girilen parametre ile bi node oluþturuluyor
	
	if (this->head == NULL) {			// Boþ mu kontrolü
		this->tail = this->head = new_node;	// Oluþturuyoruz
	}
	else {								// Deðilse ekliyoruz
		new_node->next = this->head;		// Yeni node next'i önceki head'i iþaret ediyo
		this->head->prev = new_node;		// Önceki head'in previous kýsmý yeni node'u iþaret ediyo
		this->head = new_node;				// Artýk yeni node, head oluyo
	}
	this->noOfItems += 1;				// En sonda da sayýyý arttýrýyoruz
}

//------------------------------------------------------
// Deque sonuna yeni eleman ekleme
// 
void Deque::AddRear(int item) {
	DequeNode* new_node = new DequeNode(item);

	if (this->tail == NULL) {			// Boþ mu kontrolü
		this->head = this->tail = new_node;	// Oluþturuyoruz
	}
	else {
		new_node->prev = this->tail;
		this->tail->next = new_node;
		this->tail = new_node;
	}
	this->noOfItems += 1;
} 

//------------------------------------------------------
// Öndeki elemaný alýp siler ve eðer deque boþ ise hata verir(throw an exception)
// 
int Deque::RemoveFront() {
	if (this->head == NULL) {
		throw exception("Error: You can't remove first element because deque is empty!");
	}
	
	int value;
	value = this->head->item;				// Deðeri geçici bir yere atýyoruz

	DequeNode* old_node = this->head;
	this->head = this->head->next;			// Head'i ilerletiyoruz

	if (this->head == NULL) {				// Eðer 1 düðüm var ise her þeyi null yapýyoruz
		this->tail = NULL;
	}
	else {
		this->head->prev = NULL;
	}

	delete old_node;						// En son düðüm siliniyor
	this->noOfItems -= 1;
	return value;
}

//------------------------------------------------------
// Sondaki elemaný alýp siler ve eðer deque boþ ise hata verir(throw an exception)
// 
int Deque::RemoveRear() {
	if (this->head == NULL) {
		throw exception("Error: You can't remove last element because deque is empty!");
	}

	int value;
	value = this->tail->item;

	DequeNode* old_node = this->tail;
	this->tail = this->tail->prev;			// Tail bir önceki düðüme iþaret ediyor artýk

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
// Öndeki elemaný silmeden alýr ve eðer deque boþ ise hata verir(throw an exception)
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
// Sondaki elemaný silmeden alýr ve eðer deque boþ ise hata verir(throw an exception)
// 
int Deque::Rear() {
	if (this->head == NULL) {
		throw exception("Error: Deque is empty!");
	}

	int last_value;
	last_value = this->tail->item;
	return last_value;
} 