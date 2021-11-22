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

char first[33] =
    {
        'C', 'B', 'D', 'E', 'G', 'H', 'I', 'H', 'J', 'K', 'L', 'K', 'M', 'N', 'P', 'A', 'D', 'B', 'E', 'H', 'K', 'N', 'Q', 'N', 'K', 'H', 'E', 'P', 'C', 'F', 'I', 'Q', 'O'};

char second[33] =
    {
        'B', 'A', 'E', 'F', 'H', 'I', 'H', 'G', 'K', 'L', 'K', 'J', 'N', 'O', 'Q', 'D', 'G', 'E', 'H', 'K', 'N', 'Q', 'N', 'K', 'H', 'E', 'B', 'M', 'F', 'I', 'L', 'O', 'L'};

int start[33], endd[33];

int main()
{
    for (int i = 0; i < 33;i++)
    {
        start[i] = int(first[i]) - 65;
        endd[i] = int(second[i]) - 65;
    }
    for (int i = 0; i < 33;i++)
    {
        cout << "Road(" << start[i] << ", " << endd[i] << ")," << endl;
    }
    // for (int i = 0; i < 33;i++)
    // {
    //     cout << endd[i] << endl;
    // }
    return 0;
}