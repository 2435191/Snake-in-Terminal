#include <array>
#include <string>
#include <sstream>

class Point : public std::array<int, 2> {
public:
    size_t operator() (const Point& p) const {
        return std::hash<int>()(p[0]) ^ std::hash<int>()(p[1]);
    }
    Point operator+ (const Point& p) const {
        Point out = *this;
        out[0] += p[0];
        out[1] += p[1];
        return out;
    }
    Point operator- (const Point& p) const {
        Point out = *this;
        out[0] -= p[0];
        out[1] -= p[1];
        return out;
    }

    Point operator* (const int i) const {
        Point out = *this;
        out[0] *= i;
        out[1] *= i;
        return out;
    }

    operator std::string() const {
        std::stringstream s;
        s << "(" << this->at(0) << ", " << this->at(1) << ")";
        return s.str();
    }
    


};