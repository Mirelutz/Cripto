
#include <fstream>//lucreaza cu fluxuri (stream-uri)
#include <iostream>
using namespace std;
char* citeste_din_fisier(ifstream& in)
{
	char* mesaj = new char[100];
	char c;
	int i = 0;
	if (in.good())
	{
		cout << "Fisierul a fost deschis cu succes.\nContinutul acestuia este:\n\n";
			while (!in.eof()) // cat timp nu s-a ajuns la sfarsitul fisierului sursa
			{
				in >> noskipws >> c;
				mesaj[i] = c;
				i++;
			}
		mesaj[--i] = '\0';
	}
	else
		cout << "Eroare la deschiderea fisierului.";
	return mesaj;
}
void scrie_in_fisier(char* mesaj)
{//vom scrie caracter cu caracter
	ofstream out("destinatie.txt"); //deschidem fisierul pentru scriere
	//echivalent cu:
	//fstream out("destinatie.txt",ios::out);)
	//pentru a adauga text intr-un fisier:
	//fstream out("destinatie.txt",ios::app);
	int i = 0;
	while (mesaj[i] != '\0') // cat timp nu s-a ajuns la sfarsitul mesajului
	{
		out << mesaj[i];
		i++;
	}
	out.close();//inchidem fisierul
}
void cmmdcext(int a, int b) {
	int r, ca, cb, d, e = 1, r1, r2, r3, r4, r5, r6;
	//int v[1000][2];
	ca = a;cb = b;
	r1 = 1;r2 = 0;r4 = 0;r5 = 1;
	//v[0][0] = 1;v[0][1] = 0;v[1][0] = 0;v[1][1] = 1;
	while (b)
	{
		e++;
		d = a / b;
		r = a % b;
		r3 = r1 - d * r2;
		r6 = r4 - d * r5;
		//v[e][0] = v[e - 2][0] - d * v[e - 1][0];
		//v[e][1] = v[e - 2][1] - d * v[e - 1][1];
		a = b;
		b = r;
		r1 = r2;r2 = r3;
		r4 = r5;r5 = r6;
	}
	cout << a << "=" << r1 << "*" << ca << "+" << r4 << "*" << cb << endl;
}
int inv(int a, int b) {
	if (cmmdc(a, b) != 1) return 0;
	int r, ca, cb, d, e = 1, r1, r2, r3, r4, r5, r6;
	ca = a;cb = b;
	r1 = 1;r2 = 0;r4 = 0;r5 = 1;
	while (b)
	{
		e++;
		d = a / b;
		r = a % b;
		r3 = r1 - d * r2;
		r6 = r4 - d * r5;
		a = b;
		b = r;
		r1 = r2;r2 = r3;
		r4 = r5;r5 = r6;
	}
	return r1;
}
int cmmdc(int a, int b) {
	int r;

	while (b)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
int expmod(int a, int b, int c) {
	int p = 1;
	a = a % c;
	while (b > 0)
	{
		if (b % 2)
			p = (p * a) % c;
		a = (a * a) % c;
		b /= 2;
	}
	return p;
}
bool Fermat(int n, int nrinc) {
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	for (;nrinc > 0;nrinc--)
	{
		int b = rand();
		b = 2 + b % (n - 2);
		if (cmmdc(b, n) != 1) return 0;
		if (expmod(b, n - 1, n) != 1) return 0;
	}
	return 1;
}
bool Miller_Rabin(int n, int nr_incercari)
{
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	for (; nr_incercari > 0; nr_incercari--)
	{
		int s = 0, t = n - 1, b = rand();
		b = 2 + b % (n - 2);
		while (t % 2 == 0)
		{
			s++;
			t /= 2;
		}
		t = expmod(b, t, n);//in t pastram acum puterile b^t,b^(2t),...
		if (t != 1)
		{
			while ((t != n - 1) && (--s > 0))
			{//testam pentru nr de forma b^((2^r)*t) cu r din multimea
				//{1, 2, ..., s - 1}
				t = (t * t) % n;
				if (t == 1) return 0;
			}
			if (t != n - 1) return 0;
		}
	}
	return 1;
}
bool Miller_Rabin_determinist(int n, int nr_incercari)
{
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	int v[14] = { 2,3,5,7,11,13,17,19,23,29,31,37,41 };
	for (int i=0;i<13;i++)
	{
		int s = 0, t = n - 1, b = v[i];
		while (t % 2 == 0)
		{
			s++;
			t /= 2;
		}
		t = expmod(b, t, n);//in t pastram acum puterile b^t,b^(2t),...
		if (t != 1)
		{
			while ((t != n - 1) && (--s > 0))
			{//testam pentru nr de forma b^((2^r)*t) cu r din multimea
				//{1, 2, ..., s - 1}
				t = (t * t) % n;
				if (t == 1) return 0;
			}
			if (t != n - 1) return 0;
		}
	}
	return 1;
}
