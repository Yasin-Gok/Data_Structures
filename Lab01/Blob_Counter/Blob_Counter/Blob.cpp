#include <iostream>							// Yasin G�k 152120191048
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#define satir 100
#define sutun 100

using namespace std;

void dosya_okuma(string dosya_ismi);
void yatay_sayi(int sutun_sayisi);
void dikey_sayi(int satir_sayisi);
void pikseller();
void tablo();

class BLOB {												// Piksel i�in bir s�n�f
public:
	string** dizi1;
	string satir2, sutun2;
	void dosya_okuma(string dosya_ismi);

	vector<pair<int, int>> piksel;				// Vekt�r �ifti olu�turduk
	bool siradaki_piksel = true;				// Bayrak de�i�keni gibi
	vector<vector<pair<int, int>>> piksel_dizisi;
	BLOB();													// Yap�c� (Constructor)
	~BLOB();												// Y�k�c� (Destructor)

	void yatay_sayi(int sutun_sayisi);			// Kenardaki say�lar i�in
	void dikey_sayi(int satir_sayisi);
	void pikseller();			// Tan�mlama
	void tablo();				// �izim
};

int main() {
	BLOB nesne1;			// Nesne olu�turduk
	string dosya_adi;
	cout << "Enter the filename: ";
	cin >> dosya_adi;
	cout << endl;

	if (dosya_adi != "blobs1.txt") {											// Hata mesaj�
		cout << "Dosya ismi hatali, sistemden cikiliyor..." << endl << endl;
		return -1;
		exit(-1);
	}

	nesne1.dosya_okuma(dosya_adi);			// Dosya okuma

	nesne1.yatay_sayi(stoi(nesne1.sutun2));			// Yatay rakamlar
	cout << endl;

	cout << setw(1) << "+";
	for (int x2 = 0; x2 < stoi(nesne1.sutun2); x2++) {
		cout << "-";
	}
	cout << "+";

	for (int i = 0; i < stoi(nesne1.satir2); i++) {					// Ekrana yazd�rma
		if (i > 0) {
			int sayi2 = i - 1;
			if (sayi2 == 10) {
				sayi2 = 0;
			}
			cout << sayi2;
			sayi2 += 1;
		}

		for (int j = 0; j < stoi(nesne1.sutun2) + 1; j++) {			// stringi inte �evirme
			cout << nesne1.dizi1[i][j];
			if (j == 0) {
				cout << "|";
			}
		}
		cout << "|";
	}
	cout << "9" << endl;

	cout << setw(1) << "+";
	for (int x2 = 0; x2 < stoi(nesne1.sutun2); x2++) {
		cout << "-";
	}
	cout << "+" << endl;

	nesne1.yatay_sayi(stoi(nesne1.sutun2));			// yatay rakamlar
	cout << endl << endl;

	nesne1.pikseller();			// Pikselleri b�nyeye al�yoruz
	nesne1.tablo();				// Tablo i�in

	system("pause");
	return 0;
}

BLOB::BLOB(){	// Yap�c�
	dizi1 = new string *[satir];					// Dizi1 i�in bellek ay�rd�k
	for (int i = 0; i < satir; i++) {
		dizi1[i] = new string[sutun];
	}
}

BLOB::~BLOB(){		// Y�k�c�
	for (int i = 0; i < satir; i++) {
		delete[] dizi1[i];			// Siliyoruz, bellek tasarrufu
	}
	delete[] dizi1;
}

void BLOB::dosya_okuma(string dosya_ismi) {				// Dosyadan okuma yapma
	char x1;
	fstream dosya;
	dosya.open(dosya_ismi, ios::in);	// Okuma izni
	dosya >> satir2 >> sutun2;			// �nputlar

	for (int i = 0; i < stoi(satir2); i++) {				// Yaz� say� �evirimi
		for (int j = 0; j <= stoi(sutun2); j++) {
			dosya.get(x1);
			dizi1[i][j] = x1;
		}
	}
	dosya.close();		// ��imiz bitti�i i�in kapat�yoruz
}

