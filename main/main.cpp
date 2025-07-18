#include "EllipticCurve.hpp"
#include <iostream>

int main() {
    // Define a small prime
    Integer prime(223);
    FiniteField GF(prime);

    // Define curve: y^2 = x^3 + ax + b over GF(223)
    auto a = GF.element(3);
    auto b = GF.element(89);

    // Define generator point G = (47, 71)
    auto Px = GF.element(47);
    auto Py = GF.element(71);

    auto Gx = GF.element(127);
    auto Gy = GF.element(44);

    EllipticCurve curve(a, b);

    // Print curve details
    std::cout << "Elliptic Curve: " << curve.toString() << std::endl;

    // Create a point on the curve
    EllipticCurve::Point P = curve.createPoint(Px, Py);
    EllipticCurve::Point G = curve.createPoint(Gx, Gy);

    // Add P to itself
    EllipticCurve::Point Q = P + P;
    EllipticCurve::Point T = P + G;
    curve.is_on_curve(T); // Check if T is on the curve
    // Output results
    std::cout << "P = " << P << std::endl;
    std::cout << "2P = " << Q << std::endl;
    std::cout << "P + G = " << T << std::endl;

    return 0;
}
