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

double s[20] = {0.6896, 0.7071, 0.7001, 0.7049, 0.6297, 0.7139, 0.6925, 0.6819, 0.6316, 0.6299, 0.6013, 0.6444, 0.5889, 0.6125,
                0.5563};
double y[20] = {0.7408, 0.7145, 0.7974, 0.7679, 0.6907, 0.7622, 0.7622, 0.9038, 0.7622, 0.7919, 0.7436, 0.7551, 0.7129, 0.7741,
                0.6595};

int main()
{

    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            double z = (y[i] - y[j]) / y[i];
            double t = (s[i] - s[j]) / s[i];
            if(t==0)
            {
                continue;
            }
            else
            {
                cout<<z/t<<endl;
            }
        }
    }
    return 0;
}