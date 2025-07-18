#ifndef ELLIPTIC_CURVE_HPP
#define ELLIPTIC_CURVE_HPP

#include "FiniteField.hpp"
#include <iostream>

class EllipticCurve {
public:
    using FieldElement = FiniteField::FieldElement;

    class Point {
    public:
        FieldElement x, y;
        bool isInfinity;

        Point() : x(FieldElement()), y(FieldElement()), isInfinity(true) {}
    

        Point(FieldElement x, FieldElement y, const EllipticCurve* c)
            : x(x), y(y), curve(c), isInfinity(false) {}

        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
        Point operator+(const Point& other) const;
        Point& operator+=(const Point& other);
        friend std::ostream& operator<<(std::ostream& os, const Point& p);
    };

private:
    Integer p_(0);
    FieldElement a_, b_;
    Point generator_;

public:
    EllipticCurve() : a_(0), b_(0), generator_() {}

    EllipticCurve(const FieldElement& a, const FieldElement& b, const Point& generator);

    // Getters
    const FieldElement& a() const { return a_; }
    const FieldElement& b() const { return b_; }
    const Point& generator() const { return generator_; }
    const Integer& p() const { return a_.getPrime(); }

    // Setters
    void setA(const FieldElement& a) { a_ = a; }
    void setB(const FieldElement& b) { b_ = b; }
    void setGenerator(const Point& g) {
        generator_ = g;
        generator_.curve = this;
    }

    bool is_on_curve(const Point& P) const;
};

#endif // ELLIPTIC_CURVE_HPP