void BLOB::yatay_sayi(int sutun_sayisi) {
	int sayac1 = 0;
	cout << " ";
	for (int sayi1 = 0; sayi1 < 11; sayi1++) {
		if (sayi1 == 10) {
			sayi1 = 0;
		}
		cout << sayi1;
		sayac1 += 1;
		if (sayac1 == stoi(sutun2)) {
			break;
		}
	}
	cout << " ";
}

void BLOB::dikey_sayi(int satir_sayisi) {
	int sayac2 = 0;
	for (int sayi2 = 0; sayi2 < 11; sayi2++) {
		if (sayi2 == 10) {
			sayi2 = 0;
		}
		cout << sayi2 << endl;
		sayac2 += 1;
		if (sayac2 == stoi(satir2)) {
			break;
		}
	}
}

void BLOB::pikseller(){						// Pikselleri b�nyeye al�yoruz
	vector<pair<int, int>> x3;
	pair<int, int> pixel;

	for (int i = 0; i < stoi(satir2); i++) {
		for (int j = 0; j <= stoi(sutun2); j++) {
			if (dizi1[i][j] == "x") {
				for (int k = i; k < stoi(sutun2); k++) {

					if (dizi1[k][j] == "x") {
						pixel.first = k;
						pixel.second = j - 1;
						piksel.push_back(pixel);			// Sondan ekleme i�lemi yapar
						dizi1[k][j] = "w";
					}
					else {
						break;
					}
				}

				if (j != 0) {
					if (dizi1[i][j - 1] != "w" && dizi1[i][j + 1] != "w") siradaki_piksel = true;			// Di�er piksel i�in do�ruluk kontrol�
				}
				else {
					siradaki_piksel = true;
				}

				if (siradaki_piksel) {
					piksel_dizisi.push_back(piksel);
					piksel.clear();		// Temizleme
				}
				else {
					for (int x4 = 0; x4 < piksel.size(); x4++) {
						piksel_dizisi[piksel_dizisi.size() - 1].push_back(piksel[x4]);
					}
					piksel.clear();					// Temizledik
				}
				siradaki_piksel = false;	// Bitiriyoruz
			}
		}
	}
}

void BLOB::tablo(){
	vector<pair<float, float>> satir_km;	//km -> k�tle merkezi

	for (int i = 0; i < piksel_dizisi.size(); i++) {
		float satir3 = 0, sutun3 = 0;
		for (int j = 0; j < piksel_dizisi[i].size(); j++) {
			satir3 += piksel_dizisi[i][j].first;
			sutun3 += piksel_dizisi[i][j].second;
		}

		satir3 = satir3 / piksel_dizisi[i].size();
		sutun3 = sutun3 / piksel_dizisi[i].size();
		pair<float, float> sutun_km;
		sutun_km.first = satir3;
		sutun_km.second = sutun3;
		satir_km.push_back(sutun_km);
	}

	for (int i = 0; i < 45; i++) {									// Tablo yaz�m�
		if (i == 0 || i == 7 || i == 20 || i == 30 || i == 44) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	cout << endl;

	cout << setw(7) << "| BLOB " << setw(13) << "| NoOfPixels " << setw(10) << "| CoM Row " << setw(15) << "| CoM Column |" << endl;

	for (int i = 0; i < 45; i++) {
		if (i == 0 || i == 7 || i == 20 || i == 30 || i == 44) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}

	cout << endl;

	for (int i = 0; i < piksel_dizisi.size(); i++) {
		cout << fixed << setprecision(2);		// Ondal�k k�s�m hassasiyeti
		cout << setw(6) << left << "|" << right << i + 1 << "|" << setw(12) << right << piksel_dizisi[i].size() << "|"
			<< setw(9) << right << satir_km[i].first << "|" << setw(13) << right << satir_km[i].second << "|" << endl;
	}

	for (int i = 0; i < 45; i++) {

		if (i == 0 || i == 7 || i == 20 || i == 30 || i == 44) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	cout << endl;
}