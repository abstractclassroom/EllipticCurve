#include "EllipticCurve.hpp"
#include "gtest/gtest.h"

TEST(EllipticCurveTest, PointAddition) {
    using FieldElement = FiniteField::FieldElement;

    FieldElement a(2), b(2);
    EllipticCurve curve;
    curve.setA(a);
    curve.setB(b);

    EllipticCurve::Point G(FieldElement(5), FieldElement(1), &curve);
    curve.setGenerator(G);

    EXPECT_TRUE(curve.is_on_curve(G));

    EllipticCurve::Point R = G + G;

    EXPECT_TRUE(curve.is_on_curve(R));
}
