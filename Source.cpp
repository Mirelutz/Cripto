#include<iostream>
using namespace std;
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
void cmmdcext(int a, int b) {
	int r, ca, cb, d, e=1, r1,r2,r3,r4,r5,r6;
	//int v[1000][2];
	ca = a;cb = b;
	r1=1;r2=0;r4=0;r5=1;
	//v[0][0] = 1;v[0][1] = 0;v[1][0] = 0;v[1][1] = 1;
	while (b)
	{
		e++;
		d = a / b;
		r = a % b;
		r3= r1-d*r2;
		r6 = r4 - d * r5;
		//v[e][0] = v[e - 2][0] - d * v[e - 1][0];
		//v[e][1] = v[e - 2][1] - d * v[e - 1][1];
		a = b;
		b = r;
		r1 = r2;r2 = r3;
		r4 = r5;r5 = r6;
	}
	cout << a<<"="<<r1 <<"*"<<ca <<"+" <<r4<< "*"<<cb << endl;
}
int main() {
	cmmdcext(841, 160);

}