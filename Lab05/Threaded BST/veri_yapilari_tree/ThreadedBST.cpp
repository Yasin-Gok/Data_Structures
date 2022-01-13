#include "ThreadedBST.h"					// Yasin G�k - 152120191048

//-----------------------------------------------
// A�a�taki t�m d���mleri siler.
// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {							// 1
	BSTNode* dugum = this->min();

	while (dugum != NULL) {
		BSTNode* x = this->next(dugum);			// Bir sonrakine gide gide null olmad��a devam
		delete dugum;
		dugum = x;
	}
} 

//-----------------------------------------------
// Verilen ifadeyi a�aca ekler.
// 
void ThreadedBST::add(int key) {						// 2
	if (root == NULL){							// E�er a�a� bo��a yeni yap
		root = new BSTNode(key);
		root->left = root->right = NULL;
		return;
	}

	BSTNode* gecici_dugum = root;
	BSTNode* parent_dugum = NULL;

	while (gecici_dugum){
		parent_dugum = gecici_dugum;
		if (key == gecici_dugum->key) return;			// E�itse d�nd�r
		if (key > gecici_dugum->key){					// B�y�kse sa�a do�ru git
			if (gecici_dugum->rightLinkType == CHILD) {
				gecici_dugum = gecici_dugum->right;
			}
			else {
				break;
			}
		}
		else{
			if (gecici_dugum->leftLinkType == CHILD) {	// K���kse sola do�ru git
				gecici_dugum = gecici_dugum->left;
			}
			else {
				break;
			}
		}
	}

	BSTNode* yeni_dugum = new BSTNode(key);			// Verilen ifade ile yeni d���m yapt�k
	yeni_dugum->leftLinkType = THREAD;
	yeni_dugum->rightLinkType = THREAD;

	if (key < parent_dugum->key){					// K���kse sola do�ru git
		yeni_dugum->left = parent_dugum->left;
		yeni_dugum->right = parent_dugum;
		parent_dugum->leftLinkType = CHILD;
		parent_dugum->left = yeni_dugum;
	}
	else{
		yeni_dugum->left = parent_dugum;
		yeni_dugum->right = parent_dugum->right;	// B�y�kse sa�a do�ru git
		parent_dugum->rightLinkType = CHILD;
		parent_dugum->right = yeni_dugum;
	}
} 

//-----------------------------------------------
// E�er varsa verilen ifadeyi a�a�tan kald�r�r.
// 
void ThreadedBST::remove(int key) {						// 3
	BSTNode* parent_dugum = NULL, *child_dugum = root;

	while (child_dugum != NULL){			// Alt a�a� yani child yoksa
		if (key == child_dugum->key) {
			break;
		}

		parent_dugum = child_dugum;
		if (key < child_dugum->key){					// E�er aranan k���kse ve sol tarafta child varsa , sola atama yaparak devam eder
			if (child_dugum->leftLinkType == CHILD) {
				child_dugum = child_dugum->left;
			}
			else {
				break;
			}
		}
		else{
			if (child_dugum->rightLinkType == CHILD) {	// E�er aranan b�y�kse ve sa� tarafta child varsa , sa�a atama yaparak devam eder
				child_dugum = child_dugum->right;
			}
			else {
				break;
			}
		}
	}

	BSTNode* dugum = child_dugum;

	if (child_dugum->rightLinkType == CHILD && child_dugum->leftLinkType == CHILD){			// 2 �ocuk (child) 
		parent_dugum = child_dugum;
		dugum = child_dugum->left;
		while (dugum->rightLinkType == CHILD){		// Sa� ba�lant�da child olduk�a devam
			parent_dugum = dugum;
			dugum = dugum->right;
		}
		child_dugum->key = dugum->key;				// Bir �nceki ile de�eri de�i�ir
	}

	BSTNode* max = NULL;
	BSTNode* min = NULL;

	if (parent_dugum->key >= dugum->key){			// De�erin b�y�k olma durumu
		if (dugum->rightLinkType == THREAD && dugum->leftLinkType == THREAD){		// 2 ba�lant�da da child yoksa
			parent_dugum->left = dugum->left;
			parent_dugum->leftLinkType = THREAD;			// silmeden �nce child yok diye tan�m yap�l�yor
		}
		else if (dugum->rightLinkType == THREAD){			// Devaml� sol kontrol�
			max = dugum->left;
			while (max->rightLinkType == CHILD){
				max = max->right;
			}
			max->right = parent_dugum;
			parent_dugum->left = dugum->left;
		}
		else{
			min = dugum->right;
			while (min->leftLinkType == CHILD){
				min = min->left;
			}
			min->left = dugum->left;
			parent_dugum->left = dugum->right;
		}
		delete dugum;
	}
	else{
		if (dugum->rightLinkType == THREAD && dugum->leftLinkType == THREAD){
			parent_dugum->right = dugum->right;				// Devaml� sa� kontrol�
			parent_dugum->rightLinkType = THREAD;
		}
		else if (dugum->rightLinkType == THREAD){
			max = dugum->left;
			while (max->rightLinkType == CHILD){
				max = max->right;
			}
			max->right = dugum->right;
			parent_dugum->right = dugum->left;
		}
		else{
			min = dugum->right;
			while (min->leftLinkType == CHILD){
				min = min->left;
			}
			min->left = parent_dugum;
			parent_dugum->right = dugum->right;
		}
		delete dugum;
	}
}

