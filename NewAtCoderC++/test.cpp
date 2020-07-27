#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

// 実数
using Real = double;
// 点
using Point = complex<Real>;
const Real EPS = 1e-10, PI = acos(-1);

// 実数同士の比較
inline bool eq(Real a, Real b) { return fabs(b - a) < EPS; }

Point operator*(const Point& p, const Real& d) {
    return Point(real(p) * d, imag(p) * d);
}

// 点の入力
istream& operator>>(istream& is, Point& p) {
    Real a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
}

//// 点の出力
//ostream &operator<<(ostream &os, Point &p) {
//  os << fixed << setprecision(10) << p.real() << " " << p.imag();
//}

// 点 p を反時計回りに theta 回転
Point rotate(Real theta, const Point& p) {
    return Point(cos(theta) * p.real() - sin(theta) * p.imag(), sin(theta) * p.real() + cos(theta) * p.imag());
}

// ラジアンを度数に変換
Real radian_to_degree(Real r) {
    return (r * 180.0 / PI);
}

// 度数をラジアンに変換
Real degree_to_radian(Real d) {
    return (d * PI / 180.0);
}

// a-b-c の角度のうち小さい方を返す
Real get_angle(const Point& a, const Point& b, const Point& c) {
    const Point v(b - a), w(c - a);
    Real alpha = atan2(v.imag(), v.real()), beta = atan2(w.imag(), w.real());
    if (alpha > beta) swap(alpha, beta);
    Real theta = (beta - alpha);
    return min(theta, 2 * acos(-1) - theta);
}

// ソート x座標が小さい順に並べる x座標が同じならy座標が小さい順
namespace std {
    bool operator<(const Point& a, const Point& b) {
        return !eq(a.real(), b.real()) ? a.real() < b.real() : a.imag() < b.imag();
    }
}

// 2点を通る直線
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

// 2点を結ぶ線分
struct Segment : Line {
    Segment() = default;
    Segment(Point a, Point b) : Line(a, b) {}
};


// 円
struct Circle {
    // 中心
    Point p;
    // 半径
    Real r;

    Circle() = default;

    Circle(Point p, Real r) : p(p), r(r) {}
};

// 点集合
using Points = vector< Point >;
// ポリゴン 反時計回り
using Polygon = vector< Point >;   // 注意!! 凸多角形は反時計回りに与える.(保証されない場合は面積が負なら reverse をかける)
// 線分集合
using Segments = vector< Segment >;
// 直線集合
using Lines = vector< Line >;
// 円集合
using Circles = vector< Circle >;

// 外積
Real cross(const Point& a, const Point& b) {
    return real(a) * imag(b) - imag(a) * real(b);
}

// 内積
Real dot(const Point& a, const Point& b) {
    return real(a) * real(b) + imag(a) * imag(b);
}

// 点の回転方向
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

// 線分同士の交差判定
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

        //　辺上にあるか
        if (eq(cross(a, b), 0) && dot(a, b) < EPS) return 1;
        // 交わっているか
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

    // 下側凸包を作成
    for (int i = 0; i < n; ++i) {
        // 凸じゃなくなった
        while (k >= 2 && cross(qs[k - 1] - qs[k - 2], points[i] - qs[k - 2]) < -EPS) --k;
        qs[k++] = points[i];
    }

    // 上側凸包を作成
    for (int i = n - 2, tmp = k; i >= 0; --i) {
        while (k > tmp && cross(qs[k - 1] - qs[k - 2], points[i] - qs[k - 2]) < -EPS) --k;
        qs[k++] = points[i];
    }

    // 作った
    qs.resize(k - 1);
    return qs;
}

Real CalcDist(vector<Segment>& a, vector<Segment>& b) {

    Real ret = 1000000.0;

    // 線分同士の距離
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
            // ここから線分を求める
            stars[i][0] = Segment(points[0], points[2]);
            stars[i][1] = Segment(points[0], points[3]);
            stars[i][2] = Segment(points[1], points[4]);
            stars[i][3] = Segment(points[1], points[3]);
            stars[i][4] = Segment(points[2], points[4]);
        }

        // 星mから星lに移動するのに必要な距離
        // n <= 100

        // 各星同士の距離を求めてダイクストラでよさそう

        vector<vector<Real>> dist(n, vector<Real>(n, 0.0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                // それぞれの辺からそれぞれの辺への最短距離
                Real d = CalcDist(stars[i], stars[j]);
                dist[i][j] = dist[j][i] = d;
            }
        }

        // ワーシャルフロイドでいいか
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