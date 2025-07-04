const long double EPS = 1e-10;
const long double PI = acos(-1);

static const int CCW_COUNTER_CLOCKWISE = 1;
static const int CCW_CLOCKWISE = -1;
static const int CCW_ONLINE_BACK = 2;
static const int CCW_ONLINE_FRONT = -2;
static const int CCW_ON_SEGMENT = 0;

static const int ICC_SEPARATE = 4;
static const int ICC_CIRCUMSCRIBE = 3;
static const int ICC_INTERSECT = 2;
static const int ICC_INSCRIBE = 1;
static const int ICC_CONTAIN = 0;

struct Real {
    long double value;

    Real(long double value = 0) : value(value) {}
    Real(const Real& rhs) {
        value = rhs.value;
    }

    Real operator+(const Real& rhs) const {
        return Real(value + rhs.value);
    }
    Real& operator+=(const Real& rhs) {
        return value += rhs.value, *this;
    }
    Real operator-(const Real& rhs) const {
        return Real(value - rhs.value);
    }
    Real& operator-=(const Real& rhs) {
        return value -= rhs.value, *this;
    }
    Real operator*(const Real& rhs) const {
        return Real(value * rhs.value);
    }
    Real& operator*=(const Real& rhs) {
        return value *= rhs.value, *this;
    }
    Real operator/(const Real& rhs) const {
        return Real(value / rhs.value);
    }
    Real& operator/=(const Real& rhs) {
        return value /= rhs.value, *this;
    }
    Real operator-() const {
        return Real(-value);
    }
    Real& operator++() {
        return ++value, *this;
    }
    Real& operator--() {
        return --value, *this;
    }
    Real operator++(int) {
        Real tmp(value);
        return ++value, tmp;
    }
    Real operator--(int) {
        Real tmp(value);
        return --value, tmp;
    }
    bool operator==(const Real& rhs) const {
        return fabs(value - rhs.value) < EPS;
    }
    bool operator!=(const Real& rhs) const {
        return !(*this == rhs);
    }
    bool operator<(const Real& rhs) const {
        return (*this == rhs) ? false : value < rhs.value;
    }
    bool operator>(const Real& rhs) const {
        return (*this == rhs) ? false : value > rhs.value;
    }
    bool operator<=(const Real& rhs) const {
        return (*this == rhs) ? true : value < rhs.value;
    }
    bool operator>=(const Real& rhs) const {
        return (*this == rhs) ? true : value > rhs.value;
    }
    template <class T>
    explicit operator T() const {
        return static_cast<T>(value);
    }

    friend istream& operator>>(istream& is, Real& rhs) {
        is >> rhs.value;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Real& rhs) {
        os << rhs.value;
        return os;
    }

    friend Real pow(const Real& n, const Real& p) {
        return pow(n.value, p.value);
    }
    friend Real pow(Real n, intmax_t p) {
        Real ret = 1;
        for (; p > 0; p >>= 1) {
            if (p & 1) ret *= n;
            n *= n;
        }
        return ret;
    }
    friend Real abs(const Real& rhs) {
        return abs(rhs.value);
    }
    friend Real sin(const Real& rhs) {
        return sin(rhs.value);
    }
    friend Real cos(const Real& rhs) {
        return cos(rhs.value);
    }
    friend Real tan(const Real& rhs) {
        return tan(rhs.value);
    }
    friend Real asin(const Real& rhs) {
        return asin(rhs.value);
    }
    friend Real acos(const Real& rhs) {
        return acos(rhs.value);
    }
    friend Real atan(const Real& rhs) {
        return atan(rhs.value);
    }
    friend Real atan2(const Real& lhs, const Real& rhs) {
        return atan2(lhs.value, rhs.value);
    }
    friend Real sqrt(const Real& rhs) {
        return sqrt(rhs.value);
    }
    friend Real ceil(const Real& rhs) {
        return ceil(rhs.value);
    }
    friend Real floor(const Real& rhs) {
        return floor(rhs.value);
    }
    friend Real round(const Real& rhs) {
        return round(rhs.value);
    }
    friend Real hypot(const Real& x, const Real& y) {
        return hypot(x.value, y.value);
    }
    friend Real hypot(const Real& x, const Real& y, const Real& z) {
        return hypot(x.value, y.value, z.value);
    }
    friend bool isnan(const Real& rhs) {
        return isnan(rhs.value);
    }
};

