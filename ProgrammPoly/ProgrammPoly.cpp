#include <iostream>
#include "../ToolsPoly/polynomial.h"
#include <iomanip>

int main()
{
    double a[] = { -99.,1.,2.,1. };
    const int n = sizeof a / sizeof a[0];
    double b[] = { 75.,0.,-2.,-1.,0.,0.,4.,0.,1. };
    const int m = sizeof b / sizeof b[0];
    const double c = 2.6;
    double x_0 = 1.;
    double y_0 = 3.;

    Polynomial P = CreatePoly(a, n);
    std::cout << "P_3(x) = " << P << '\n';

    Polynomial P2 = AddPoly(P, P);
    std::cout << "P2_3(x) = " << P2 << '\n';

    Polynomial R = CreatePoly(b, m);
    std::cout << "R_8(x) = " << R << '\n';

    Polynomial C = AddPoly(P, R);
    std::cout << "C_8(x) = " << C << '\n';
    std::cout << "Are equal: " << std::boolalpha << AreEqual(P, P)
        << "\nAre equal: " << AreEqual(P, P2) << '\n';

    Polynomial D = *P + R;
    std::cout << "D_8(x) = " << D << '\n';
    std::cout << "The function and the operator act equally: " << AreEqual(C, D) << '\n';

    Polynomial V = Derivative(C);
    std::cout << "C_8'(x) = " << V << '\n';

    Polynomial Q = MultByC(P, c);
    std::cout << "Q_8(x) = " << Q << '\n';

    Polynomial E = Integral(P, x_0, y_0);
    std::cout << "E_8(x) = " << E << '\n';

    Polynomial M = MultPoly(P2, P2);
    std::cout << "M_8(x) = " << M << '\n';

    Polynomial B = DivideByC(P2, c);
    std::cout << "B_8(x) = " << B << '\n';

    Polynomial W = SubstractPoly(P, R);
    std::cout << "W_8(x) = " << W << '\n';

    std::cout << "Input elements of polynomial in such form: coefficient power.\n" <<
        "(If you filled all the elements needed, input any letter or symbol): \n";
    Polynomial F = ReadPoly(std::cin);
    std::cout << "Your polynomial F_8(x): " << F << '\n';

    RemovePoly(V);
    RemovePoly(P);
    RemovePoly(P2);
    RemovePoly(R);
    RemovePoly(C);
    RemovePoly(D);
    RemovePoly(Q);
    RemovePoly(E);
    RemovePoly(M);
    RemovePoly(B);
    RemovePoly(W);
    RemovePoly(F);
    return 0;
}
