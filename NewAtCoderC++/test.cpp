#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

// ����
using Real = double;
// �_
using Point = complex<Real>;
const Real EPS = 1e-10, PI = acos(-1);

// �������m�̔�r
inline bool eq(Real a, Real b) { return fabs(b - a) < EPS; }

Point operator*(const Point& p, const Real& d) {
    return Point(real(p) * d, imag(p) * d);
}

// �_�̓���
istream& operator>>(istream& is, Point& p) {
    Real a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
}

//// �_�̏o��
//ostream &operator<<(ostream &os, Point &p) {
//  os << fixed << setprecision(10) << p.real() << " " << p.imag();
//}

// �_ p �𔽎��v���� theta ��]
Point rotate(Real theta, const Point& p) {
    return Point(cos(theta) * p.real() - sin(theta) * p.imag(), sin(theta) * p.real() + cos(theta) * p.imag());
}

// ���W�A����x���ɕϊ�
Real radian_to_degree(Real r) {
    return (r * 180.0 / PI);
}

// �x�������W�A���ɕϊ�
Real degree_to_radian(Real d) {
    return (d * PI / 180.0);
}

// a-b-c �̊p�x�̂�������������Ԃ�
Real get_angle(const Point& a, const Point& b, const Point& c) {
    const Point v(b - a), w(c - a);
    Real alpha = atan2(v.imag(), v.real()), beta = atan2(w.imag(), w.real());
    if (alpha > beta) swap(alpha, beta);
    Real theta = (beta - alpha);
    return min(theta, 2 * acos(-1) - theta);
}

// �\�[�g x���W�����������ɕ��ׂ� x���W�������Ȃ�y���W����������
namespace std {
    bool operator<(const Point& a, const Point& b) {
        return !eq(a.real(), b.real()) ? a.real() < b.real() : a.imag() < b.imag();
    }
}

// 2�_��ʂ钼��
struct Line {
    Point a, b;

    Line() = default;

    Line(Point a, Point b) : a(a), b(b) {}

    Line(Real A, Real B, Real C) // Ax + By = C
    {
        if (eq(A, 0)) a = Point(0, C / B), b = Point(1, C / B);
        else if (eq(B, 0)) b = Point(C / A, 0), b = Point(C / A, 1);
        else a = Point(0, C / B), b = Point(C / A, 0);
    }

    friend ostream& operator<<(ostream& os, Line& p) {
        return os << p.a << " to " << p.b;
    }

    friend istream& operator>>(istream& is, Line& a) {
        return is >> a.a >> a.b;
    }
};

// 2�_�����Ԑ���
struct Segment : Line {
    Segment() = default;
    Segment(Point a, Point b) : Line(a, b) {}
};


// �~
struct Circle {
    // ���S
    Point p;
    // ���a
    Real r;

    Circle() = default;

    Circle(Point p, Real r) : p(p), r(r) {}
};

// �_�W��
using Points = vector< Point >;
// �|���S�� �����v���
using Polygon = vector< Point >;   // ����!! �ʑ��p�`�͔����v���ɗ^����.(�ۏ؂���Ȃ��ꍇ�͖ʐς����Ȃ� reverse ��������)
// �����W��
using Segments = vector< Segment >;
// �����W��
using Lines = vector< Line >;
// �~�W��
using Circles = vector< Circle >;

// �O��
Real cross(const Point& a, const Point& b) {
    return real(a) * imag(b) - imag(a) * real(b);
}

// ����
Real dot(const Point& a, const Point& b) {
    return real(a) * real(b) + imag(a) * imag(b);
}

// �_�̉�]����
//          +1
//          
//  +2   a   0   b  -2
//
//          -1
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C&lang=jp
int ccw(const Point& a, Point b, Point c) {
    b = b - a, c = c - a;
    if (cross(b, c) > EPS) return +1;  // "COUNTER_CLOCKWISE"
    if (cross(b, c) < -EPS) return -1; // "CLOCKWISE"
    if (dot(b, c) < 0) return +2;      // "ONLINE_BACK"
    if (norm(b) < norm(c)) return -2;  // "ONLINE_FRONT"
    return 0;                         // "ON_SEGMENT"
}