//-----------------------------------------------
// Verilen ifadeyi a�a�ta arar.
// �fadeyi tutan d���me bir i�aret�i d�nd�r�r ve ifade bulunmazsa, NULL d�nd�r�r. 
// 
BSTNode *ThreadedBST::find(int key) {				// 4
	BSTNode* dugum = root;				// K�k d���m

	while (dugum != NULL) {
		if (key == dugum->key) {
			return dugum;
		}
		else if (key < dugum->key) {		// Her seferinde sola giderek arar
			dugum = dugum->left;
		}
		else {								// Her seferinde sa�a giderek arar
			dugum = dugum->right;
		}
	}
	return NULL;
} 

//-----------------------------------------------
// A�a�taki minimum ifadeyi d�nd�r�r.
// �fadeyi tutan d���me bir i�aret�i d�nd�r�r ve ifade bulunmazsa, NULL d�nd�r�r.
//
BSTNode* ThreadedBST::min() {				// 5
	if (root == NULL) {
		return NULL;
	}

	BSTNode* dugum = root;

	while (dugum->left != NULL) {			// Min solda olaca�� i�in devaml� sola gider, en son veri olana kadar
		dugum = dugum->left;
	}
	return dugum;
} 

//-----------------------------------------------
// A�a�taki maximum ifadeyi d�nd�r�r.
// �fadeyi tutan d���me bir i�aret�i d�nd�r�r ve ifade bulunmazsa, NULL d�nd�r�r.
// 
BSTNode* ThreadedBST::max() {				// 6
	if (root == NULL) {
		return NULL;
	}

	BSTNode* dugum = root;

	while (dugum->right != NULL) {			// Max sa�da olaca�� i�in devaml� sa�a gider, en son veri olana kadar
		dugum = dugum->right;
	}
	return dugum;
} 

//-----------------------------------------------
// A�a�taki bir d���me ge�erli bir i�aret�i verildi�inde, inorder �nc�l�n� i�eren d���me bir i�aret�i d�nd�r�r. 
// Inorder �nc�l� yoksa, NULL d�nd�r�r.
// 
BSTNode* ThreadedBST::previous(BSTNode* node) {					// 7
	if (node == NULL) {
		return NULL;
	}

	if (node->leftLinkType == THREAD) {			// Ba�lant� thread mi, �nceki dedi�i i�in sol kontrol�
		return node->left;
	}
	else{
		node = node->left;
		while (node->rightLinkType == CHILD) {		// Ba�lant� ger�ekten bir alt a�a� yani �ocuk olana kadar
			node = node->right;
		}
	}
	return node;
}

//-----------------------------------------------
// A�a�taki bir d���me ge�erli bir i�aret�i verildi�inde, s�ra ard�l�n� i�eren d���me bir i�aret�i d�nd�r�r. 
// S�ralama ard�l� yoksa, NULL d�nd�r�r.
// 
BSTNode* ThreadedBST::next(BSTNode* node) {						// 8
	if (node == NULL) {
		return NULL;
	}

	if (node->rightLinkType == THREAD) {		// Ba�lant� thread mi, sonraki dedi�i i�in sa� kontrol�
		return node->right;
	}
	else{
		node = node->right;
		while (node->leftLinkType == CHILD)
			node = node->left;
	}
	return node;
} 