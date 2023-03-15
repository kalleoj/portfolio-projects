#include "point.hh"

Point::Point(int x, int y, int z) : x_(x), y_(y), z_(z)
{

}

Point::Point() : x_(UNKNOWN_VALUE), y_(UNKNOWN_VALUE), z_(UNKNOWN_VALUE)
{

}

int Point::getX() const
{
    return x_;
}

int Point::getY() const
{
    return y_;
}

int Point::getZ() const {
    return z_;
}

double Point::countDistance(Point& point) const
{
    int dx = x_ - point.getX();
    int dy = y_ - point.getY();
    int dz = z_ - point.getZ();

    return sqrt(dx*dx + dy*dy + dz*dz);
}
