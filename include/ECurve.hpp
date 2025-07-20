#ifndef ECURVE_HPP
#define ECURVE_HPP

#include "FiniteField.hpp"
#include <iostream>
#include <string>
#include <unordered_map>  // Added this

class EllipticCurve {
public:
    using FieldElement = FiniteField::FieldElement;

    class Point;

    EllipticCurve(const FieldElement& a, const FieldElement& b);

struct CurveRegistry {
    struct Params {
        std::string id;
        std::string p;
        std::string a;
        std::string b;
        std::string gx;
        std::string gy;
        std::string n;
    };

    explicit CurveRegistry(const std::string& jsonPath);

    const Params& getParamsByID(const std::string& id) const;
    const std::unordered_map<std::string, Params>& getAll() const;

private:
    std::unordered_map<std::string, Params> curves_;
};


    static EllipticCurve fromID(const std::string& id);

    Point createPoint(const FieldElement& x, const FieldElement& y) const;
    bool is_on_curve(const Point& P) const;
    std::string toString() const;

    const FieldElement& getAParameter() const;
    const FieldElement& getBParameter() const;
    const Integer& getPrime() const;

private:
    const FiniteField* field_;
    FieldElement a_;
    FieldElement b_;
};

#endif // ECURVE_HPP
