#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <istream>
#include <complex>

using namespace std;

struct Point
{
    double x, y;
    Point (double x = 0, double y = 0):x(x),y(y)
    {
    }
};
typedef Point Vector;

struct Car
{
    Point center;
    Vector Direction;
    int rd;
    Car(Point center=Point(0,0),Vector Direction=Point(0,0)):center(center),Direction(Direction)
    {
    }
    double acceleration=0;
};

Vector operator + (Vector A, Vector B)
{
    return Vector(A.x+B.x,A.y+B.y);
}
Vector operator - (Vector A, Vector B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator * (Vector A, double p)
{
    return Vector(A.x*p,A.y*p);
}
Vector operator / (Vector A, double p)
{
    return Vector(A.x/p,A.y/p);
}
bool operator < (const Point &a, const Point &b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double Dot(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y;
}
double Length(Vector A)
{
    return sqrt(Dot(A,A));
}
double Angle(Vector A, Vector B)
{
    return acos(Dot(A,B))/Length(A)/Length(B);
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
double Area2(Point A, Point B, Point C)
{
    return Cross(B-A, C-A);
}

Vector Rotate(Vector A, double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
// please make sure its not a zero vector!
Vector Normal(Vector A)
{
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
Vector Format(const Vector &A)
{
    double L=Length(A);
    return Vector(A.x/L,A.y/L);
}

const double eps = 1e-10;
int dcmp(double x)
{
    if(fabs(x) < eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}

bool operator == (const Point &a, const Point &b)
{
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
Point read_point()
{
    double x, y;
    cin >> x >> y;
    return Vector(x, y);
}
//
Point GetLineIntersection (Point P, Vector v, Point Q, Vector w)
{
    Vector u=P-Q;
    double t = Cross(w,u)/Cross(v,w);
    return P+v*t;
}

double DistanceToLine (Point P, Point A, Point B)
{
    Vector v1 = B-A,v2=P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}
double DistanceToSegment (Point P, Point A, Point B)
{
    if (A==B)
        return Length(P-A);
    Vector v1=B-A,v2=P-A,v3=P-B;
    if(dcmp(Dot(v1,v2))<0)
        return Length(v2);
    else if(dcmp(Dot(v1,v3))>0)
        return Length(v3);
    else
        return fabs(Cross(v1,v2))/Length(v1);
}

Point GetLineProjection(const Point& P, const Point& A, const Point& B)
{
    Vector v = B - A;
    return A + v * (Dot(v, P - A) / Dot(v, v));
}

bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2)
{
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1),
    c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

bool isPointOnSegment(const Point& p, const Point& a1, const Point& a2)
{
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
double PolygonArea(Point* p, int n)
{
    double area = 0;
    for (int i = 1; i < n - 1; i++)
        area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return area / 2;
}

struct Circle
{
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0) :c(c), r(r) {}
    inline Point point(double a)
    {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};
Circle read_circle()
{
    Circle C;
    scanf("%lf%lf%lf", &C.c.x, &C.c.y, &C.r);
    return C;
}

int GetLineCircleIntersection(const Point& A, const Point& B, const Circle& C, vector<Point>& sol)
{
    double d = DistanceToLine(C.c, A, B);
    int mode = dcmp(d - C.r);
    if (mode > 0) return 0;
    Point P = GetLineProjection(C.c, A, B);
    if (mode == 0)
    {
        sol.push_back(P);
        return 1;
    }
    double dist = sqrt(C.r * C.r - d * d);
    Vector v = Format(B - A);
    sol.push_back(P - v * dist);
    sol.push_back(P + v * dist);
    return 2;
}

int GetCircleCircleIntersection (Circle C1, Circle C2, vector<Point>& sol)
{
    if (C1.r < C2.r) swap(C1, C2);
    double D = Length(C1.c - C2.c);
    if (dcmp(D) == 0)
        return dcmp(C1.r - C2.r) == 0 ? -1 : 0;
    if (dcmp(C1.r + C2.r - D) < 0) return 0;
    if (dcmp(fabs(C1.r - C2.r) - D) > 0) return 0;

    double d1 = ((C1.r * C1.r - C2.r * C2.r) / D + D) / 2;
    double x = sqrt(C1.r * C1.r - d1 * d1);
    Point O = C1.c + Format(C2.c - C1.c) * d1;
    Point P1 = O + Normal(O - C2.c) * x, P2 = O - Normal(O - C2.c) * x;
    sol.push_back(P1);
    if (P1 == P2) return 1;
    sol.push_back(P2);
    return 2;
}

inline int GetTangents (const Point P, const Circle C, vector<Point>& v)
{
    Vector u = C.c - P;
    double dist = Length(u);
    int mode = dcmp(dist - C.r);
    if (mode < 0) return 0;
    if (mode == 0)
    {
        v.push_back(P + Normal(u));
        return 1;
    }
    double x = sqrt(dist * dist - C.r * C.r);
    Circle C2(P, x);
    return GetCircleCircleIntersection(C, C2, v);
}

double site_x[20] =
    {
        0.00,
        151.17,
        371.11,
        0.00,
        151.17,
        371.11,
        0.00,
        151.17,
        371.11,
        0.00,
        151.17,
        371.11,
        0.00,
        151.17,
        251.26,
        0.00,
        151.17
    };
double site_y[20] =
    {
        295.19,
        295.19 ,
        295.19 ,
        224.14 ,
        224.14 ,
        224.14 ,
        170.97 ,
        170.97 ,
        170.97 ,
        107.43 ,
        107.43 ,
        107.43 ,
        48.89 ,
        48.89 ,
        48.89 ,
        0.00 ,
        0.00
    };
const int LEN_OF_SITES = 17;
// from A to Q, 17 points in total

struct Road
{
    int start;
    int end;
    Car first_car;

    Road(int start, int end):start(start),end(end)
    {
    }
};

Point sites[20];
Car cs[1005];

Road roads[33] =
    {
        Road(2, 1),
        Road(1, 0),
        Road(3, 4),
        Road(4, 5),
        Road(6, 7),
        Road(7, 8),
        Road(8, 7),
        Road(7, 6),
        Road(9, 10),
        Road(10, 11),
        Road(11, 10),
        Road(10, 9),
        Road(12, 13),
        Road(13, 14),
        Road(15, 16),
        Road(0, 3),
        Road(3, 6),
        Road(1, 4),
        Road(4, 7),
        Road(7, 10),
        Road(10, 13),
        Road(13, 16),
        Road(16, 13),
        Road(13, 10),
        Road(10, 7),
        Road(7, 4),
        Road(4, 1),
        Road(15, 12),
        Road(2, 5),
        Road(5, 8),
        Road(8, 11),
        Road(16, 14),
        Road(14, 11)
    };

const double UPPER = 295.59;
const double LOWER = 0.00;
const double LEFT = 0.00;
const double RIGHT = 371.11;
const double SEP = 151.17;
const double SEP2 = 107.43;

const double CAR_WIDTH = 1.6;
const double CAR_LENGTH = 4.8;

const Vector TO_UP = Vector(0, 1);
const Vector TO_DOWN = Vector(0, -1);
const Vector TO_LEFT = Vector(-1, 0);
const Vector TO_RIGHT = Vector(1, 0);

bool is_same_dir(Vector a, Vector b)
{
    if(Dot(a,b)==Length(a)*Length(b))
    {
        return true;
    }
    return false;
}

bool is_out(Car vehicle)
{
    // bool c1 = (vehicle.center.y == UPPER && vehicle.center.x >= LEFT && vehicle.center.x <= RIGHT);
    // bool c2 = (vehicle.center.y == LOWER && vehicle.center.x >= LEFT && vehicle.center.x <= SEP);
    // bool c3 = (vehicle.center.x >= SEP && vehicle.center.x <= RIGHT && vehicle.center.y < 0.49 * vehicle.center.x - 73.8);
    // bool c4 = (vehicle.center.x == LEFT && vehicle.center.y >= LOWER && vehicle.center.y <= UPPER);
    // bool c5 = (vehicle.center.x == RIGHT && vehicle.center.y >= SEP2 && vehicle.center.y <= UPPER);
    bool c1 = (vehicle.center.y >= UPPER && is_same_dir(vehicle.Direction,TO_UP));
    bool c2 = (vehicle.center.y <= LOWER && is_same_dir(vehicle.Direction,TO_DOWN));
    bool c3 = (vehicle.center.x >= SEP && vehicle.center.x <= RIGHT && vehicle.center.y < 0.49 * vehicle.center.x - 73.8 && is_same_dir(vehicle.Direction,TO_RIGHT));
    bool c4 = (vehicle.center.x <= LEFT && is_same_dir(vehicle.Direction,TO_LEFT));
    bool c5 = (vehicle.center.x >= RIGHT && is_same_dir(vehicle.Direction,TO_RIGHT));
    return (c1 || c2 || c3 || c4 || c5);
}

/*
将每个路段的车辆从前到后依次排序，组成一个队列
队列中的元素为 Car, 每个元素需要有一个前驱 prev 与后继 next, 还有 Car 本身的属性, 以及到达下一个路口的预计花费时间 t
每隔1秒更新一次数据
*/

Car get_first(int rd_number)
{

}// 找到该路段最靠前的一辆车

int get_num(int rd_number)
{

}// 输出该路段有多少辆车

bool get_to_intersection(Car cr)
{

}// 判断车辆是否到达路口


// 1s update 一次
void update()
{
    // 从 get_first(...) 从前往后更新
        // 假如自己不是 prev
            // 假如 prev 需要减速
                // 根据公式1计算该车的相应最大减速度，并把所有与该车有关的状态更新
            // 假如 prev 正常行驶
                // 计算 t 并判断自己是否需要减速
                    // 假如需要减速, 更新减速度为公式2
        // 假如自己是 prev
            // 随机数看转什么弯（在允许的车向范围内，且不准掉头）
                // 小转弯直接转，添加到另一个路段队列的末尾
                // 判断自己是否需要减速
                    // 需要
                        // 以最大减速度减速即可
                        // 等待绿灯
                        // 绿灯亮后以最大加速度进行下面的操作
                    // 不需要：正常更新
                        // 假如在 1s 内能到达路口(get_to_intersection), 正常转弯并进入另一条路段队列末尾


}

/*
引入智能路灯后：
1. 刹车距离约为 16m，即路口必须 lidar 全覆盖
2. 对于路段中没有 lidar 覆盖的车辆，按照匀速行驶
3. wifi 分配按照二分图匹配算法来
*/











int main()
{
    // Point test=Point(1.5,2.5);
    // cout << dcmp(-0.1) << endl;
    // cout << dcmp(1e-11) << endl;
    // cout << test.x << " " << test.y << endl;
    // Point new_test = read_point();
    // cout << new_test.x << endl;

    for(int i = 0; i < LEN_OF_SITES;i++)
    {
        sites[i] = Point(site_x[i], site_y[i]);
    }

    // for (int i = 0; i < LEN_OF_SITES;i++)
    // {
    //     cout <<char(65+i)<<"\t"<< sites[i].x << "\t" << sites[i].y << endl;
    // }

    Car test(sites[14],Point(3.3,0));
    // cout << test.center.x << endl
    //      << test.center.y << endl
    //      << test.Direction.x << endl
    //      << test.Direction.y << endl;
    // cout << is_out(test);
    cout << is_out(test) << endl;
    // cout << is_same_dir(Vector(1, 0), Vector(9, 0));


    return 0;
}