#pragma once
#include <iostream>

struct PolyNode;
// ������-���������
using Polynomial = PolyNode*;
// ����� ������, ������� �������
struct PolyNode
{
	double coef;
	int power;
	Polynomial next;
	PolyNode(double c, int p, Polynomial n = nullptr) :coef(c), power(p), next(n) {}
	Polynomial operator+(Polynomial other);
};

// ���� � ������ �������� ���� (���������� ������), ������� ������-������ 
Polynomial ReadPoly(std::istream& is);

// ������� ������-������ �� ������� �����������, �� ���������� � ������� �����
// ������ ������� n-1
Polynomial CreatePoly(double* a, int n);

// ����� ���'��� �� ����� ������, ������ p == nullptr
void RemovePoly(Polynomial& p);

// �������� � ������� ������ �+b 
Polynomial AddPoly(Polynomial a, Polynomial b);

// ������� ����������� ������� � �� ��������� � 
Polynomial MultByC(Polynomial a, double c);

// �������� � ������� ������ �*b 
Polynomial MultPoly(Polynomial a, Polynomial b);

// �������� ������ ������� 
bool AreEqual(Polynomial A, Polynomial B);

// �������� �������� ������� P � ����� � 
double CalcValue(Polynomial P, double x);

// ������� ������ ������� (��������� ������ �������) 
int Degree(Polynomial p);

// ������� ������ - ������� ��������� 
Polynomial Derivative(Polynomial p);

// ������� �������, �� ��������� ����� ����� (x_0;y_0) 
Polynomial Integral(Polynomial p, double x_0, double y_0);

// �������� ������ � ���� � ������������� �����
std::ostream& operator<<(std::ostream& os, Polynomial p);

//������� ������ � ����
std::istream& operator>>(std::istream& is, PolyNode& A);

//����� ����������� ������� p �� ��������� � 
Polynomial DivideByC(Polynomial p, double �);

//�������� � ������� ������ a-b 
Polynomial SubstractPoly(Polynomial A, Polynomial B);