using real_t = Real;
real_t operator""_r(long double value) {
    return value;
};

struct Point {
    real_t x, y;

    explicit Point(real_t x = 0, real_t y = 0) : x(x), y(y) {}

    static const Point null;

    bool isnull(const Point& p1) const {
        return isnan(p1.x) && isnan(p1.y);
    }
    Point operator+(const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(const Point& rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    Point operator*(const real_t& rhs) const {
        return Point(x * rhs, y * rhs);
    }
    Point operator/(const real_t& rhs) const {
        return Point(x / rhs, y / rhs);
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    bool operator==(const Point& rhs) const {
        return (x == rhs.x && y == rhs.y) || (isnull(*this) && isnull(rhs));
    }
    bool operator!=(const Point& rhs) const {
        return !(*this == rhs);
    }
    bool operator<(const Point& rhs) const {
        return (x == rhs.x) ? y < rhs.y : x < rhs.x;
    }
    bool operator>(const Point& rhs) const {
        return (x == rhs.x) ? y > rhs.y : x > rhs.x;
    }
    bool operator<=(const Point& rhs) const {
        return (*this == rhs) ? true : *this < rhs;
    }
    bool operator>=(const Point& rhs) const {
        return (*this == rhs) ? true : *this > rhs;
    }

    friend istream& operator>>(istream& is, Point& rhs) {
        is >> rhs.x >> rhs.y;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Point& rhs) {
        os << rhs.x << ' ' << rhs.y;
        return os;
    }
};

const Point Point::null = Point(nan(""), nan(""));

using Vector = Point;
using Polygon = vector<Point>;

real_t norm(const Vector& a) {
    return a.x * a.x + a.y * a.y;
}
real_t len(const Vector& a) {
    return sqrt(norm(a));
}
real_t dot(const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y;
}
real_t cross(const Vector& a, const Vector& b) {
    return a.x * b.y - a.y * b.x;
}

struct Segment {
    Point p1, p2;

    explicit Segment(Point p1 = Point(), Point p2 = Point()) : p1(p1), p2(p2) {}

    static const Segment null;

    bool isnull(const Segment& rhs) const {
        return rhs.p1 == Point::null && rhs.p2 == Point::null;
    }
    bool operator==(const Segment& rhs) const {
        return (p1 == rhs.p1 && p2 == rhs.p2) || (isnull(*this) && isnull(rhs));
    }
    bool operator!=(const Segment& rhs) const {
        return !(*this == rhs);
    }

    friend istream& operator>>(istream& is, Segment& rhs) {
        is >> rhs.p1 >> rhs.p2;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Segment& rhs) {
        os << rhs.p1 << ' ' << rhs.p2;
        return os;
    }
};

const Segment Segment::null = Segment(Point::null, Point::null);

using Line = Segment;

struct Circle {
    Point c;
    real_t r;

    Circle(Point c = Point(), real_t r = 0) : c(c), r(r) {}

    bool operator==(const Circle& rhs) const {
        return c == rhs.c && r == rhs.r;
    }
    bool operator!=(const Circle& rhs) const {
        return !(*this == rhs);
    }

    friend istream& operator>>(istream& is, Circle& rhs) {
        is >> rhs.c >> rhs.r;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Circle& rhs) {
        os << rhs.c << ' ' << rhs.r;
        return os;
    }
};

real_t norm(const Segment& s) {
    return norm(s.p1 - s.p2);
}

real_t len(const Segment& s) {
    return len(s.p1 - s.p2);
}

bool isParallel(const Vector& a, const Vector& b) {
    return cross(a, b) == 0.0_r;
}
bool isParallel(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    return isParallel(a1 - a2, b1 - b2);
}
bool isParallel(const Segment& s1, const Segment& s2) {
    return isParallel(s1.p1, s1.p2, s2.p1, s2.p2);
}

bool isOrthogonal(const Vector& a, const Vector& b) {
    return dot(a, b) == 0.0_r;
}
bool isOrthogonal(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
}
bool isOrthogonal(const Segment& s1, const Segment& s2) {
    return isOrthogonal(s1.p1, s1.p2, s2.p1, s2.p2);
}

Point project(const Segment& s, const Point& p) {
    const Vector base = s.p2 - s.p1;
    const Vector hypo = p - s.p1;
    const real_t r = dot(hypo, base) / norm(base);
    return s.p1 + base * r;
}

Point reflect(const Segment& s, const Point& p) {
    return p + (project(s, p) - p) * 2.0;
}

real_t arg(const Vector& p) {
    return atan2(p.y, p.x);
}

Vector polar(real_t r, real_t ang) {
    return Point(r * cos(ang), r * sin(ang));
}

// rotate p1 counterclockwise ang around p0
Point rotate(const Point& p0, const Point& p1, const real_t& ang) {
    Vector a = p1 - p0;
    return p0 + Vector(a.x * cos(ang) - a.y * sin(ang), a.x * sin(ang) + a.y * cos(ang));
}

int ccw(const Point& p0, const Point& p1, const Point& p2);
bool intersectSS(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
bool intersectSS(const Segment& s1, const Segment& s2);
bool intersectSL(const Segment& s, const Line& l);
bool intersectSG(const Segment& s, const Polygon& g);
int intersectCC(Circle c1, Circle c2);
bool intersectLC(const Line& l, const Circle& c);
int intersectSC(const Segment& s, const Circle& c);
real_t getDistancePP(const Point& p1, const Point& p2);
real_t getDistanceLP(const Line& l, const Point& p);
real_t getDistanceSP(const Segment& s, const Point& p);
real_t getDistanceSS(const Segment& s1, const Segment& s2);
Point getcrossPointSS(const Segment& s1, const Segment& s2);
Point getcrossPointLL(const Line& l1, const Line& l2);
Point getcrossPointSL(const Segment& s, const Line& l);
Polygon getcrossPointLC(const Line& l, const Circle& c);
Polygon getcrossPointSC(const Segment& s, const Circle& c);
Polygon getcrossPointCC(const Circle& c1, const Circle& c2);
bool isConvex(const Polygon& g);
int contains(const Polygon& g, const Point& p);
int convexContains(const Polygon& g, const Point& p);
Polygon convexFull(Polygon g, bool ONSEG);
real_t area(const Polygon& g);
void argsort(vector<Point>& ps);

int ccw(const Point& p0, const Point& p1, const Point& p2) {
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if (cross(a, b) > 0.0_r) return CCW_COUNTER_CLOCKWISE;
    if (cross(a, b) < 0.0_r) return CCW_CLOCKWISE;
    if (dot(a, b) < 0.0_r) return CCW_ONLINE_BACK;
    if (norm(a) < norm(b)) return CCW_ONLINE_FRONT;
    return CCW_ON_SEGMENT;
}

bool intersectSS(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    return ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
            ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0;
}

bool intersectSS(const Segment& s1, const Segment& s2) {
    return intersectSS(s1.p1, s1.p2, s2.p1, s2.p2);
}

bool intersectSL(const Segment& s, const Line& l) {
    if (s == Segment::null) return false;
    const real_t x1 = l.p1.x;
    const real_t y1 = l.p1.y;
    const real_t x2 = l.p2.x;
    const real_t y2 = l.p2.y;
    const real_t a = y2 - y1;
    const real_t b = -(x2 - x1);
    const real_t c = -(a * x1 + b * y1);
    const real_t t1 = a * s.p1.x + b * s.p1.y + c;
    const real_t t2 = a * s.p2.x + b * s.p2.y + c;
    return (t1 >= 0 && t2 <= 0) || (t1 <= 0 && t2 >= 0);
}

bool intersectSG(const Segment& s, const Polygon& g) {
    const size_t N = g.size();
    for (size_t i = 0; i < N; ++i) {
        if (intersectSS(Segment(g[i], g[(i + 1) % N]), s)) return true;
    }
    return false;
}

int intersectCC(Circle c1, Circle c2) {
    if (c1.r < c2.r) swap(c1, c2);
    const real_t d = len(c1.c - c2.c);
    const real_t r = c1.r + c2.r;
    if (d == r) return ICC_CIRCUMSCRIBE;
    if (d > r) return ICC_SEPARATE;
    if (d + c2.r == c1.r) return ICC_INSCRIBE;
    if (d + c2.r < c1.r) return ICC_CONTAIN;
    return ICC_INTERSECT;
}

bool intersectLC(const Line& l, const Circle& c) {
    return getDistanceSP(l, c.c) <= c.r;
}

int intersectSC(const Segment& s, const Circle& c) {
    const Point h = project(s, c.c);
    if (norm(h - c.c) - c.r * c.r > 0.0_r) return 0;
    const real_t d1 = getDistancePP(c.c, s.p1);
    const real_t d2 = getDistancePP(c.c, s.p2);
    if (d1 < c.r && d2 < c.r) return 0;
    if ((d1 < c.r && d2 > c.r) || (d1 > c.r && d2 < c.r)) return 1;
    if (dot(s.p1 - h, s.p2 - h) < 0.0_r) return 2;
    return 0;
}

real_t getDistancePP(const Point& p1, const Point& p2) {
    return len(p2 - p1);
}

real_t getDistanceLP(const Line& l, const Point& p) {
    return abs(cross(l.p2 - l.p1, p - l.p1) / len(l.p2 - l.p1));
}

real_t getDistanceSP(const Segment& s, const Point& p) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0_r) return getDistancePP(p, s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0_r) return getDistancePP(p, s.p2);
    return getDistanceLP(s, p);
}

real_t getDistanceSS(const Segment& s1, const Segment& s2) {
    if (intersectSS(s1, s2)) return 0.0;
    const real_t opt1 = getDistanceSP(s1, s2.p1);
    const real_t opt2 = getDistanceSP(s1, s2.p2);
    const real_t opt3 = getDistanceSP(s2, s1.p1);
    const real_t opt4 = getDistanceSP(s2, s1.p2);
    return min({opt1, opt2, opt3, opt4});
}

Point getcrossPointSS(const Segment& s1, const Segment& s2) {
    if (!intersectSS(s1, s2)) return Point::null;
    Vector base = s2.p2 - s2.p1;
    const real_t d1 = abs(cross(base, s1.p1 - s2.p1));
    const real_t d2 = abs(cross(base, s1.p2 - s2.p1));
    const real_t t = d1 / (d1 + d2);
    return s1.p1 + (s1.p2 - s1.p1) * t;
}

Point getcrossPointLL(const Line& l1, const Line& l2) {
    if (isParallel(l1, l2)) return Point::null;
    real_t a = cross(l1.p2 - l1.p1, l2.p2 - l2.p1);
    real_t b = cross(l1.p2 - l1.p1, l1.p2 - l2.p1);
    if (a == 0 && b == 0) return l2.p1;
    return l2.p1 + (l2.p2 - l2.p1) * (b / a);
}

Point getcrossPointSL(const Segment& s, const Line& l) {
    if (!intersectSL(s, l)) {
        return Point::null;
    }
    return getcrossPointLL(s, l);
}

Polygon getcrossPointLC(const Line& l, const Circle& c) {
    Polygon ps;
    const Point pr = project(l, c.c);
    const Vector e = (l.p2 - l.p1) / len(l.p2 - l.p1);
    if (getDistanceLP(l, c.c) == c.r) {
        ps.emplace_back(pr);
        return ps;
    }
    const real_t base = sqrt(c.r * c.r - norm(pr - c.c));
    ps.emplace_back(pr + e * base);
    ps.emplace_back(pr - e * base);
    return ps;
}

Polygon getcrossPointSC(const Segment& s, const Circle& c) {
    const Line l(s);
    Polygon ret = getcrossPointLC(l, c);
    if (intersectSC(s, c) == 2) return ret;
    if (ret.size() > 1) {
        if (dot(l.p1 - ret[0], l.p2 - ret[0]) > 0.0_r) swap(ret[0], ret[1]);
        ret.pop_back();
    }
    return ret;
}

Polygon getcrossPointCC(const Circle& c1, const Circle& c2) {
    Polygon p(2);
    const real_t d = getDistancePP(c1.c, c2.c);
    const real_t a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0_r * c1.r * d));
    const real_t t = arg(c2.c - c1.c);
    p[0] = c1.c + polar(c1.r, t + a);
    p[1] = c1.c + polar(c1.r, t - a);
    return p;
}

