#ifndef POINT_HH
#define POINT_HH

#include <map>
#include <cmath>
#include <limits>

using namespace std;

const int UNKNOWN_VALUE = numeric_limits<int>::max();

class Point
{
public:
    Point(int x, int y, int z);
    Point();
    int getX() const;
    int getY() const;
    int getZ() const;

    double countDistance(Point& point) const;

private:
    int x_;
    int y_;
    int z_;
};

#endif // POINT_HH
