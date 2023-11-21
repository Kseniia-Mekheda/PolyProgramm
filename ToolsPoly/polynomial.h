#pragma once
#include <iostream>

struct PolyNode;
// Список-многочлен
using Polynomial = PolyNode*;
// Вузол списку, доданок полінома
struct PolyNode
{
	double coef;
	int power;
	Polynomial next;
	PolyNode(double c, int p, Polynomial n = nullptr) :coef(c), power(p), next(n) {}
	Polynomial operator+(Polynomial other);
};

// читає з потоку введення пари (коефіцієнт степінь), створює список-поліном 
Polynomial ReadPoly(std::istream& is);

// створює список-поліном за масивом коефіцієнтів, що починається з вільного члена
// степінь полінома n-1
Polynomial CreatePoly(double* a, int n);

// очищує пам'ять від ланок списку, робить p == nullptr
void RemovePoly(Polynomial& p);

// обчислює і повертає поліном а+b 
Polynomial AddPoly(Polynomial a, Polynomial b);

// домножує коефіцієнти полінома р на константу с 
Polynomial MultByC(Polynomial a, double c);

// обчислює і повертає поліном а*b 
Polynomial MultPoly(Polynomial a, Polynomial b);

// перевіряє рівність поліномів 
bool AreEqual(Polynomial A, Polynomial B);

// обчислює значення полінома P в точці х 
double CalcValue(Polynomial P, double x);

// повертає степінь полінома (найбільший степінь доданка) 
int Degree(Polynomial p);

// повертає поліном - похідну аргумента 
Polynomial Derivative(Polynomial p);

// повертає первісну, що проходить через точку (x_0;y_0) 
Polynomial Integral(Polynomial p, double x_0, double y_0);

// виводить поліном в потік у математичному записі
std::ostream& operator<<(std::ostream& os, Polynomial p);

//вводить поліном в потік
std::istream& operator>>(std::istream& is, PolyNode& A);

//ділить коефіцієнти полінома p на константу с 
Polynomial DivideByC(Polynomial p, double с);

//обчислює і повертає поліном a-b 
Polynomial SubstractPoly(Polynomial A, Polynomial B);
