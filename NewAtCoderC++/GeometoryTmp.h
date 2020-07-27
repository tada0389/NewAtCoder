//#include <iostream>
//#include <complex>
//#include <vector>
//#include <algorithm>
//#include <functional>
//#include <iomanip>
//
//using namespace std;
//
//template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
//template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }
//
//// 実数
//using Real = double;
//// 点
//using Point = complex<Real>;
//const Real EPS = 1e-10, PI = acos(-1);
//
//// 実数同士の比較
//inline bool eq(Real a, Real b) { return fabs(b - a) < EPS; }
//
//Point operator*(const Point& p, const Real& d) {
//    return Point(real(p) * d, imag(p) * d);
//}
//
//// 点の入力
//istream& operator>>(istream& is, Point& p) {
//    Real a, b;
//    is >> a >> b;
//    p = Point(a, b);
//    return is;
//}
//
////// 点の出力
////ostream &operator<<(ostream &os, Point &p) {
////  os << fixed << setprecision(10) << p.real() << " " << p.imag();
////}
//
//// 点 p を反時計回りに theta 回転
//Point rotate(Real theta, const Point& p) {
//    return Point(cos(theta) * p.real() - sin(theta) * p.imag(), sin(theta) * p.real() + cos(theta) * p.imag());
//}
//
//// ラジアンを度数に変換
//Real radian_to_degree(Real r) {
//    return (r * 180.0 / PI);
//}
//
//// 度数をラジアンに変換
//Real degree_to_radian(Real d) {
//    return (d * PI / 180.0);
//}
//
//// a-b-c の角度のうち小さい方を返す
//Real get_angle(const Point& a, const Point& b, const Point& c) {
//    const Point v(b - a), w(c - a);
//    Real alpha = atan2(v.imag(), v.real()), beta = atan2(w.imag(), w.real());
//    if (alpha > beta) swap(alpha, beta);
//    Real theta = (beta - alpha);
//    return min(theta, 2 * acos(-1) - theta);
//}
//
//// ソート x座標が小さい順に並べる x座標が同じならy座標が小さい順
//namespace std {
//    bool operator<(const Point& a, const Point& b) {
//        return !eq(a.real(), b.real()) ? a.real() < b.real() : a.imag() < b.imag();
//    }
//}
//
//// 2点を通る直線
//struct Line {
//    Point a, b;
//
//    Line() = default;
//
//    Line(Point a, Point b) : a(a), b(b) {}
//
//    Line(Real A, Real B, Real C) // Ax + By = C
//    {
//        if (eq(A, 0)) a = Point(0, C / B), b = Point(1, C / B);
//        else if (eq(B, 0)) b = Point(C / A, 0), b = Point(C / A, 1);
//        else a = Point(0, C / B), b = Point(C / A, 0);
//    }
//
//    friend ostream& operator<<(ostream& os, Line& p) {
//        return os << p.a << " to " << p.b;
//    }
//
//    friend istream& operator>>(istream& is, Line& a) {
//        return is >> a.a >> a.b;
//    }
//};
//
//// 2点を結ぶ線分
//struct Segment : Line {
//    Segment() = default;
//    Segment(Point a, Point b) : Line(a, b) {}
//};
//
//
//// 円
//struct Circle {
//    // 中心
//    Point p;
//    // 半径
//    Real r;
//
//    Circle() = default;
//
//    Circle(Point p, Real r) : p(p), r(r) {}
//};
//
//// 点集合
//using Points = vector< Point >;
//// ポリゴン 反時計回り
//using Polygon = vector< Point >;   // 注意!! 凸多角形は反時計回りに与える.(保証されない場合は面積が負なら reverse をかける)
//// 線分集合
//using Segments = vector< Segment >;
//// 直線集合
//using Lines = vector< Line >;
//// 円集合
//using Circles = vector< Circle >;
//
//// 外積
//Real cross(const Point& a, const Point& b) {
//    return real(a) * imag(b) - imag(a) * real(b);
//}
//
//// 内積
//Real dot(const Point& a, const Point& b) {
//    return real(a) * real(b) + imag(a) * imag(b);
//}
//
//// 点の回転方向
////          +1
////          
////  +2   a   0   b  -2
////
////          -1
//// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C&lang=jp
//int ccw(const Point& a, Point b, Point c) {
//    b = b - a, c = c - a;
//    if (cross(b, c) > EPS) return +1;  // "COUNTER_CLOCKWISE"
//    if (cross(b, c) < -EPS) return -1; // "CLOCKWISE"
//    if (dot(b, c) < 0) return +2;      // "ONLINE_BACK"
//    if (norm(b) < norm(c)) return -2;  // "ONLINE_FRONT"
//    return 0;                         // "ON_SEGMENT"
//}
//
//// 線分同士の交差判定
//// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
//bool intersect(const Segment& s, const Segment& t) {
//    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
//}
//
//Real CalcDist(const Segment& s, const Point& p) {
//    double t = dot(s.b - s.a, p - s.a) / norm(s.b - s.a);
//    Point c = s.a + (s.b - s.a) * t;
//    Real res = 1000000.0;
//    if (t > -EPS && t < 1.0 + EPS) return sqrt(norm(p - c));
//    chmin(res, sqrt(norm(p - s.b)));
//    chmin(res, sqrt(norm(p - s.a)));
//    return res;
//}
//
//int main() {
//
//    int n;
//    cin >> n;
//
//    Polygon polygon;
//    for (int i = 0; i < n; ++i) {
//        Point p;
//        cin >> p;
//        polygon.emplace_back(p);
//    }
//
//    int q;
//    cin >> q;
//    vector<int> ans(q, 2);
//    for (int i = 0; i < q; ++i) {
//        Point p;
//        cin >> p;
//
//        // 面積求めて負のものがあったら外
//        // 0のものがあったら洗浄
//
//        for (int j = 0; j < n; ++j) {
//            Real volume = cross(polygon[j] - p, polygon[(j + 1) % n] - p);
//
//            if (volume < -EPS) {
//                ans[i] = 0;
//                break;
//            }
//            else if (abs(volume) < EPS) {
//                if (ccw(polygon[j], polygon[(j + 1) % n], p) == 0) ans[i] = 1;
//                else ans[i] = 0;
//                break;
//            }
//        }
//    }
//
//    for (auto res : ans) cout << res << endl;
//
//    //cout << fixed << setprecision(1) << ans << endl;
//}
