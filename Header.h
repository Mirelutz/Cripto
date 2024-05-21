#pragma once
#include <fstream>//lucreaza cu fluxuri (stream-uri)
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
bool prim(int n) {
	if (n == 1) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	for (int i = 3; i <= sqrt((double)n); i += 2)
		if (n % i == 0) return 0;
	return 1;
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
unsigned long long cmmdc(unsigned long long a, unsigned long long b) {
	unsigned long long r;

	while (b)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
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
unsigned long long expmod(unsigned long long a, unsigned long long b, unsigned long long c) {
	unsigned long long p = 1;
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
bool Fermat(unsigned long long n, int nrinc) {
	if (n == 2) return 1;
	if ((n % 2 == 0)||(n%3==0)||(n%10==5)) return 0;
	for (;nrinc > 0;nrinc--)
	{
		unsigned long long b = rand();
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
		unsigned long long s = 0, t = n - 1, b = rand();
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
bool Miller_Rabin_determinist(unsigned long long n)
{
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	int v[14] = { 2,3,5,7,11,13,17,19,23,29,31,37,41 };
	for (int i = 0;i < 13;i++)
	{
		unsigned long long s = 0, t = n - 1, b = v[i];
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
struct bloc
{
	char c;
	int nr;
};
bloc character[100] = { 0 };
int N = 0;
int da_cod(char c)
{
	for (int i = 0; i < N; i++)
		if (character[i].c == c)
			return i;
	return -1;
}

char da_caracter(int cod)
{
	return character[cod % N].c;
}
void citeste_alfabet(ifstream& in)
{
	if (!in.good())
		perror("Fisier inexistent");
	char c;
	while (in >> noskipws >> c)
	{
		character[N].c = c;
		N++;
	}
	if (N == 0)
		cout << "Alfabetul dat are 0 caractere" << endl;
}
bloc* ordonareFrecvente()
{
	bloc* result = new bloc[N];
	int ordonat = 0;
	for (int i = 0; i < N; i++)
		result[i] = character[i];
	while (!ordonat)
	{
		ordonat = 1;
		for (int i = 0; i < N - 1; i++)
		{
			if (result[i].nr < result[i + 1].nr)
			{
				ordonat = 0;
				bloc temp = result[i];
				result[i] = result[i + 1];
				result[i + 1] = temp;
			}
		}
	}
	return result;
}
void frecv(ifstream& fin)
{
	if (!fin.good())
		perror("Fisier inexistent");
	char c;
	while (fin >> noskipws >> c)
	{
		int cod = da_cod(c);
		if (cod >= 0 && cod < N)
			character[cod].nr++;
	}
}
void frecv2(ifstream& fin, vector<int>& character_pairs, int N) {
	if (!fin.good()) {
		perror("Fisier inexistent");
		return;
	}

	char c, prev = '\0'; // prev va reține caracterul anterior
	while (fin >> noskipws >> c) {
		if (prev != '\0') { // Verificăm dacă avem un caracter anterior
			int pair_index = da_cod(prev) * N + da_cod(c); // Calculăm un index unic pentru fiecare pereche de caractere
			if (pair_index >= 0 && pair_index < N * N) { // Verificăm dacă indexul este valid
				character_pairs[pair_index]++; // Incrementăm frecvența grupului de caractere
			}
		}
		prev = c; // Actualizăm caracterul anterior pentru următoarea iterație
	}
}
struct cheieAfina {
	int n;//dimensiunea matricilor de criptare
	int** a;
	int* b;
};
int modulo(int k, int n) {//extindem operatorul modulo (%) si pentru numere negative
	if (k >= n)
		return k % n;
	else
		if (k < 0)
			return n - (-k) % n;
	return k;
}
void criptareCezar(ifstream& in, ofstream& out, int k)
{
	char m;
	while (in >> noskipws >> m)
	{
		out << da_caracter(da_cod(m) + k);
	}
}

void criptareAfina(ifstream& in, ofstream& out, int a, int b)
{
	char m;
	while (in >> noskipws >> m)
	{
		out << da_caracter(da_cod(m) * a + b);
	}
}
int** calcul_minor(int** matrice, int lin, int col, int n) {
	int i, j, ** a = new int* [n - 1];
	for (i = 0; i < n - 1; i++) {
		a[i] = new int[n - 1];
	}
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - 1; j++)
			if (i < lin) {
				if (j < col)
					a[i][j] = matrice[i][j];
				else
					a[i][j] = matrice[i][j + 1];
			}
			else {
				if (j < col)
					a[i][j] = matrice[i + 1][j];
				else
					a[i][j] = matrice[i + 1][j + 1];
			}
	return a;
}

int calcul_det(int** matrice, int n) {
	if (n <= 1) return matrice[0][0];
	int S = 0;
	for (int i = 0; i < n; i++)
		S += matrice[0][i] * (i % 2 ? -1 : 1) * calcul_det(calcul_minor(matrice, 0, i, n), n - 1);
	return S;
}

int** calcul_matr_inv_Zn(int** a, int n, int Zn) {
	int i, j, ** rez;
	rez = new int* [n];
	for (i = 0; i < n; i++)
		rez[i] = new int[n];

	int inv_determinant = inv(calcul_det(a, n), Zn);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			rez[i][j] = modulo(inv_determinant * ((i + j) % 2 ? -1 : 1) * calcul_det(calcul_minor(a, j, i, n), n - 1), Zn);
		}
	return rez;
}
void criptareAfina(ifstream& in, ofstream& out, cheieAfina k)
{
	int i = 0;
	char m;
	int* M = new int[k.n];
	int* C = new int[k.n];
	while (in >> noskipws >> m)
	{
		M[i++] = da_cod(m);
		if (i == k.n)
		{
			for (int j = 0; j < k.n; j++)
			{
				C[j] = 0;
				for (int l = 0; l < k.n; l++)
				{
					C[j] += k.a[j][l] * M[l] + k.b[l];
				}
				out << da_caracter(C[j]);
			}
			i = 0;
		};
	}
}

void spargereCezar(ifstream& in, ofstream& out, char frecvent = ' ')
{
	frecv(in);
	bloc* ordonat = ordonareFrecvente();
	int k = modulo(-da_cod(ordonat[0].c) + da_cod(frecvent), N);
	cout << k << endl;
	in.clear();
	in.seekg(0);
	criptareCezar(in, out, k);
}

void spargereAfina(ifstream& in, ofstream& out, char frecvent0 = ' ', char frecvent1 = 'e')
{
	frecv(in);
	bloc* ordonat = ordonareFrecvente();
	int a = modulo((da_cod(frecvent1) - da_cod(frecvent0)) * inv(da_cod(ordonat[1].c) - da_cod(ordonat[0].c), N), N);
	int b = modulo(da_cod(frecvent1) - a * da_cod(ordonat[1].c), N);
	in.clear();
	in.seekg(0);
	criptareAfina(in, out, a, b);
}


void spargereafina(ifstream& in, ofstream& out, char frecvent0 = ' ', char frecvent1 = 'a')
{
	frecv(in);
	bloc* ordonat = ordonareFrecvente();
	int a = modulo((da_cod(frecvent0) - da_cod(frecvent1)) * inv(da_cod(ordonat[0].c) - da_cod(ordonat[1].c), N), N);
	int b = modulo(da_cod(frecvent0) - a * da_cod(ordonat[0].c), N);
	in.clear();
	in.seekg(0);


	criptareAfina(in, out, a, b);
}
unsigned long long da_prim(unsigned long long min, unsigned long long max, int nr) {
	unsigned long long r = 0;
	int nrinc = 5;
	while (r % 2 == 0)
		r = rand() % (max - min + 1) + min;
	bool b = Miller_Rabin_determinist(r);
	if ((b==true)&&(r != nr)) return r;
	else
		while (nrinc > 0)
		{
			for (unsigned long long i = r;i <= max;i = i + 2)
			{
				b = Miller_Rabin_determinist(i);
				if ((i != nr) && (b == true)) return i;
				nrinc--;
			}
		}
	return -1;
}
unsigned long long log1_d(unsigned long long b, unsigned long long y, unsigned long long p)
{
	unsigned long long prod = 1;
	unsigned long long x = 0;
	while (prod != y && x<p)
	{
		prod = (prod * b) % p;
		x++;
	}
	if (prod == y)
		return x;
	return -1;
}
unsigned long long log_d(unsigned long long b, unsigned long long y, unsigned long long p)
{
	unsigned long long i, j, * v, a;
	a = (unsigned long long)sqrt((unsigned long long)p);
	v = new unsigned long long[a + 1];
	v[0] = 1;
	v[1] = expmod(b, a, p);
	for (i = 2; i <= a; i++)
		v[i] = (v[i - 1] * v[1]) % p;
	y = y%p;
	for (j = 0; j < a; j++) {
		for (i = 0; i <= a; i++)
			if (y == v[i])
				return( i * a - j)% (p - 1);
		y = (y * b) % p;
	}
	return 0;
}
struct RSA_key
{
	int n, e, d, l, j;
};
RSA_key generare_chei()
{
	RSA_key cheie;
	int p, q, n, phi, e, d;
	srand((int)time(NULL));
	p = da_prim(2, 1000, 2);//Generam numere astfel incat produsul a doua asemenea numere sa nu depaseasca domeniul pentru variabile
		q = da_prim(2, 1000, p);
	n = p * q;
	phi = (p - 1) * (q - 1);
	e = 3 + rand() % (phi - 3);
	d = inv(e, phi);
	while (d < 0)
	{//pentru ca e sa fie inversabil
		e++;
		d = inv(e, phi);
	}
	cheie.n = cheie.n = n;
	cheie.e = e;
	cheie.d = d;
	return cheie;
}
void RSA(ifstream in, ofstream out, RSA_key key)
{
	char* c = new char[key.l >= key.j ? key.l : key.j];
	int i = 0, m = 0;
	while (in >> noskipws >> c[i]) {
		m = m * N + da_cod(c[i]);
		if (i == key.j - 1) {
			m = expmod(m, key.e, key.n);
			i = key.l - 1;
			while (m > 0) {
				c[i] = da_caracter(m % N);
				m = m / N;
				i--;
			}
			while (i >= 0)c[i--] = da_caracter(0);
			for (i = 0; i < key.l; i++)out << c[i];
			i = 0;
		}
		else
			i++;
	}
	//out.close();
	in.close();
}
void signRSA(ifstream& in,ofstream& out, RSA_key key1, RSA_key key2){
	//doar semnatura adc ultimele 3 cifre la exp de la tabla
	//din semnatura.txt iau textul de la semnatura adc acel ok
}
void ss(int m, int nr)
{
	int r, n;
	int s[10000],t[10000];
	s[0] = rand() | rand();
	t[0]=s[0];
	cout << "s" << 1 << " = " << bitset<16>(t[0]) << endl;
	n = s[0];
	for (int i = 1;i < nr-1;i++)
	{
		s[i] = rand() | rand();
		t[i] = s[i]^s[i-1];
		cout << "s"<<i+1<<" = " << bitset<16>(t[i]) << endl;
		n = n ^ t[i];
	}

	t[nr - 1] = m ^ s[nr - 2];
	n = n ^ t[nr-1];
	cout << "s" << nr << " = " << bitset<16>(t[nr - 1]) << endl;
	cout << "m=" << n;
}
int val_pol(int* coef, int grad, int x, int p)
{
	int S = 0;
	for (int i = grad; i >= 0; i--)
		S = modulo(S * x + coef[i], p);
	return S;
}
void fragmentare_secret()
{
	int M, n, m, p, * a;
	cout << "Dati secretul: ";
	cin >> M;
	cout << "Dati numarul total de fragmente: ";
	cin >> n;
	cout << "Dati numarul de fragmente pentru reconstituirea secretului: ";
	cin >> m;
	for (p = M + 1; p < M * 2; p++)//mai trebuie verificat ca p>n
		if (prim(p)) break;
	a = new int[m];//coeficientii polinomului
	a[0] = M;
	for (int i = 1; i < m - 1; i++)
		a[i] = rand() % p;
	a[m - 1] = 1 + rand() % (p - 1);
	cout << "\nFragmente generate:\n";
	for (int i = 1; i <= n; i++)
		cout << "(" << i << "," << val_pol(a, m - 1, i, p) << ")" << " ";
	cout << "S-a folosit numarul prim: " << p << endl;
}
int reconstituire_secret(int p, int k, int* x, int* y)
{
	int S = 0;
	for (int i = 0; i < k; i++)
	{
		int l = 1;
		for (int j = 0; j < k; j++)
			if (j != i)
				l = modulo(-x[j] * l * inv(x[i] - x[j], p), p);
		S = modulo(S + y[i] * l, p);
	}
	return S;
}

