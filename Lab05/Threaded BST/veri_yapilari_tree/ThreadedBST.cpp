#include "ThreadedBST.h"					// Yasin Gök - 152120191048

//-----------------------------------------------
// Ağaçtaki tüm düğümleri siler.
// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {							// 1
	BSTNode* dugum = this->min();

	while (dugum != NULL) {
		BSTNode* x = this->next(dugum);			// Bir sonrakine gide gide null olmadıça devam
		delete dugum;
		dugum = x;
	}
} 

//-----------------------------------------------
// Verilen ifadeyi ağaca ekler.
// 
void ThreadedBST::add(int key) {						// 2
	if (root == NULL){							// Eğer ağaç boşşa yeni yap
		root = new BSTNode(key);
		root->left = root->right = NULL;
		return;
	}

	BSTNode* gecici_dugum = root;
	BSTNode* parent_dugum = NULL;

	while (gecici_dugum){
		parent_dugum = gecici_dugum;
		if (key == gecici_dugum->key) return;			// Eşitse döndür
		if (key > gecici_dugum->key){					// Büyükse sağa doğru git
			if (gecici_dugum->rightLinkType == CHILD) {
				gecici_dugum = gecici_dugum->right;
			}
			else {
				break;
			}
		}
		else{
			if (gecici_dugum->leftLinkType == CHILD) {	// Küçükse sola doğru git
				gecici_dugum = gecici_dugum->left;
			}
			else {
				break;
			}
		}
	}

	BSTNode* yeni_dugum = new BSTNode(key);			// Verilen ifade ile yeni düğüm yaptık
	yeni_dugum->leftLinkType = THREAD;
	yeni_dugum->rightLinkType = THREAD;

	if (key < parent_dugum->key){					// Küçükse sola doğru git
		yeni_dugum->left = parent_dugum->left;
		yeni_dugum->right = parent_dugum;
		parent_dugum->leftLinkType = CHILD;
		parent_dugum->left = yeni_dugum;
	}
	else{
		yeni_dugum->left = parent_dugum;
		yeni_dugum->right = parent_dugum->right;	// Büyükse sağa doğru git
		parent_dugum->rightLinkType = CHILD;
		parent_dugum->right = yeni_dugum;
	}
} 

//-----------------------------------------------
// Eğer varsa verilen ifadeyi ağaçtan kaldırır.
// 
void ThreadedBST::remove(int key) {						// 3
	BSTNode* parent_dugum = NULL, *child_dugum = root;

	while (child_dugum != NULL){			// Alt ağaç yani child yoksa
		if (key == child_dugum->key) {
			break;
		}

		parent_dugum = child_dugum;
		if (key < child_dugum->key){					// Eğer aranan küçükse ve sol tarafta child varsa , sola atama yaparak devam eder
			if (child_dugum->leftLinkType == CHILD) {
				child_dugum = child_dugum->left;
			}
			else {
				break;
			}
		}
		else{
			if (child_dugum->rightLinkType == CHILD) {	// Eğer aranan büyükse ve sağ tarafta child varsa , sağa atama yaparak devam eder
				child_dugum = child_dugum->right;
			}
			else {
				break;
			}
		}
	}

	BSTNode* dugum = child_dugum;

	if (child_dugum->rightLinkType == CHILD && child_dugum->leftLinkType == CHILD){			// 2 çocuk (child) 
		parent_dugum = child_dugum;
		dugum = child_dugum->left;
		while (dugum->rightLinkType == CHILD){		// Sağ bağlantıda child oldukça devam
			parent_dugum = dugum;
			dugum = dugum->right;
		}
		child_dugum->key = dugum->key;				// Bir önceki ile değeri değişir
	}

	BSTNode* max = NULL;
	BSTNode* min = NULL;

	if (parent_dugum->key >= dugum->key){			// Değerin büyük olma durumu
		if (dugum->rightLinkType == THREAD && dugum->leftLinkType == THREAD){		// 2 bağlantıda da child yoksa
			parent_dugum->left = dugum->left;
			parent_dugum->leftLinkType = THREAD;			// silmeden önce child yok diye tanım yapılıyor
		}
		else if (dugum->rightLinkType == THREAD){			// Devamlı sol kontrolü
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
			parent_dugum->right = dugum->right;				// Devamlı sağ kontrolü
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
// Verilen ifadeyi ağaçta arar.
// İfadeyi tutan düğüme bir işaretçi döndürür ve ifade bulunmazsa, NULL döndürür. 
// 
BSTNode *ThreadedBST::find(int key) {				// 4
	BSTNode* dugum = root;				// Kök düğüm

	while (dugum != NULL) {
		if (key == dugum->key) {
			return dugum;
		}
		else if (key < dugum->key) {		// Her seferinde sola giderek arar
			dugum = dugum->left;
		}
		else {								// Her seferinde sağa giderek arar
			dugum = dugum->right;
		}
	}
	return NULL;
} 

//-----------------------------------------------
// Ağaçtaki minimum ifadeyi döndürür.
// İfadeyi tutan düğüme bir işaretçi döndürür ve ifade bulunmazsa, NULL döndürür.
//
BSTNode* ThreadedBST::min() {				// 5
	if (root == NULL) {
		return NULL;
	}

	BSTNode* dugum = root;

	while (dugum->left != NULL) {			// Min solda olacağı için devamlı sola gider, en son veri olana kadar
		dugum = dugum->left;
	}
	return dugum;
} 

//-----------------------------------------------
// Ağaçtaki maximum ifadeyi döndürür.
// İfadeyi tutan düğüme bir işaretçi döndürür ve ifade bulunmazsa, NULL döndürür.
// 
BSTNode* ThreadedBST::max() {				// 6
	if (root == NULL) {
		return NULL;
	}

	BSTNode* dugum = root;

	while (dugum->right != NULL) {			// Max sağda olacağı için devamlı sağa gider, en son veri olana kadar
		dugum = dugum->right;
	}
	return dugum;
} 

//-----------------------------------------------
// Ağaçtaki bir düğüme geçerli bir işaretçi verildiğinde, inorder öncülünü içeren düğüme bir işaretçi döndürür. 
// Inorder öncülü yoksa, NULL döndürür.
// 
BSTNode* ThreadedBST::previous(BSTNode* node) {					// 7
	if (node == NULL) {
		return NULL;
	}

	if (node->leftLinkType == THREAD) {			// Bağlantı thread mi, önceki dediği için sol kontrolü
		return node->left;
	}
	else{
		node = node->left;
		while (node->rightLinkType == CHILD) {		// Bağlantı gerçekten bir alt ağaç yani çocuk olana kadar
			node = node->right;
		}
	}
	return node;
}

//-----------------------------------------------
// Ağaçtaki bir düğüme geçerli bir işaretçi verildiğinde, sıra ardılını içeren düğüme bir işaretçi döndürür. 
// Sıralama ardılı yoksa, NULL döndürür.
// 
BSTNode* ThreadedBST::next(BSTNode* node) {						// 8
	if (node == NULL) {
		return NULL;
	}

	if (node->rightLinkType == THREAD) {		// Bağlantı thread mi, sonraki dediği için sağ kontrolü
		return node->right;
	}
	else{
		node = node->right;
		while (node->leftLinkType == CHILD)
			node = node->left;
	}
	return node;
} 