#include "WordFreq.h"						// Yasin Gök 152120191048												
#include <iostream>							
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;			// Verilen metin dosyasini isler ve en cok kullanilan "k" kelimelerini dondurur

bool sirali_mi(const pair <string, int>& x, const pair <string, int>& y) {
	return (x.second > y.second);
}

vector<WordFreq> GetMostFrequentKWords(string filename, int k) {
	vector <WordFreq> result;
	map <string, int> kelime_sayisi;			// kume icinde olusturuluyor
	string metin;
	ifstream dosya;
	dosya.open(filename);

	int i = 0;
	while (!dosya.eof()) {		// dosyanin sonuna gelene kadar
		dosya >> metin;
		metin.erase(remove(metin.begin(), metin.end(), ','), metin.end());			// algoritma kutuphanesi ile gelenler
		metin.erase(remove(metin.begin(), metin.end(), '.'), metin.end());			// eger varsa virgul ve noktayi siliyoruz

		if (metin.length() >= 2) {		
			if (kelime_sayisi.find(metin) == kelime_sayisi.end()) {			// kelime ilk kez okunmus ise
				kelime_sayisi[metin] = 1;
			}
			else {						// birden fazla olan durum eklenir
				kelime_sayisi[metin]++;
			}
		}
	}

	int boyut = kelime_sayisi.size();			// kelime sayisi fazla girilirse
	if (k > boyut) {
		cout << "Error: You can't enter more variables than the number of words!" << endl;
		cout << "You entered " << k << " numbers " << "but there are " << boyut << " different words!" << endl;
		exit(1);
	}
	else if (k < 1) {
		cout << "Error: You can't enter lower variables than 1!" << endl;
		exit(1);
	}

	vector <pair <string, int> > vektor;
	map <string, int> ::iterator iter;
	for (iter = kelime_sayisi.begin(); iter != kelime_sayisi.end(); iter++) {
		vektor.push_back(make_pair(iter->first, iter->second));				// Bunlari iterator ile cift yapiyoruz islem yapabilmek icin
	}																		// first kelime, second sayi
	sort(vektor.begin(), vektor.end(), sirali_mi);			// siraliyoruz

	map <string, int> ::iterator itr;
	for (int i = 0; i < k; i++) {
		result.push_back(vektor[i].first);			// once metni
		result[i].freq = vektor[i].second;			// sonra kullanim sayisini atýyo
	}
	return result;
}