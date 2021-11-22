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
const double max_acceleration = 7.0;//×î´ó¼õËÙ¶È£¨µÄ¾ø¶ÔÖµ£© 
double dealt_time; // ÒÑ¾­´¦ÀíµÄÊ±¼ä³¤¶È 
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
    double acceleration=0;//¼ÓËÙ¶È 
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
//double operator % (double a, double b) { // Á½¸öÕıĞ¡ÊıÈ¡ÓàÔËËã 
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
//cross+area2 ÇóÃæ»ı 
Vector Rotate(Vector A, double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
//Ğı×ªÏòÁ¿ 
// please make sure its not a zero vector!
Vector Normal(Vector A)//Ğı×ª90¡ã²¢µ¥Î»»¯ 
{
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
Vector Format(const Vector &A)//»»Ëãµ¥Î»ÏòÁ¿ 
{
    double L=Length(A);
    return Vector(A.x/L,A.y/L);
}

const double eps = 1e-10;//¾«¶È 
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
Point GetLineIntersection (Point P, Vector v, Point Q, Vector w)//½âÎöÊ½ 
{
    Vector u=P-Q;
    double t = Cross(w,u)/Cross(v,w);
    return P+v*t;
}
//F*ck CCF
double DistanceToLine (Point P, Point A, Point B)//µãµ½Ö±Ïß¾àÀë 
{
    Vector v1 = B-A,v2=P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}
double DistanceToSegment (Point P, Point A, Point B)//µãµ½Ïß¶Î¾àÀë 
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

Point GetLineProjection(const Point& P, const Point& A, const Point& B)//Ö±ÏßÍ¶Ó° 
{
    Vector v = B - A;
    return A + v * (Dot(v, P - A) / Dot(v, v));
}

bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2)//½»µã 
{
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1),
    c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
//FUCKCCF 
bool isPointOnSegment(const Point& p, const Point& a1, const Point& a2)//ÅĞ¶ÏµãÔÚÏß¶ÎÉÏ 
{
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
double PolygonArea(Point* p, int n)//Çó¶à±ßĞÎÃæ»ı£¬*pÎª¶ËµãÊı×é 
{
    double area = 0;
    for (int i = 1; i < n - 1; i++)
        area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return area / 2;
}

struct Circle//Ô² 
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
int GetLineCircleIntersection(const Point& A, const Point& B, const Circle& C, vector<Point>& sol)//Ö±ÏßºÍÔ²µÄ½»µãÊıÁ¿ 
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

int GetCircleCircleIntersection (Circle C1, Circle C2, vector<Point>& sol)//Á½¸öÔ²µÄ½»µãÊıÁ¿
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
//€€¡ê 
inline int GetTangents (const Point P, const Circle C, vector<Point>& v)//ÇĞÏß 
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
//µÀÊ¿´ò¸æ 
struct Road
{
    int start;
    int end;
    Car first_car;
	double lim_v;
    Road(int start, int end):start(start),end(end)
    {
    }
};
//shabiccf 
Point sites[20];//µÀÂ·½»µã 
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

bool is_same_dir(Vector a, Vector b)//ÅĞ¶ÏÁ½¸öÏòÁ¿ÊÇ·ñÍ¬Ïò 
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
å°†æ¯ä¸ªè·¯æ®µçš„è½¦è¾†ä»å‰åˆ°åä¾æ¬¡æ’åºï¼Œç»„æˆä¸€ä¸ªé˜Ÿåˆ—
é˜Ÿåˆ—ä¸­çš„å…ƒç´ ä¸º Car, æ¯ä¸ªå…ƒç´ éœ€è¦æœ‰ä¸€ä¸ªå‰é©± prev ä¸åç»§ next, è¿˜æœ‰ Car æœ¬èº«çš„å±æ€§, ä»¥åŠåˆ°è¾¾ä¸‹ä¸€ä¸ªè·¯å£çš„é¢„è®¡èŠ±è´¹æ—¶é—´ t
æ¯éš”1ç§’æ›´æ–°ä¸€æ¬¡æ•°æ®
*/
double point_dist(Point a,Point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

struct cross
{
	int outrd[6];
	int roadnumber;//µÀÂ·ÊıÁ¿ 
	double red, green; // ´Ë´¦ red ¶¨ÒåÎª ±àºÅ0/2 µÄ³ö±ßµÄºìµÆ
	double initstatus; // initstatus ¶¨ÒåÎª ±àºÅ0/2 µÄ³ö±ßµÚÒ»´ÎÂÌµÆ×ªºìµÆµÄÊ±ºò¾àÀë³õÊ¼Ê±¼äµÄÊ±¿Ì 
}crosses[44];

int get_num(int rd_number)
{
	int cnt=0;
	for(int i=1;i<=nc;i++)
	{
		if(isPointOnSegment(cs[i].center,sites[roads[i].start],sites[roads[i].end])) cnt++;
	}
	return cnt;
}// è¾“å‡ºè¯¥è·¯æ®µæœ‰å¤šå°‘è¾†è½¦

bool red_or_green (double time, int cross, int sta) { // 0=red 1=green
	double cyctime = mod(time + crosses[cross].initstatus, crosses[cross].red + crosses[cross].green);
	bool red_02 = (cyctime < crosses[cross].red);
	if ((red_02 + (sta % 2)) == 1) return 0;
	return 1;
}

double car_turning[1009],decelerate_time[1009],accelerate_time[1009];//¼ÇÂ¼Ã¿Á¾³µ»¹ĞèÒª¶àÉÙÊ±¼ä×ªÍä ÒÔ¼°»¹Òª¶àÉÙÊ±¼ä¼õËÙµ½0 
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
}// æ‰¾åˆ°è¯¥è·¯æ®µæœ€é å‰çš„ä¸€è¾†è½¦

Car get_first_end(int rd_number)
{
	Car nearest;
	if(!get_num(rd_number)) return nearest;
	double minn=998244353.0;
	int mink=114514;
	Point dir=sites[roads[rd_number].start]-sites[roads[rd_number].end];
	bool flag=0;
	for(int i=1;i<=nc;i++)
	{
		if(isPointOnSegment(cs[i].center,sites[roads[i].start],sites[roads[i].end]))
		{
			if(minn>point_dist(cs[i].center,sites[roads[rd_number].end])&&Dot(dir,cs[i].Direction)<0)
			{
				mink=i;
				minn=point_dist(cs[i].center,sites[roads[rd_number].end]);
				nearest=cs[i];
			}
		}
	}
	return nearest;
}// æ‰¾åˆ°è¯¥è·¯æ®µæœ€é å‰çš„ä¸€è¾†è½¦
#define crossroads GetLineIntersection(roads[i].start,roads[i].end-roads[i].start,roads[j].start,roads[j].end-roads[j].start)
bool get_to_intersection(Car cr)
{
	for(int i=0;i<33;i++)
		for(int j=i+1;i<33;j++)
		{
			if(crossroads==cr.center) return 1; 
		}
	return 0;
}// åˆ¤æ–­è½¦è¾†æ˜¯å¦åˆ°è¾¾è·¯å£

// 0.5s update ä¸€æ¬¡
//roads 0~16ºáÏò 17~30×İÏò 3132Ğ±Ïò 
struct turn
{
	int to_num;
	double turn_time;
};

turn rand_turn(int crossroad_number,int status)//rand-status=0 µôÍ· rand-status=1 ÓÒ×ª rand-status=2 Ö±ĞĞ rand-status=3 ×ó×ª 
{
	srand(time(0));
	int rand_turn=rand()%4;
	turn to_road;
	to_road.to_num=crosses[crossroad_number].outrd[rand_turn];
	int turnstatus=(rand_turn+4-status)%4;
	if(turnstatus<2) to_road.turn_time=5.0;
	else if(turnstatus==2) to_road.turn_time=1.5;
	else to_road.turn_time=0.5; 
	return to_road;
}//ÓÒ×ª5s Ö±ĞĞ1.5s ×ó×ª0.5s µôÍ·5s

double max_upspeed(double a,double s,double maxv,int cross) {
	/*
	Ë¼Â·£ºÏÈÅĞ¶ÏÏÈ¼ÓËÙµ½×î´óËÙ¶ÈÔÙÔÈËÙÄÜ·ñ¹ıºìµÆ
	Èç¹û²»ĞĞ£¬ÔÙÅĞ¶ÏºÎÊ±¼õËÙ 
	*/
	double acc_dis = maxv * maxv / a / 2;
	double acc_time = maxv / a;
	double other_time = (s - acc_dis) / maxv;
	double red_time = (crosses[cross].red + crosses[cross].green) - mod(dealt_time + crosses[cross].initstatus, crosses[cross].red + crosses[cross].green);
	if (acc_time + other_time <= red_time) {//ÄÜÍ¨¹ı Ìõ¼şÕ¼Î» 
		return maxv;
	}
	double maxv_s = maxv / 2 * (maxv / a + maxv / max_acceleration);
	if (maxv_s <= s) return maxv;
	return sqrt(s * 2 / (1 / a + 1 / max_acceleration));
} 

void update()//0.5second
{
	dealt_time = dealt_time + 0.5;
	//todos: how to judge whether a car can pass a traffic light
	//       how to update the variable 'done'
	bool done=0;
    // ä» get_first(...) ä»å‰å¾€åæ›´æ–°
        // å‡å¦‚è‡ªå·±ä¸æ˜¯ prev
            // å‡å¦‚ prev éœ€è¦å‡é€Ÿ
                // æ ¹æ®å…¬å¼1è®¡ç®—è¯¥è½¦çš„ç›¸åº”æœ€å¤§å‡é€Ÿåº¦ï¼Œå¹¶æŠŠæ‰€æœ‰ä¸è¯¥è½¦æœ‰å…³çš„çŠ¶æ€æ›´æ–°
            // å‡å¦‚ prev æ­£å¸¸è¡Œé©¶
                // è®¡ç®— t å¹¶åˆ¤æ–­è‡ªå·±æ˜¯å¦éœ€è¦å‡é€Ÿ
                    // å‡å¦‚éœ€è¦å‡é€Ÿ, æ›´æ–°å‡é€Ÿåº¦ä¸ºå…¬å¼2
        // å‡å¦‚è‡ªå·±æ˜¯ prev
            // éšæœºæ•°çœ‹è½¬ä»€ä¹ˆå¼¯ï¼ˆåœ¨å…è®¸çš„è½¦å‘èŒƒå›´å†…ï¼Œä¸”ä¸å‡†æ‰å¤´ï¼‰
                // å°è½¬å¼¯ç›´æ¥è½¬ï¼Œæ·»åŠ åˆ°å¦ä¸€ä¸ªè·¯æ®µé˜Ÿåˆ—çš„æœ«å°¾
                // åˆ¤æ–­è‡ªå·±æ˜¯å¦éœ€è¦å‡é€Ÿ
                    // éœ€è¦
                        // ä»¥æœ€å¤§å‡é€Ÿåº¦å‡é€Ÿå³å¯
                        // ç­‰å¾…ç»¿ç¯
                        // ç»¿ç¯äº®åä»¥æœ€å¤§åŠ é€Ÿåº¦è¿›è¡Œä¸‹é¢çš„æ“ä½œ
                    // ä¸éœ€è¦ï¼šæ­£å¸¸æ›´æ–°
                        // å‡å¦‚åœ¨ 1s å†…èƒ½åˆ°è¾¾è·¯å£(get_to_intersection), æ­£å¸¸è½¬å¼¯å¹¶è¿›å…¥å¦ä¸€æ¡è·¯æ®µé˜Ÿåˆ—æœ«å°¾
	while(!done)
	{
		int crsrd_num,sta;
		for(int i=0;i<33;i++)//across
		{
			for(int j=i+1;j<33;j++)//not across
			{
				if(!isPointOnSegment(crossroads,roads[i].start,roads[i].end)||!isPointOnSegment(crossroads,roads[j].start,roads[j].end)) continue;//²»´æÔÚµÄ½»µã£¨½»µã´æÔÚÓÚÏß¶ÎÍâ£© 
				Point dir = sites[roads[i].start]-sites[roads[i].end];
				if(crossroads == roads[i].start)
				{
					for(int k=1;k<=nc;k++)
					{
						if(isPointOnSegment(cs[k].center,sites[roads[i].start],sites[roads[i].end])&&Dot(dir,cs[k].Direction)>0&&car_turning[k]==0)//×¼±¸×ªÍä 
						{
							if(get_to_intersection(cs[k]))
							{
								if (accelerate_time[i] > 0) {
									cs[i].Direction = cs[i].Direction * (Length(cs[i].Direction) + 0.5 * max_acceleration) / Length(cs[i].Direction);
									accelerate_time[i] = accelerate_time[i] - 0.5; 
								}
								for(int z=0;z<20;z++)
									if(sites[z]==crossroads)
									{
										crsrd_num=z;
										break;
									}
								for(int z=0;z<4;z++)
								{
									if(i==crosses[crsrd_num].outrd[z])
									{
										sta=z;
										break;
									}
								}
								turn Turning=rand_turn(crsrd_num,sta);
								car_turning[k]=Turning.turn_time;
								cs[k].rd=Turning.to_num;
								if(crossroads == sites[roads[cs[k].rd].start]) cs[k].Direction=sites[roads[cs[k].rd].end]-sites[roads[cs[k].rd].start];
								else cs[k].Direction=sites[roads[cs[k].rd].start]-sites[roads[cs[k].rd].end];
							}
						}
						else if (isPointOnSegment(cs[i].center, sites[roads[i].start], sites[roads[i].end]) && Dot(dir, cs[i].Direction) > 0 && car_turning[i] != 0) {
							car_turning[i] -= 0.5;
							if (car_turning[i] <= 0) {
								accelerate_time[i] = max_upspeed(max_acceleration, Length(roads[cs[i].rd].start - roads[cs[i].rd].end), roads[cs[i].rd].lim_v, crsrd_num);
							}
						}
						else {
							if ( /*ÄÜÍ¨¹ı*/ 1) { // ºìÂÌµÆÄÜÍ¨¹ı Ìõ¼şÕ¼Î» 
								cs[k].center = cs[k].center + (cs[k].Direction / 2); 
							}
							else { // ÎŞ·¨Í¨¹ı£¬¼õËÙ 
								if (decelerate_time[k]>0) {
									cs[k].Direction = cs[k].Direction * (Length(cs[k].Direction) + max_acceleration) / Length(cs[k].Direction);
								}
								if (point_dist(cs[k].center, sites[roads[i].start]) <= min_decelarate_dis(Length(cs[k].Direction), max_acceleration)) {
									decelerate_time[k] = Length(cs[k].Direction), max_acceleration;
								}
							} 
						}
					}
				}
			}
		}
	}
}

/*
å¼•å…¥æ™ºèƒ½è·¯ç¯åï¼š
1. åˆ¹è½¦è·ç¦»çº¦ä¸º 16mï¼Œå³è·¯å£å¿…é¡» lidar å…¨è¦†ç›–
2. å¯¹äºè·¯æ®µä¸­æ²¡æœ‰ lidar è¦†ç›–çš„è½¦è¾†ï¼ŒæŒ‰ç…§åŒ€é€Ÿè¡Œé©¶
3. wifi åˆ†é…æŒ‰ç…§äºŒåˆ†å›¾åŒ¹é…ç®—æ³•æ¥
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
	for(int i = 0; i < 3; i++) {
		roads[i].lim_v = 70.0 / 3.6;
	}
	for(int i = 3; i < 33; i++) {
		roads[i].lim_v = 50.0 / 3.6;
	}
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
