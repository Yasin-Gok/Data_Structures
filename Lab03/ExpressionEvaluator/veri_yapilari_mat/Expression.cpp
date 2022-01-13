#include <string>							// Yasin Gök - 152120191048
#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

int oncelik_sirasi(char isaret) {
	if (isaret == '+' || isaret == '-') {			// oncelige gore farkli sayilar return etcez
		return 1;
	}
	else if (isaret == '/' || isaret == '*') {	
		return 2;								
	}
	else if (isaret == '^') {	
		return 3;
	}
	else {
		return -1;			
	}
}

//----------------------------------------------------------------------------------
// infix-notation halinde verilen ifadeyi post-fix yapar
//  
string Infix2Postfix(string &s) {
	string result;
	stack <char> postfix;
	stringstream ss(s);
	char ifade;

	while (ss >> ifade)
	{
		if (isdigit(ifade)) {	// eger sayiysa
			result += ifade;	// sonuca at
		}
		else if (ifade == '(') {	// parantezi stack'a at
			postfix.push('(');
		}
		else if (ifade == ')'){
			while (!postfix.empty() && postfix.top() != '(')	// bos degilse ve buna esit degilse
			{
				result += ' ';			// sonuca bosluk ekle
				result += postfix.top();	// en ust degeri al
				postfix.pop();			//	en ustu sil
			}
			postfix.pop();	
		}
		else{
			result += ' ';
			while (!postfix.empty() && oncelik_sirasi(ifade) <= oncelik_sirasi(postfix.top()))
			{
				result += postfix.top();	// en usttekini sonuca cek
				result += ' ';
				postfix.pop();		// sil
			}
			postfix.push(ifade);		// ifadeyi push et
		}
	}

	while (!postfix.empty())
	{
		result += ' ';
		result += postfix.top();	// ustteki degeri al ve sonuca at
		postfix.pop();				// sonra sil
	}
	return result;
}

//----------------------------------------------------------------------------------
//post-fix halinde verilen ifadeyi hesaplar
//
int EvaluatePostfixExpression(string& s) {
	stack <int> sonuc;
	stringstream ayrik_ifade(s);
	string mat;

	while (ayrik_ifade >> mat)
	{
		if (mat != "-" && mat != "+" && mat != "*" && mat != "/")
			sonuc.push(stoi(mat));	// eger operator degilse stacka push et sayiyi
		else{
			int sayi1 = sonuc.top();		// son 2 degeri al ve sil
			sonuc.pop();
			int sayi2 = sonuc.top();
			sonuc.pop();
			if (mat == "+")					// sonra da isarete gore islem yap
				sonuc.push(sayi1 + sayi2);
			else if (mat == "-")
				sonuc.push(sayi2 - sayi1);
			else if (mat == "*")
				sonuc.push(sayi2 * sayi1);
			else if (mat == "/")
				sonuc.push(sayi2 / sayi1);
		}
	}
	return sonuc.top();	// en son stacktadaki top degerini return et
}