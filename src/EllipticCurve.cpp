#include "EllipticCurve.hpp"
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using CurveParams = EllipticCurve::CurveRegistry::Params;

// --- EllipticCurve Implementation ---

EllipticCurve::EllipticCurve(const FieldElement& a, const FieldElement& b)
    : field_(a.field), a_(a), b_(b) {}

EllipticCurve::Point EllipticCurve::createPoint(const FieldElement& x, const FieldElement& y) const {
    Point p1(x, y, this);
    if (!is_on_curve(p1)) {
        throw std::invalid_argument("Point is not on the curve");
    }
    return p1;
}

bool EllipticCurve::is_on_curve(const Point& P) const {
    if (P.isInfinity) return true;
    const auto& x = P.x;
    const auto& y = P.y;
    return y * y == x * x * x + a_ * x + b_;
}

std::string EllipticCurve::toString() const {
    std::ostringstream oss;
    oss << "y^2 = x^3 + " << a_ << "x + " << b_ << " over GF(" << field_->getPrime() << ")";
    return oss.str();
}

const EllipticCurve::FieldElement& EllipticCurve::getAParameter() const { return a_; }
const EllipticCurve::FieldElement& EllipticCurve::getBParameter() const { return b_; }
const Integer& EllipticCurve::getPrime() const { return field_->getPrime(); }

std::ostream& operator<<(std::ostream& os, const EllipticCurve::Point& p) {
    if (p.isInfinity) return os << "Point(infinity)";
    return os << "Point(" << p.x << ", " << p.y << ")";
}

EllipticCurve EllipticCurve::fromID(const std::string& id) {
    throw std::logic_error("Use CurveRegistry instance to load by ID instead of static fromID.");
}

// --- CurveRegistry (Nested Class) Implementation ---

EllipticCurve::CurveRegistry::CurveRegistry(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open curve registry file: " + path);
    }

    json j;
    file >> j;

    for (auto& [name, obj] : j.items()) {
        curves_[name] = Params{
            name,
            obj["p"].get<std::string>(),
            obj["a"].get<std::string>(),
            obj["b"].get<std::string>(),
            obj["gx"].get<std::string>(),
            obj["gy"].get<std::string>(),
            obj["n"].get<std::string>()
        };
    }
}

const EllipticCurve::CurveRegistry::Params& EllipticCurve::CurveRegistry::getParamsByID(const std::string& id) const {
    auto it = curves_.find(id);
    if (it == curves_.end()) throw std::invalid_argument("Curve not found: " + id);
    return it->second;
}

const std::unordered_map<std::string, EllipticCurve::CurveRegistry::Params>& EllipticCurve::CurveRegistry::getAll() const {
    return curves_;
}
