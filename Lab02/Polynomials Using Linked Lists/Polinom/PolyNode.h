#ifndef _POLYNODE_H_
#define _POLYNODE_H_

struct PolyNode {						// Her polinom düðümü bir katsayý ve bir üsten oluþur.
	double coef;						// Katsayý
	int exp;							// Üs
	struct PolyNode* next;				// Diðer polinom düðümü	Baðlantýlý liste devamý
};

#endif