// Aproksymacja.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "pch.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

class punkt {
public:
	double x, y;
};

double iloczynSkalarny(double tab[], double tab2[], int n) {
	double wynik = 0;
	for (int i = 0; i < n; i++)
		wynik += tab[i]*tab2[i];
	return wynik;
}

double lagendre(double x, double n) {
	if (n == 0)
		return 1;
	else if (n == 1)
		return x;
	else
		return ((((2 * n - 1) / n) * x *lagendre(x, n - 1)) - (((n - 1) / n) * lagendre(x, n - 2)));
}

double elementH(int n, double fx[], double fy[], double x) {
	double wynik = 0.;

	double* lag= new double[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			lag[j] = lagendre(fx[j], i);
		}
		wynik += iloczynSkalarny(fy, lag, n) / iloczynSkalarny(lag, lag, n)*lagendre(x, i);
	}
	return wynik;
}

double approx(double x,double fx[], double fy[]) {
	return elementH(6, fx, fy, x);
}

int main()
{
	ifstream odczyt;
	ofstream zapis;
	zapis.open("aproks2.txt");
	odczyt.open("punkty.txt");
	//double fx[6] = { -1,-0.4,-0.2,-0.1,0.4,1.0 };
	//double fy[6] = { 0.1,5.3,4.4,2.5,3.7,12.0 };
	double fx[6], fy[6];
	for (int i = 0; i < 6; i++) {
		odczyt >> fx[i] >> fy[i];
	}
		
	for (double x = -1.0; x <= 1.0; x += 0.1) {
		zapis << approx(x,fx,fy)<<endl;
		cout << approx(x,fx,fy) << endl;
	}
	zapis.close();
	odczyt.close();
	return 0;
}