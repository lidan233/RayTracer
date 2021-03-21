//
// Created by 李源 on 2021-02-19.
//

#ifndef PATHTRACER_RAY_H
#define PATHTRACER_RAY_H
#include "EigenLidan.h"


class Ray{
public:
    Point3 origin;
    Vec3 dir;
    double time;

public:
    Ray() {}
    Ray(const Point3& origin, const Vec3& direction)
            : origin(origin), dir(direction), time(0)
    {}

    Ray(const Point3& origin, const Vec3& direction, double time)
            : origin(origin), dir(direction), time(time)
    {}
    Point3 GetOrigin() const  { return origin; }
    Vec3 GetDirection() const { return dir; }
    double GetTime() const    { return time; }
    Point3 at(double t) const { return origin + t*dir; }

};
#endif //PATHTRACER_RAY_H
