#ifndef _POLYNODE_H_
#define _POLYNODE_H_

struct PolyNode {						// Her polinom d���m� bir katsay� ve bir �sten olu�ur.
	double coef;						// Katsay�
	int exp;							// �s
	struct PolyNode* next;				// Di�er polinom d���m�	Ba�lant�l� liste devam�
};

#endif