bool isConvex(const Polygon& g) {
    const size_t N = g.size();
    for (size_t i = 0; i < N; ++i) {
        const int state = ccw(g[i], g[(i + 1) % N], g[(i + 2) % N]);
        if (state == CCW_CLOCKWISE) return false;
    }
    return true;
}

// OUT:0 ON:1 IN:2
enum { OUT, ON, IN };

int contains(const Polygon& g, const Point& p) {
    const size_t N = g.size();
    bool valid = false;
    for (size_t i = 0; i < N; ++i) {
        Point a = g[i] - p, b = g[(i + 1) % N] - p;
        if (abs(cross(a, b)) == 0.0_r && dot(a, b) <= 0.0_r) return ON;
        if (a.y > b.y) swap(a, b);
        if (a.y <= 0.0_r && 0.0_r < b.y && cross(a, b) > 0.0_r) valid ^= 1;
    }
    return (valid ? IN : OUT);
}

// time complexity: O(log N)
int convexContains(const Polygon& g, const Point& p) {
    const size_t N = g.size();
    const Point G = (g[0] + g[N / 3] + g[2 * N / 3]) / 3.0_r;
    const Vector Gp = p - G;
    size_t l = 0, r = N;
    while (r - l > 1) {
        const size_t m = (l + r) / 2;
        const Vector Gl = g[l] - G;
        const Vector Gm = g[m] - G;
        if (cross(Gl, Gm) > 0.0_r) {
            if (cross(Gl, Gp) >= 0.0_r && cross(Gm, Gp) <= 0.0_r) {
                r = m;
            } else
                l = m;
        } else {
            if (cross(Gl, Gp) <= 0.0_r && cross(Gm, Gp) >= 0.0_r) {
                l = m;
            } else {
                r = m;
            }
        }
    }
    r %= N;
    if (cross(g[l] - p, g[r] - p) < 0.0_r) return OUT;
    if (cross(g[l] - p, g[r] - p) > 0.0_r) return IN;
    return ON;
}

