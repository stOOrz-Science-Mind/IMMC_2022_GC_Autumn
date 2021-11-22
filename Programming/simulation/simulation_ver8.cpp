#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <istream>
#include <complex>
#include <ctime>
using namespace std;
const double max_acceleration = 7.0;//�����ٶȣ��ľ���ֵ��
double dealt_time; // �Ѿ�������ʱ�䳤��
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
    int rd;//road
    double acceleration=0;//���ٶ�
    Car(Point center=Point(0,0),Vector Direction=Point(0,0)):center(center),Direction(Direction)
    {
    }
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
//double operator % (double a, double b) { // ������С��ȡ������
//	double ans = 0;
//	while(b*ans<=a) ans = ans + 1;
//	return (a - b * (ans-1));
//}
double mod (double a, double b) {
	double ans = 0.0;
	while (b * ans <= a) ans = ans + 1;
	return a - (ans - 1) * b;
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
//cross+area2 �����
Vector Rotate(Vector A, double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
//��ת����
// please make sure its not a zero vector!
Vector Normal(Vector A)//��ת90�㲢��λ��
{
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
Vector Format(const Vector &A)//���㵥λ����
{
    double L=Length(A);
    return Vector(A.x/L,A.y/L);
}

const double eps = 1e-10;//����
int dcmp(double x)
{
    if(fabs(x) < eps)//fabs=abs
        return 0;
    else
        return x < 0 ? -1 : 1;
}

bool operator == (const Point &a, const Point &b)
{
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
Point read_point()//duliu input point
{
    double x, y;
    cin >> x >> y;
    return Vector(x, y);
}
//???
Point GetLineIntersection (Point P, Vector v, Point Q, Vector w)//����ʽ
{
    Vector u=P-Q;
    double t = Cross(w,u)/Cross(v,w);
    return P+v*t;
}
//F*ck CCF
double DistanceToLine (Point P, Point A, Point B)//�㵽ֱ�߾���
{
    Vector v1 = B-A,v2=P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}
double DistanceToSegment (Point P, Point A, Point B)//�㵽�߶ξ���
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

Point GetLineProjection(const Point& P, const Point& A, const Point& B)//ֱ��ͶӰ
{
    Vector v = B - A;
    return A + v * (Dot(v, P - A) / Dot(v, v));
}

bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2)//����
{
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1),
    c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
//FUCKCCF
bool isPointOnSegment(const Point& p, const Point& a1, const Point& a2)//�жϵ����߶���
{
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
double PolygonArea(Point* p, int n)//�����������*pΪ�˵�����
{
    double area = 0;
    for (int i = 1; i < n - 1; i++)
        area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return area / 2;
}

struct Circle//Բ
{
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0) :c(c), r(r) {}
    inline Point point(double a)
    {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};
Circle read_circle()//duliu input
{
    Circle C;
    scanf("%lf%lf%lf", &C.c.x, &C.c.y, &C.r);
    return C;
}
//ccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsbccfsb
int GetLineCircleIntersection(const Point& A, const Point& B, const Circle& C, vector<Point>& sol)//ֱ�ߺ�Բ�Ľ�������
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

int GetCircleCircleIntersection (Circle C1, Circle C2, vector<Point>& sol)//����Բ�Ľ�������
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
//����
inline int GetTangents (const Point P, const Circle C, vector<Point>& v)//����
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

double min_decelarate_dis(double v, double a)
{
	return v * v / a / 2;
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
//��ʿ���
struct Road
{
    int start;
    int end;
    Car first_car;
	double lim_v;
	double width;
    Road(int start, int end):start(start),end(end)
    {
    }
};
//shabiccf
Point sites[20];//��·����
Car cs[1005];//cs=cars

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

bool is_same_dir(Vector a, Vector b)//�ж����������Ƿ�ͬ��
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
int num_of_car;
#define nc num_of_car
/*
将每个路段的车辆从前到后依次排序，组成一个队列
队列中的元素为 Car, 每个元素需要有一个前驱 prev 与后继 next, 还有 Car 本身的属性, 以及到达下一个路口的预计花费时间 t
每隔1秒更新一次数据
*/
double point_dist(Point a,Point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

struct cross
{
	int outrd[6];
	int roadnumber;//��·����
	double red, green; // �˴� red ����Ϊ ���0/2 �ĳ��ߵĺ��
	double initstatus; // initstatus ����Ϊ ���0/2 �ĳ��ߵ�һ���̵�ת��Ƶ�ʱ������ʼʱ���ʱ��
}crosses[44];

int get_num(int rd_number)
{
	int cnt=0;
	for(int i=1;i<=nc;i++)
	{
		if(isPointOnSegment(cs[i].center,sites[roads[i].start],sites[roads[i].end])) cnt++;
	}
	return cnt;
}// 输出该路段有多少辆车

bool red_or_green (double time, int cross, int sta) { // 0=red 1=green
	double cyctime = mod(time + crosses[cross].initstatus, crosses[cross].red + crosses[cross].green);
	bool red_02 = (cyctime < crosses[cross].red);
	if ((red_02 + (sta % 2)) == 1) return 0;
	return 1;
}

double car_turning[1009],decelerate_time[1009],accelerate_time[1009];//��¼ÿ��������Ҫ����ʱ��ת�� �Լ���Ҫ����ʱ����ٵ�0
Car get_first_start(int rd_number)
{
	Car nearest;
	if(!get_num(rd_number)) return nearest;
	double minn=998244353.0;
	int mink=114514;
	Vector dir=sites[roads[rd_number].start]-sites[roads[rd_number].end];
	bool flag=0;
	for(int i=1;i<=nc;i++)
	{
		if(isPointOnSegment(cs[i].center,sites[roads[i].start],sites[roads[i].end]))
		{
			if(minn>point_dist(cs[i].center,sites[roads[rd_number].start])&&Dot(dir,cs[i].Direction)>0)
			{
				mink=i;
				minn=point_dist(cs[i].center,sites[roads[rd_number].start]);
				nearest=cs[i];
				flag=1;
			}
		}
	}
	return nearest;
}// 找到该路段最靠前的一辆车

Car get_first_end(int rd_number) {
	Car nearest;
	if(!get_num(rd_number)) {
		return nearest;
	}
	double minn = 998244353.0;
	int mink = 114514;
	Point dir = sites[roads[rd_number].start] - sites[roads[rd_number].end];
	bool flag = 0;
	for(int i = 1; i <= nc; i++) {
		if (isPointOnSegment(cs[i].center, sites[roads[i].start], sites[roads[i].end])) {
			if (minn > point_dist(cs[i].center, sites[roads[rd_number].end]) && Dot(dir,cs[i].Direction) < 0) {
				mink = i;
				minn = point_dist(cs[i].center, sites[roads[rd_number].end]);
				nearest = cs[i];
			}
		}
	}
	return nearest;
} // 找到该路段最靠前的一辆车
#define crossroads GetLineIntersection(roads[i].start, roads[i].end - roads[i].start, roads[j].start, roads[j].end - roads[j].start)
bool get_to_intersection(Car cr) {
	for(int i = 0; i < 33; i++) {
		for(int j = i + 1; j < 33; j++) {
			if(crossroads == cr.center) return 1;
		}
	}
	return 0;
}

//TODO: ����
// 判断车辆是否到达路口
// 0.5s update 一次
//roads 0~16���� 17~30���� 3132б��
struct turn {
	int to_num;
	double turn_time;
};

turn rand_turn(int crossroad_number, int status) { // rand-status=0 ��ͷ rand-status=1 ��ת rand-status=2 ֱ�� rand-status=3 ��ת
	srand(time(0));
	int rand_turn = rand() % crosses[crossroad_number].roadnumber;
	turn to_road;
	to_road.to_num = crosses[crossroad_number].outrd[rand_turn];
	int turnstatus = (rand_turn + 4 - status) % 4;
	if(turnstatus < 2) {
		to_road.turn_time = 5.0;
	} else if (turnstatus == 2) {
		to_road.turn_time = 1.5;
	} else {
		to_road.turn_time = 0.5;
	}
	return to_road;
} //��ת5s ֱ��1.5s ��ת0.5s ��ͷ5s

double max_upspeed(double a, double s, double maxv, int cross) {
	/*
	˼·�����ж��ȼ��ٵ�����ٶ��������ܷ�����
	������У����жϺ�ʱ����
	*/
	double acc_dis = maxv * maxv / a / 2;
	double acc_time = maxv / a;
	double other_time = (s - acc_dis) / maxv;
	double red_time = (crosses[cross].red + crosses[cross].green) - mod(dealt_time + crosses[cross].initstatus, crosses[cross].red + crosses[cross].green);
	if (acc_time + other_time <= red_time) {//��ͨ��
		return maxv;
	}
	double maxv_s = maxv / 2 * (maxv / a + maxv / max_acceleration);
	if (maxv_s <= s) return maxv;
	return sqrt(s * 2 / (1 / a + 1 / max_acceleration));
}

void update() { // 0.5second
	//TODO: how to judge whether a car can pass a traffic light
	//      how to update the variable 'done'
	bool done = 0;

	//TODO: ����
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
	dealt_time = dealt_time + 0.5;
	int crsrd_num, sta;
	for(int i = 0; i < 33; i++) { // across
		for(int j = i + 1; j < 33; j++) { // not across
			if (!isPointOnSegment(crossroads, roads[i].start, roads[i].end) || !isPointOnSegment(crossroads, roads[j].start, roads[j].end)) continue; // �����ڵĽ��㣨����������߶��⣩
			Point dir = sites[roads[i].start]-sites[roads[i].end];
			if(crossroads == roads[i].start) {
				for(int k=1;k<=nc;k++) {
					if(isPointOnSegment(cs[k].center,sites[roads[i].start],sites[roads[i].end])&&Dot(dir,cs[k].Direction)>0&&car_turning[k]==0) { // ׼��ת��
						if(get_to_intersection(cs[k])) {
							if (accelerate_time[i] > 0) {
								cs[i].Direction = cs[i].Direction * (Length(cs[i].Direction) + 0.5 * max_acceleration) / Length(cs[i].Direction);
								accelerate_time[i] = accelerate_time[i] - 0.5;
							}
							for(int z = 0; z < 20; z++) {
								if (sites[z] == crossroads) {
									crsrd_num = z;
									break;
								}
							}
							for(int z=0;z<4;z++) {
								if (i == crosses[crsrd_num].outrd[z]) {
									sta = z;
									break;
								}
							}
							turn Turning = rand_turn(crsrd_num, sta);
							car_turning[k] = Turning.turn_time;
							cs[k].rd = Turning.to_num;
							if (crossroads == sites[roads[cs[k].rd].start]) {
								cs[k].Direction = sites[roads[cs[k].rd].end] - sites[roads[cs[k].rd].start];
							} else {
								cs[k].Direction = sites[roads[cs[k].rd].start] - sites[roads[cs[k].rd].end];
							}
						}
					}
					else if (isPointOnSegment(cs[i].center, sites[roads[i].start], sites[roads[i].end]) && Dot(dir, cs[i].Direction) > 0 && car_turning[i] != 0) {
						car_turning[i] -= 0.5;
						if (car_turning[i] <= 0) {
							accelerate_time[i] = max_upspeed(max_acceleration, Length(roads[cs[i].rd].start - roads[cs[i].rd].end), roads[cs[i].rd].lim_v, crsrd_num);
						}
					}
					else {
						if ( /*��ͨ��*/ 1) { // ���̵���ͨ�� ����ռλ
							cs[k].center = cs[k].center + (cs[k].Direction / 2);
						}
						else { // �޷�ͨ��������
							if (decelerate_time[k]>0) {
								cs[k].Direction = cs[k].Direction * (Length(cs[k].Direction) + max_acceleration) / Length(cs[k].Direction);
							}
							if (point_dist(cs[k].center, sites[roads[i].start]) <= min_decelarate_dis(Length(cs[k].Direction), max_acceleration)) {
								decelerate_time[k] = Length(cs[k].Direction) / max_acceleration;
							}
						}
					}
				}
			}
		}
	}
}

/*
引入智能路灯后：
1. 刹车距离约为 16m，即路口必须 lidar 全覆盖
2. 对于路段中没有 lidar 覆盖的车辆，按照匀速行驶
3. wifi 分配按照二分图匹配算法来
*/

bool is_on_road(Car c)
{
	bool condition1 = ((c.center.y == UPPER) || (c.center.y == 224.14) || (c.center.y == 170.97) || (c.center.y == 107.43)) && (c.center.x >= LEFT) && (c.center.x <= RIGHT);
	bool condition2 = (c.center.y == 48.89) && (c.center.x >= LEFT) && (c.center.x <= 251.26);
	bool condition3 = (c.center.y == 0) && (c.center.x >= LEFT) && (c.center.x <= SEP);
	bool condition4 = (c.center.x == 0) && ((c.center.y >= 170.97 && c.center.y <= UPPER) || (c.center.y >= 0 && c.center.y <= 48.89));
	bool condition5 = (c.center.x == SEP) && c.center.y >= 0 && c.center.y <= UPPER;
	bool condition6 = (c.center.x == RIGHT) && c.center.y >= 107.43 && c.center.y <= UPPER;
	// 一开始把所有车子生成在横平竖直的道路上，到时候再开上去
	return (condition1 || condition2 || condition3 || condition4 || condition5 || condition6);
}

double rand_y[6] = {
	UPPER,
	224.14,
	170.97,
	107.43,
	48.89,
	0.00
};

// 随机生成符合条件的车
double randomly_decide_y(double x)
{

	int opt = 0;
	// if(x==0)
	// {
	// 	int opt = rand() % 2;
	// 	if(opt==0)
	// 	{
	// 		int len = int(UPPER - 170.97) - 2;
	// 		return (rand() % len + 171);
	// 	}
	// 	else if(opt==1)
	// 	{
	// 		int len = int(48.89) - 2;
	// 		return (rand() % len);
	// 	}
	// }
	if(x>=0 && x<=SEP)
	{
		srand(time(0));
		opt = rand() % 6;
	}
	else if(x>SEP && x<=251.26)
	{
		srand(time(0));
		opt = rand() % 5;
	}
	else if(x>251.26 && x<=RIGHT)
	{
		srand(time(0));
		opt = rand() % 4;
	}
	return rand_y[opt];
}

int main()
{
    // Point test=Point(1.5,2.5);
    // cout << dcmp(-0.1) << endl;
    // cout << dcmp(1e-11) << endl;
    // cout << test.x << " " << test.y << endl;
    // Point new_test = read_point();
    // cout << new_test.x << endl;

    for(int i = 0; i < LEN_OF_SITES;i++) {
        sites[i] = Point(site_x[i], site_y[i]);
    }

    // for (int i = 0; i < LEN_OF_SITES;i++)
    // {
    //     cout <<char(65+i)<<"\t"<< sites[i].x << "\t" << sites[i].y << endl;
    // }
	for(int i = 0; i < 3; i++) {
		roads[i].lim_v = 70.0 / 3.6;
	}
	for(int i = 3; i < 33; i++) {
		roads[i].lim_v = 50.0 / 3.6;
	}
    Car test(sites[14], Point(3.3,0));
    // cout << test.center.x << endl
    //      << test.center.y << endl
    //      << test.Direction.x << endl
    //      << test.Direction.y << endl;
    // cout << is_out(test);
    cout << is_out(test) << endl;
    // cout << is_same_dir(Vector(1, 0), Vector(9, 0));

	crosses[1].outrd[0] = 15;
	crosses[1].outrd[1] = 1;
	crosses[1].roadnumber = 2;
	crosses[2].outrd[0] = 1;
	crosses[2].outrd[1] = 17;
	crosses[2].outrd[2] = 0;
	crosses[2].roadnumber = 3;
	crosses[3].outrd[0] = 0;
	crosses[3].outrd[1] = 28;
	crosses[3].roadnumber = 2;
	crosses[4].outrd[0] = 16;
	crosses[4].outrd[1] = 2;
	crosses[4].outrd[3] = 15;
	crosses[4].roadnumber = 3;
	crosses[5].outrd[0] = 17;
	crosses[5].outrd[1] = 2;
	crosses[5].outrd[2] = 18;
	crosses[5].outrd[3] = 3;
	crosses[5].roadnumber = 4;
	crosses[6].outrd[0] = 28;
	crosses[6].outrd[1] = 3;
	crosses[6].outrd[2] = 29;
	crosses[6].roadnumber = 3;
	crosses[7].outrd[0] = 7;
	crosses[7].outrd[1] = 16;
	crosses[7].roadnumber = 2;
	crosses[8].outrd[0] = 18;
	crosses[8].outrd[1] = 7;
	crosses[8].outrd[2] = 19;
	crosses[8].outrd[3] = 5;
	crosses[8].roadnumber = 4;
	crosses[9].outrd[0] = 28;
	crosses[9].outrd[1] = 5;
	crosses[9].outrd[2] = 30;
	crosses[9].roadnumber = 3;
	crosses[10].outrd[0] = 8;
	crosses[10].roadnumber = 1;
	crosses[11].outrd[0] = 19;
	crosses[11].outrd[1] = 8;
	crosses[11].outrd[2] = 20;
	crosses[11].outrd[3] = 9;
	crosses[11].roadnumber = 4;
	crosses[12].outrd[0] = 10;
	crosses[12].roadnumber = 1;
	crosses[13].outrd[0] = 12;
	crosses[13].roadnumber = 1;
	crosses[14].outrd[0] = 21;
	crosses[14].outrd[1] = 13;
	crosses[14].outrd[2] = 20;
	crosses[14].roadnumber = 3;
	crosses[15].outrd[0] = 32;
	crosses[15].roadnumber = 1;
	crosses[16].outrd[0] = 14;
	crosses[16].outrd[1] = 27;
	crosses[16].roadnumber = 2;
	crosses[17].outrd[0] = 31;
	crosses[17].outrd[1] = 22;
	crosses[17].roadnumber = 2;
	for (int i = 1; i < 18; i++) {
		crosses[i].initstatus = rand() % 100; // ���ȡÿ��·�ڵĳ�ʼֵ
		// ÿ��·�ڵ�ѭ�����Ⱦ�Ϊ 100s?
	}
	roads[0].width = roads[1].width = 40;
	roads[2].width = roads[3].width = 10;
	for(int i = 4; i < 8; i++) {
		roads[i].width = 17;
	}
	for(int i = 8; i < 12; i++) {
		roads[i].width = 23;
	}
	roads[12].width = roads[13].width = roads[27].width = 8;
	roads[14].width = roads[31].width = roads[32].width = 14;
	roads[15].width = roads[16].width = roads[28].width = roads[29].width = roads[30].width = 15;
	for(int i = 17; i < 27; i++) {
		roads[i].width = 17;
	}
	for(int i = 1; i <= 17; i++) {
		crosses[i].green = 100 * (roads[crosses[i].outrd[0]].width) / (roads[crosses[i].outrd[0]].width + roads[crosses[i].outrd[1]].width);
		crosses[i].red = 100 - crosses[i].green;
	}
	// srand(time(0));
	// for (int i = 1; i <= 10;i++)
	// {
	// 	int xxx = rand() % 100;
	// 	cout<< randomly_decide_y(xxx) << endl;
	// }
	return 0;
}
