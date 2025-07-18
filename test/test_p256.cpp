#include "EllipticCurve.hpp"
#include <gtest/gtest.h>

TEST(EllipticCurveTest, P256CurveScalarMultiplication) {
    // Setup prime and field
    Integer prime("115792089210356248762697446949407573530086143415290314195533631308867097853951");
    FiniteField GF(prime);

    // Curve coefficients
    auto a = GF.element(-3);
    auto b = GF.element("41058363725152142129326129780047268409114441015993725554835256314039467401291");
    EllipticCurve curve(a, b);

    // Generator coordinates
    auto Gx = GF.element("48439561293906451759052585252797914202762949526041747995844080717082404635286");
    auto Gy = GF.element("36134250956749795798585127919587881956611106672985015071877198253568414405109");

    // Create G
    EllipticCurve::Point G = curve.createPoint(Gx, Gy);

    // Verify G is on the curve using raw Integer math
    Integer xCoord = Gx.value;
    Integer yCoord = Gy.value;
    Integer aValue = prime -3;
    Integer bValue = b.value;

    Integer expectedLHS = yCoord * yCoord;
    Integer expectedRHS = xCoord * xCoord * xCoord + aValue * xCoord + bValue;

    EXPECT_EQ(expectedLHS % prime, expectedRHS % prime) << "Generator point should be on the curve";

    // Double-and-add test via manual additions
    EllipticCurve::Point G2 = G + G;
    EllipticCurve::Point G4 = G2 + G2;
    EllipticCurve::Point G8 = G4 + G4;
    EllipticCurve::Point G16 = G8 + G8;
    EllipticCurve::Point G32 = G16 + G16;
    EllipticCurve::Point G64 = G32 + G32;
    EllipticCurve::Point G128 = G64 + G64;
    EllipticCurve::Point G256 = G128 + G128;
    EllipticCurve::Point G512 = G256 + G256;
    EllipticCurve::Point G1024 = G512 + G512;
    EllipticCurve::Point G1028 = G1024 + G4;
    EllipticCurve::Point G1030 = G1028 + G2;

    // Scalar multiply
    EllipticCurve::Point P = G.scalarMultiply(Integer(1030));

    EXPECT_TRUE(P == G1030) << "Scalar multiplication by 1030 should match repeated addition";
}