// Counter Clockwise
Polygon convexFull(Polygon g, bool ONSEG) {
    Polygon u, l;
    if (g.size() < 3) return g;
    sort(g.begin(), g.end());
    u.emplace_back(g[0]);
    u.emplace_back(g[1]);
    l.emplace_back(g[g.size() - 1]);
    l.emplace_back(g[g.size() - 2]);

    if (ONSEG) {
        for (int i = 2; i < g.size(); ++i) {
            for (int n = u.size();
                    n >= 2 && ccw(u[n - 2], u[n - 1], g[i]) == CCW_COUNTER_CLOCKWISE; --n) {
                u.pop_back();
            }
            u.emplace_back(g[i]);
        }
        for (int i = g.size() - 3; i >= 0; --i) {
            for (int n = l.size();
                    n >= 2 && ccw(l[n - 2], l[n - 1], g[i]) == CCW_COUNTER_CLOCKWISE; --n) {
                l.pop_back();
            }
            l.emplace_back(g[i]);
        }
    } else {
        for (int i = 2; i < g.size(); ++i) {
            for (int n = u.size();
                    n >= 2 && ccw(u[n - 2], u[n - 1], g[i]) != CCW_CLOCKWISE; --n) {
                u.pop_back();
            }
            u.emplace_back(g[i]);
        }
        for (int i = g.size() - 3; i >= 0; --i) {
            for (int n = l.size();
                    n >= 2 && ccw(l[n - 2], l[n - 1], g[i]) != CCW_CLOCKWISE; --n) {
                l.pop_back();
            }
            l.emplace_back(g[i]);
        }
    }

    reverse(l.begin(), l.end());
    for (int i = u.size() - 2; i >= 1; --i) l.emplace_back(u[i]);

    return l;
}

