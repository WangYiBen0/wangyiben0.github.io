#include <utility>
#include <initializer_list>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

namespace PlaneGeometry
{
    double sqrt(const double &x) { return __builtin_sqrt(x); }
    long double sqrt(const long double &x) { return __builtin_sqrtl(x); }

    class real
    {
    public:
        typedef long double real_type;
        constexpr static real_type eps = 1e-18;

    private:
        real_type val;
        bool check() const { return val < eps && val > -eps; }

    public:
        real(const real &) = default;
        explicit real(const real_type &v = .0) : val(v) {}
        real &operator=(const real &b) = default;
        real &operator=(const real_type &b) { return val = b, *this; };
        real operator+(const real &b) const { return real(val + b.val); }
        real operator-(const real &b) const { return real(val - b.val); }
        real operator*(const real &b) const { return real(val * b.val); }
        real operator/(const real &b) const { return real(val / b.val); }
        real operator-() const { return real(-val); }
        bool operator<(const real &b) const { return val < b.val; }
        bool operator>(const real &b) const { return val > b.val; }
        bool operator==(const real &b) const { return (b - *this).check(); }
        bool operator!=(const real &b) const { return !(*this == b); }
        real &operator+=(const real &b) { return val += b.val, *this; }
        real &operator-=(const real &b) { return val -= b.val, *this; }
        real &operator*=(const real &b) { return val *= b.val, *this; }
        real &operator/=(const real &b) { return val /= b.val, *this; }
        bool is_zero() const { return check(); }
        operator real_type() const { return val; }
        friend real sqrt(const real &x) { return (real)sqrt(real_type(x.val)); }
        friend std::istream &operator>>(std::istream &in, real &b) { return in >> b.val; }
        friend std::ostream &operator<<(std::ostream &out, const real &b) { return out << b.val; }
    };
    static const real Pi(std::acos(-1));
    class basic_point
    {
    public:
        real x, y;
        basic_point() : x(0.0), y(0.0) {}
        basic_point(const real &x, const real &y) : x(x), y(y) {}
        basic_point(const basic_point &) = default;
        basic_point &operator=(const basic_point &) = default;
        basic_point(std::initializer_list<real> list) : x(list.begin()[0]), y(list.begin()[1]) {}
        basic_point operator-() const { return basic_point(-x, -y); }
        basic_point operator*(const real &b) const { return basic_point(x * b, y * b); }
        basic_point operator/(const real &b) const { return basic_point(x / b, y / b); }
    };
    class point;
    class vector : public basic_point
    {
        using basic_point::basic_point;

    public:
        vector operator+(const vector &b) const { return vector(x + b.x, y + b.y); }
        vector operator-(const vector &b) const { return vector(x - b.x, y - b.y); }
        real operator*(const vector &b) const { return x * b.x + y * b.y; }
        real operator^(const vector &b) const { return x * b.y - y * b.x; }
        real length() const { return sqrt(x * x + y * y); }
        vector unit() const { return vector(x / length(), y / length()); }
        vector rotate(const real &);
    };
    class point : public basic_point
    {
        friend class vector;
        using basic_point::basic_point;

    public:
        friend real distance(const point &a, const point &b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
        point operator-(const vector &b) const { return point(x - b.x, y - b.y); }
        point operator+(const vector &b) const { return point(x + b.x, y + b.y); }
        vector operator-(const point &b) const { return vector(x - b.x, y - b.y); }
        point rotate(const real &, const point &);
    };
    class line
    {
    public:
        point p;
        vector v;

    public:
        line(const point &p, const vector &v) : p(p), v(v) {}
        line(const point &p, const point &q) : p(p), v(q - p) {}
        line(const real a, const real b, const real c) : p(-c / a, -c / b), v(-b, a) {}
        line(const line &) = default;
        friend point cross(const line &a, const line &b)
        {
            return point(a.p.x + a.v.x * (b.v ^ (b.p - a.p)) / (a.v ^ b.v), a.p.y + a.v.y * (b.v ^ (b.p - a.p)) / (a.v ^ b.v));
        }
    };
    vector vector::rotate(const real &angle)
    {
        return vector(real(x * cos(angle) - y * sin(angle)), real(x * sin(angle) + y * cos(angle)));
    }
    point point::rotate(const real &angle, const point &center = {})
    {
        return point(real(center.x + (x - center.x) * cos(angle) - (y - center.y) * sin(angle)), real(center.y + (x - center.x) * sin(angle) + (y - center.y) * cos(angle)));
    }
    std::vector<point> convex_hull(std::vector<point> points)
    {
        std::sort(points.begin(), points.end(), [](const point &a, const point &b)
                  { return a.x < b.x || (a.x == b.x && a.y < b.y); });
        std::vector<point> hull;
        for (const auto &p : points)
        {
            while (hull.size() >= 2 && ((hull.back() - hull[hull.size() - 2]) ^ (p - hull.back())) < 0.0)
                hull.pop_back();
            hull.emplace_back(p);
        }
        auto t(hull.size() + 1);
        for (int i = points.size() - 2; i >= 0; --i)
        {
            while (hull.size() >= t && ((hull.back() - hull[hull.size() - 2]) ^ (points[i] - hull.back())) < 0.0)
                hull.pop_back();
            hull.emplace_back(points[i]);
        }
        hull.pop_back();
        return hull;
    }
    real perimeter(const std::vector<point> &points)
    {
        real ans(0.0);
        for (std::size_t i = 1; i < points.size(); ++i)
            ans += distance(points[i - 1], points[i]);
        ans += distance(points.back(), points[0]);
        return ans;
    }
}
