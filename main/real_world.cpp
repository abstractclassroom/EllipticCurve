#include "EllipticCurve.hpp"
#include <iostream>

int main() {
    EllipticCurve::CurveRegistry registry("../main/curves.json");
    auto params = registry.getParamsByID("NIST_P256");
    FiniteField field(params.p);
    auto aa = field.element(params.a);
    auto bb = field.element(params.b);
    auto gx = field.element(params.gx);
    auto gy = field.element(params.gy);
    EllipticCurve curve2(aa, bb);
    auto GG = curve2.createPoint(gx, gy);

    

    Integer prime("115792089210356248762697446949407573530086143415290314195533631308867097853951");
    FiniteField GF("115792089210356248762697446949407573530086143415290314195533631308867097853951");
    auto a = GF.element(-3);
    auto b = GF.element("41058363725152142129326129780047268409114441015993725554835256314039467401291");
    EllipticCurve curve(a, b);
    // // EllipticCurve curve = EllipticCurve::fromID(EllipticCurve::EllipticCurveID::NIST_P256);

    auto Gx = GF.element("48439561293906451759052585252797914202762949526041747995844080717082404635286");
    auto Gy = GF.element("36134250956749795798585127919587881956611106672985015071877198253568414405109");




    Integer xCoord = Integer("48439561293906451759052585252797914202762949526041747995844080717082404635286");
    Integer yCoord = Integer("36134250956749795798585127919587881956611106672985015071877198253568414405109");
    Integer aValue = Integer("115792089210356248762697446949407573530086143415290314195533631308867097853948");
    Integer bValue = Integer("41058363725152142129326129780047268409114441015993725554835256314039467401291");
    Integer dd = xCoord * xCoord * xCoord + aValue * xCoord + bValue ;
    Integer yy = yCoord * yCoord;

    std::cout << "Y * Y = " << Gy * Gy << std::endl;
    std::cout << "YY = " << yy % prime << std::endl;

    if (yy % prime == dd % prime) {
        std::cout << "Point G is on the curve." << std::endl;
    } else {
        std::cout << "Point G is NOT on the curve." << std::endl;
    }



    // Print curve details
    std::cout << "Elliptic Curve: " << curve.toString() << std::endl;



    // Create a point on the curve
    EllipticCurve::Point G = curve.createPoint(Gx, Gy);
std::cout << "G is infinity: " << G.isInfinity << "\n";
std::cout << "GG is infinity: " << GG.isInfinity << "\n";
std::cout << "G.x == GG.x? " << (G.x == GG.x ? "yes" : "no") << "\n";
std::cout << "G.y == GG.y? " << (G.y == GG.y ? "yes" : "no") << "\n";

    //print all parameters of G
    std::cout << "Gx : " << G.x << "\n";
    std::cout << "Gy : " << G.y << "\n";
    std::cout << "G  Prime from curve: " << curve.getPrime() << "\n";

    //Do the same for GG
    std::cout << "GGx: " << GG.x << "\n";
    std::cout << "GGy: " << GG.y << "\n";
    std::cout << "GG Prime from curve: " << curve2.getPrime() << "\n";
    std::cout<<"GG: " << GG << "\n";
    std::cout<<"G : " << G << "\n";
    if (GG == G) {
        std::cout << "GG is equal to G" << std::endl;
    } else {
        std::cout << "GG is NOT equal to G" << std::endl;
    }
    // EllipticCurve curve2 = EllipticCurve::fromID(EllipticCurve::EllipticCurveID::NIST_P256);
    // EllipticCurve::Point G1 = curve2.createPoint(Gx, Gy);
    // std::cout << "G = " << G << std::endl;
    // std::cout << "G1 = " << G1 << std::endl;

    // Successive point additions
    auto G2 = G + G;
    auto G4 = G2 + G2;
    auto G8 = G4 + G4;
    auto G16 = G8 + G8;
    auto G32 = G16 + G16;
    auto G64 = G32 + G32;
    auto G128 = G64 + G64;
    auto G256 = G128 + G128;
    auto G512 = G256 + G256;
    auto G1024 = G512 + G512;
    auto G1028 = G1024 + G4;
    auto G1030 = G1028 + G2;
    std::cout << "G = " << G << std::endl;
    std::cout << "G1030 = " << G1030 << std::endl;

    auto P = G.scalarMultiply(Integer(1030));
    //The above can be called as follows::
    // EllipticCurve::Point P = G.scalarMultiply(1030);
    std::cout << "P = " << P << std::endl;
    std::cout << "(P == G1030) -->"<< ((P == G1030) ? "True" : "False") << std::endl;
std::cout<< "P ==GG1030 --> " << ((P == GG.scalarMultiply(1030)) ? "True" : "False") << std::endl;
    return 0;
}