real_t area(const Polygon& g) {
    const size_t N = g.size();
    real_t res = 0;
    for (size_t i = 0; i < g.size(); ++i) {
        res += cross(g[i], g[(i + 1) % N]) / 2.0;
    }
    return res;
}

// time complexity: expected value O(N)
Circle minimumInclusionCircle(Polygon g) {
    const size_t N = g.size();

    assert(N >= 1);
    if (N == 1) {
        return {g[0], 0.0_r};
    }

    random_device seed_gen;
    mt19937 engine(seed_gen());
    shuffle(g.begin(), g.end(), engine);

    const auto makeCircle3 = [](const Point& a, const Point& b,
                                const Point& c) -> Circle {
        const real_t A = norm(b - c), B = norm(c - a), C = norm(a - b),
                        S = cross(b - a, c - a);
        const Point p =
            (a * (A * (B + C - A)) + b * (B * (C + A - B)) + c * (C * (A + B - C))) /
            (4.0_r * S * S);
        const real_t r2 = getDistancePP(p, a);
        return {p, r2};
    };

    const auto makeCircle2 = [](const Point& a, const Point& b) -> Circle {
        const Point c = (a + b) / 2.0_r;
        const real_t r2 = getDistancePP(a, c);
        return {c, r2};
    };

    const auto inCircle = [](const Point& a, const Circle& c) -> bool {
        return getDistancePP(a, c.c) <= c.r;
    };

    Circle c = makeCircle2(g[0], g[1]);

    for (size_t i = 2; i < N; ++i) {
        if (!inCircle(g[i], c)) {
            c = makeCircle2(g[0], g[i]);
            for (size_t j = 1; j < i; ++j) {
                if (!inCircle(g[j], c)) {
                    c = makeCircle2(g[i], g[j]);
                    for (size_t k = 0; k < j; ++k) {
                        if (!inCircle(g[k], c)) {
                            c = makeCircle3(g[i], g[j], g[k]);
                        }
                    }
                }
            }
        }
    }

    return c;
}

const auto getA = [](Point p) {
    if (p.x >= 0 && p.y >= 0) return 0;
    if (p.y >= 0) return 1;
    if (p.x <= 0) return -2;
    return -1;
};
const auto comp = [](Point a, Point b) {
    if (getA(a) != getA(b)) return getA(a) < getA(b);
    if (a.x == 0 && a.y == 0) return !(b.x == 0 && b.y == 0);
    if (b.x == 0 && b.y == 0) return false;
    return cross(a, b) > 0;
};
void argsort(vector<Point>& ps) {
    sort(ps.begin(), ps.end(), comp);
}