// �������m�̌�������
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
bool intersect(const Segment& s, const Segment& t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

Real CalcDist(const Segment& s, const Point& p) {
    double t = dot(s.b - s.a, p - s.a) / norm(s.b - s.a);
    Point c = s.a + (s.b - s.a) * t;
    Real res = 1000000.0;
    if (t > -EPS && t < 1.0 + EPS) return sqrt(norm(p - c));
    chmin(res, sqrt(norm(p - s.b)));
    chmin(res, sqrt(norm(p - s.a)));
    return res;
}

Real CalcDist(const Segment& a, const Segment& b) {
    return min({CalcDist(a, b.a), CalcDist(a, b.b), CalcDist(b, a.a), CalcDist(b, a.b)});
}

int InPolygon(Point& p, const Polygon& pol) {
    int n = pol.size();

    bool is_in = false;
    for(int i = 0; i < n; ++i) {
        Point a = pol[i] - p;
        Point b = pol[(i + 1) % n] - p;

        //�@�ӏ�ɂ��邩
        if (eq(cross(a, b), 0) && dot(a, b) < EPS) return 1;
        // ������Ă��邩
        if (a.imag() < b.imag()) swap(a, b);
        if (a.imag() > EPS && b.imag() < EPS && cross(a, b) > EPS) is_in = !is_in;
    }

    return (is_in) ? 2 : 0;
}

bool CmpX(const Point& lhs, const Point& rhs) {
    if (lhs.real() != rhs.real()) return lhs.real() < rhs.real();
    return lhs.imag() < rhs.imag();
}

Polygon ConvexHull(vector<Point>& points) {
    int n = points.size();
    sort(points.begin(), points.end(), CmpX);

    int k = 0;
    vector<Point> qs(n * 2);

    // �����ʕ���쐬
    for (int i = 0; i < n; ++i) {
        // �ʂ���Ȃ��Ȃ���
        while (k >= 2 && cross(qs[k - 1] - qs[k - 2], points[i] - qs[k - 2]) < -EPS) --k;
        qs[k++] = points[i];
    }

    // �㑤�ʕ���쐬
    for (int i = n - 2, tmp = k; i >= 0; --i) {
        while (k > tmp && cross(qs[k - 1] - qs[k - 2], points[i] - qs[k - 2]) < -EPS) --k;
        qs[k++] = points[i];
    }

    // �����
    qs.resize(k - 1);
    return qs;
}

Real CalcDist(vector<Segment>& a, vector<Segment>& b) {

    Real ret = 1000000.0;

    // �������m�̋���
    for (auto& segA : a) {
        for (auto& segB : b) {
            if (intersect(segA, segB)) return 0.0;
            chmin(ret, CalcDist(segA, segB));
        }
    }

    return ret;
}


int main() {

    vector<Real> ans;
    while (true) {
        int n, m, l;
        cin >> n >> m >> l;

        if (n == 0 && m == 0 && l == 0) break;

        vector<vector<Segment>> stars(n, vector<Segment>(5));
        for (int i = 0; i < n; ++i) {
            Real x, y, a, r;
            cin >> x >> y >> a >> r;
            vector<Point> points(5);
            for (int j = 0; j < 5; ++j) {
                Real angle = acos(-1) * (90 + 72 * j + a) / 180.0;
                Real px = x + r * cos(angle);
                Real py = y + r * sin(angle);
                points[j] = Point(px, py);
            }
            // ����������������߂�
            stars[i][0] = Segment(points[0], points[2]);
            stars[i][1] = Segment(points[0], points[3]);
            stars[i][2] = Segment(points[1], points[4]);
            stars[i][3] = Segment(points[1], points[3]);
            stars[i][4] = Segment(points[2], points[4]);
        }

        // ��m���琯l�Ɉړ�����̂ɕK�v�ȋ���
        // n <= 100

        // �e�����m�̋��������߂ă_�C�N�X�g���ł悳����

        vector<vector<Real>> dist(n, vector<Real>(n, 0.0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                // ���ꂼ��̕ӂ��炻�ꂼ��̕ӂւ̍ŒZ����
                Real d = CalcDist(stars[i], stars[j]);
                dist[i][j] = dist[j][i] = d;
            }
        }

        // ���[�V�����t���C�h�ł�����
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        ans.emplace_back(dist[m - 1][l - 1]);
    }

    for (auto res : ans) cout << fixed << setprecision(8) << res << endl;
}