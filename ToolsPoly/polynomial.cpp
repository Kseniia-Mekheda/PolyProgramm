#include "pch.h"
#include "polynomial.h"
#include <iostream>
#include <iomanip>

Polynomial CreatePoly(double* a, int n)
{
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] != 0.0)
        {
            curr->next = new PolyNode(a[i], i);
            curr = curr->next;
        }
    }
    return phantom.next;
}

void RemovePoly(Polynomial& p)
{
    while (p != nullptr)
    {
        Polynomial victim = p;
        p = p->next;
        delete victim;
    }
}

Polynomial AddPoly(Polynomial a, Polynomial b)
{
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    while (a != nullptr && b != nullptr)
    {
        if (a->power == b->power)
        {
            double s = a->coef + b->coef;
            if (s != 0.0)
            {
                curr->next = new PolyNode(s, a->power);
                curr = curr->next;
            }
            a = a->next; b = b->next;
        }
        else if (a->power < b->power)
        {
            curr->next = new PolyNode(a->coef, a->power);
            curr = curr->next;
            a = a->next;
        }
        else
        {
            curr->next = new PolyNode(b->coef, b->power);
            curr = curr->next;
            b = b->next;
        }
    }
    while (a != nullptr)
    {
        curr->next = new PolyNode(a->coef, a->power);
        curr = curr->next;
        a = a->next;
    }
    while (b != nullptr)
    {
        curr->next = new PolyNode(b->coef, b->power);
        curr = curr->next;
        b = b->next;
    }
    return phantom.next;
}

bool AreEqual(Polynomial A, Polynomial B)
{
    while (A != nullptr && B != nullptr && A->coef == B->coef && A->power == B->power)
    {
        A = A->next;
        B = B->next;
    }
    return A == B;
}

double CalcValue(Polynomial P, double x)
{
    double res = 0.0;
    double p = 1.0; // степінь x
    int i = 0;
    while (P != nullptr)
    {
        while (i < P->power)
        {
            p *= x;
            ++i;
        }
        res += P->coef * p;
        P = P->next;
    }
    return res;
}

int Degree(Polynomial p)
{
    while (p->next != nullptr) p = p->next;
    return p->power;
}

Polynomial Derivative(Polynomial p)
{
    if (p->power == 0) p = p->next;
    PolyNode phantom(0., 0);
    Polynomial curr = &phantom;
    while (p != nullptr)
    {
        curr->next = new PolyNode(p->coef * p->power, p->power - 1);
        curr = curr->next;
        p = p->next;
    }
    return phantom.next;
}

std::ostream& operator<<(std::ostream& os, Polynomial p)
{
    while (p != nullptr)
    {
        os << std::showpos << p->coef << "x^" << std::noshowpos << p->power << ' ';
        p = p->next;
    }
    return os;
}

Polynomial PolyNode::operator+(Polynomial other)
{
    return AddPoly(this, other);
}

Polynomial MultByC(Polynomial a, double c) {
    if (c == 0) {
        return nullptr;
    }

    PolyNode phantom(0., 0);
    Polynomial curr = &phantom;
    while (a != nullptr) {
        double coef = a->coef * c;
        curr->next = new PolyNode(coef, a->power);
        curr = curr->next;
        a = a->next;
    }
    return phantom.next;
}

Polynomial Integral(Polynomial p, double x_0, double y_0) {
    PolyNode phantom(0., 0);
    Polynomial curr = &phantom;
    while (p != nullptr) {
        double num = p->coef;
        int n = p->power;
        if (num != 0.) {
            double coefI = num / (n + 1.0);
            p->power = n + 1;
            p->coef = coefI;
        }
        curr->next = new PolyNode(p->coef, p->power);
        curr = curr->next;
        p = p->next;
    }
    double C;
    double value = CalcValue(phantom.next, x_0);
    C = y_0 - value;
    curr = &phantom;
    curr->next = new PolyNode(C, 0, curr->next);
    return phantom.next;
}

std::istream& operator>>(std::istream& is, PolyNode& A) {
    is >> A.coef >> A.power;
    return is;
}

Polynomial ReadPoly(std::istream& is) {
    PolyNode phantom(0., 0);
    Polynomial formula;
    PolyNode elements(0., 0);
    while (is >> elements) {
        formula = &phantom;
        if (elements.coef != 0 && elements.power >= 0) {
            while (formula->next != nullptr && formula->next->power <= elements.power) {
                formula = formula->next;
            }
            formula->next = new PolyNode(elements.coef, elements.power, formula->next);
        }
    }
    return phantom.next;
}

Polynomial MultPoly(Polynomial a, Polynomial b) {
    Polynomial summPtr = new PolyNode(0, 0);
    Polynomial victim;

    while (a != nullptr) {
        Polynomial bPtr = b;
        while (bPtr != nullptr) {
            Polynomial termPtr = new PolyNode(a->coef * bPtr->coef, a->power + bPtr->power);
            victim = summPtr;
            summPtr = AddPoly(summPtr, termPtr);
            delete victim;
            delete termPtr;
            bPtr = bPtr->next;
        }

        a = a->next;
    }
    return summPtr;
}

Polynomial DivideByC(Polynomial p, double c) {
    if (c == 0) {
        return nullptr;
    }
    return MultByC(p, 1 / c);
}

Polynomial SubstractPoly(Polynomial A, Polynomial B) {
    return AddPoly(A, MultByC(B, -1.));
}