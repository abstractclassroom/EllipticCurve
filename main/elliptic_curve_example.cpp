#include <iostream>
#include "EllipticCurve.hpp"

using Field = FiniteField::FieldElement;

int main() {
    FiniteField GF(97);
    EllipticCurve curve;

    // Set curve parameters: y^2 = x^3 + ax + b
    Field a = GF.element(9);
    Field b = GF.element(13);
    curve.setA(a);
    curve.setB(b);

    // Create a generator point and set it
    EllipticCurve::Point G(Field(10), Field(6), &curve);
    EllipticCurve::Point H(Field(45),Field(84), &curve);
    EllipticCurve::Point GH = G+H;
    std::cout<<"GH "<<GH<<std::endl;
    curve.setGenerator(G);

    // Show generator
    std::cout << "G = " << G << std::endl;

    // Perform 2G = G + G
    EllipticCurve::Point P = G + G;
    std::cout << "2G = " << P << std::endl;

    // Perform 3G = 2G + G
    EllipticCurve::Point Q = P + G;
    std::cout << "3G = " << Q << std::endl;

    return 0;
}
