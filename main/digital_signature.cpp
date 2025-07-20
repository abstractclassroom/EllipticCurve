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
    auto modulus = params.n;  // n is used as a modulus, not a field element
    EllipticCurve curve(a, b);
    auto G = curve.createPoint(gx, gy);

    auto GG = G.scalarMultiply(modulus);
    std::cout << "GG = " << GG << std::endl;

    // HASH OF ORIGINAL MESSAGE
    Integer HASH_BASE_10("5121999207149805743248838456851986493914089000052133121297052643529222900553");

    // BOB'S SIGNATURE GENERATION
    Integer BOB_PRIVATE_KEY("28475757382829293384747483829223456654345434098234598");
    Integer BOB_EPHEMERAL_KEY("3409834928374298427898472938573948573943204928043298520958340");
    auto R = G.scalarMultiply(BOB_EPHEMERAL_KEY);
    auto R_x = R.x;
    auto R_y = R.y;
    std::cout << "R.x = " << R_x << std::endl;
    
    Integer S = (Integer::mod_inverse(BOB_EPHEMERAL_KEY, modulus ) * (HASH_BASE_10 + BOB_PRIVATE_KEY * R_x.value)) % modulus;
    std::cout << "S = " << S << std::endl;
    std::cout << "R = " << R << std::endl;

    // BOB Public Key
    auto BOB_PUBLIC_KEY = G.scalarMultiply(BOB_PRIVATE_KEY);

    // BOB SENDS (R, S) TO ALICE
    // ALICE RECEIVES (R, S) FROM BOB
    // ALICE NOW CAN VERIFY THE SIGNATURE
    // ALICE COMPUTES THE HASH OF THE MESSAGE (SAME AS BOB)
    Integer S_inv = Integer::mod_inverse(S, modulus);
    Integer u1 = (S_inv * HASH_BASE_10) % modulus;
    Integer u2 = (S_inv * R_x.value) % modulus;

    auto P = G.scalarMultiply(u1) + BOB_PUBLIC_KEY.scalarMultiply(u2);
    std::cout << "P.x = " << P.x << std::endl;

    // Compare P.x with R.x
    if (P.x == R_x) {
        std::cout << "Signature is valid!" << std::endl;
    } else {
        std::cout << "Signature is NOT valid!" << std::endl;
    }

    return 0;
}
