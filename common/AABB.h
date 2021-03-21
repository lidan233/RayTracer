//
// Created by 李源 on 2021-02-17.
//

#ifndef PATHTRACER_AABB_H
#define PATHTRACER_AABB_H
#include  "EigenLidan.h"
#include  "Ray.h"

class AABB{
private:
    Point3 _min ;
    Point3 _max ;
public:
    AABB() {}
    AABB(const Point3& a, const Point3& b) { _min = a; _max = b; }
    Point3 min() const {return _min; }
    Point3 max() const {return _max; }

    bool hit(const Ray& r, double tmin, double tmax) const {
        for (int a = 0; a < 3; a++) {
            auto t0 = fmin((_min[a] - r.GetOrigin()[a]) / r.GetDirection()[a],
                           (_max[a] - r.GetOrigin()[a]) / r.GetDirection()[a]);
            auto t1 = fmax((_min[a] - r.GetOrigin()[a]) / r.GetDirection()[a],
                           (_max[a] - r.GetOrigin()[a]) / r.GetDirection()[a]);
            tmin = fmax(t0, tmin);
            tmax = fmin(t1, tmax);
            if (tmax <= tmin)
                return false;
        }
        return true;
    }

    double area() const {
        auto a = _max.x() - _min.x();
        auto b = _max.y() - _min.y();
        auto c = _max.z() - _min.z();
        return 2*(a*b + b*c + c*a);
    }

    int longest_axis() const {
        auto a = _max.x() - _min.x();
        auto b = _max.y() - _min.y();
        auto c = _max.z() - _min.z();
        if (a > b && a > c)
            return 0;
        else if (b > c)
            return 1;
        else
            return 2;
    }


    AABB merge(AABB other) {
        Vec3 small(fmin(min().x(), other.min().x()),
                   fmin(min().y(), other.min().y()),
                   fmin(min().z(), other.min().z()));

        Vec3 big  (fmax(max().x(), other.max().x()),
                   fmax(max().y(), other.max().y()),
                   fmax(max().z(), other.max().z()));

        return AABB(small,big);
    }
};



}


#endif //PATHTRACER_AABB_H
