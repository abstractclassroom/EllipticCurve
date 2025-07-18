#include "EllipticCurve.hpp"
#include <vector>
#include <gtest/gtest.h>

// Helper to verify that a point lies on the given curve
void expectOnCurve(const EllipticCurve& curve, const EllipticCurve::Point& P) {
    EXPECT_TRUE(curve.is_on_curve(P)) << "Point " << P << " is not on the curve.";
}

// Test curve y^2 = x^3 + 7 over GF(223)
TEST(EllipticCurveTest, Curve1_y2_eq_x3_plus_7) {
    Integer prime(223);
    FiniteField GF(prime);

    auto a = GF.element(0);
    auto b = GF.element(7);
    EllipticCurve curve(a, b);

    // Known points on the curve
    std::vector<std::pair<int, int>> knownPoints = {
        {47, 71}, 
        {126, 96}, 
        {47, 152}, 
        {69, 86}, 
        {126, 127}
    };
    std::vector<EllipticCurve::Point> points;

    for (const auto& [x, y] : knownPoints) {
        auto Px = GF.element(x);
        auto Py = GF.element(y);
        auto P = curve.createPoint(Px, Py);
        points.push_back(P);
        expectOnCurve(curve, P);
    }

    // test all pairs of addition of points
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < points.size(); ++j) {
            const auto& P1 = points[i];
            const auto& P2 = points[j];
            auto sum = P1 + P2;
            expectOnCurve(curve, sum);
        }
    }
}

// Test curve y^2 = x^3 + 3x + 89 over GF(223)
TEST(EllipticCurveTest, Curve2_y2_eq_x3_plus_3x_plus_89) {
    Integer prime(223);
    FiniteField GF(prime);

    auto a = GF.element(3);
    auto b = GF.element(89);
    EllipticCurve curve(a, b);

    // Known point
    auto Px = GF.element(47);
    auto Py = GF.element(71);
    auto P = curve.createPoint(Px, Py);
    expectOnCurve(curve, P);

    // Test doubling
    auto Q = P + P;
    expectOnCurve(curve, Q);

    // Test addition with another point
    auto Gx = GF.element(127);
    auto Gy = GF.element(44);
    auto G = curve.createPoint(Gx, Gy);
    expectOnCurve(curve, G);

    auto T = P + G;
    expectOnCurve(curve, T);
}

// Test scalar multiplication on y^2 = x^3 + 2x + 2 over GF(17)
TEST(EllipticCurveTest, ScalarMultiply_GF17) {
    Integer prime(17);
    FiniteField GF(prime);

    auto a = GF.element(2);
    auto b = GF.element(2);
    EllipticCurve curve(a, b);

    auto Gx = GF.element(5);
    auto Gy = GF.element(1);
    auto G = curve.createPoint(Gx, Gy);
    expectOnCurve(curve, G);

    // 2G
    auto G2 = G + G;
    expectOnCurve(curve, G2);

    // 3G using scalarMultiply
    auto G3 = G.scalarMultiply(3);
    EXPECT_EQ(G3, G + G + G);
    expectOnCurve(curve, G3);

    // Check point at infinity after full cycle (order 19 for this curve)
    auto inf = G.scalarMultiply(19);
    EXPECT_TRUE(inf.isInfinity);
}
