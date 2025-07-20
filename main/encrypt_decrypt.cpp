#include "EllipticCurve.hpp"
#include <iostream>

int main() {
    EllipticCurve::CurveRegistry registry("../main/curves.json");
    auto params = registry.getParamsByID("NIST_P256");
    FiniteField field(params.p);
    auto a = field.element(params.a);
    auto b = field.element(params.b);
    auto gx = field.element(params.gx);
    auto gy = field.element(params.gy);
    auto n = field.element(params.n);
    EllipticCurve curve(a, b);
    auto G = curve.createPoint(gx, gy);

    // Bob Public Key 
    auto BOB_PRIVATE_KEY = field.element("9083838473822342329193848596969658483829118293443");
    auto BOB_PUBLIC_KEY = G.scalarMultiply(BOB_PRIVATE_KEY);
    std::cout << "Bob's Public Key: " << BOB_PUBLIC_KEY << std::endl;

    // Alice Public Key
    auto ALICE_PRIVATE_KEY = field.element("356472828283475757432111223468542458087534534456787");
    auto ALICE_PUBLIC_KEY = G.scalarMultiply(ALICE_PRIVATE_KEY);
    std::cout << "Alice's Public Key: " << ALICE_PUBLIC_KEY << std::endl;

    // Shared Secret Calculation
    auto BOB_SHARED_SECRET = ALICE_PUBLIC_KEY.scalarMultiply(BOB_PRIVATE_KEY);
    auto ALICE_SHARED_SECRET = BOB_PUBLIC_KEY.scalarMultiply(ALICE_PRIVATE_KEY);
    std::cout << "Bob's Shared Secret: " << BOB_SHARED_SECRET << std::endl;
    std::cout << "Alice's Shared Secret: " << ALICE_SHARED_SECRET << std::endl; 
    if (BOB_SHARED_SECRET == ALICE_SHARED_SECRET) {
        std::cout << "Shared secrets match!" << std::endl;
    } else {
        std::cout << "Shared secrets do not match!" << std::endl;
    }   

    return 0;
}