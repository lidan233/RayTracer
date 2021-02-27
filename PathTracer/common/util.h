//
// Created by 李源 on 2021-02-20.
//

#ifndef PATHTRACER_UTIL_H
#define PATHTRACER_UTIL_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


using std::shared_ptr ;
using std::make_shared ;
using std::sqrt ;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


inline double clamp(double x, double min, double max)
{
    if ( x < min ) x = min ;
    if ( x > max ) x = max ;
    return x ;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}


inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    return static_cast<int>(random_double(min, max+1));
}





#include "Ray.h"
#include "EigenLidan.h"
#include "Model.h"

inline void write_color(std::ostream &out, Color pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    if (r != r) r = 0.0;
    if (g != g) g = 0.0;
    if (b != b) b = 0.0;

    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

bool hit_sphere(const Point3& center, double radius, const Ray& ray)
{
    Vec3 direct = ray.GetOrigin() - center ;
    if(direct.length()<radius) return true ;
    Vec3 raydir = unit_vector(ray.GetDirection()) ;
    Vec3 left = raydir * (direct*raydir).length() ;
    double dis = sqrt(direct.length_square() - left.length_square()) ;
    if(dis <= radius) return true ;
    return false ;
}

double hit_sphere_norm(const Point3& center, double radius, const Ray& ray)
{
    Vec3 direct = ray.GetOrigin() - center ;
    if(direct.length()<radius) return -1.0 ;
    Vec3 raydir = unit_vector(ray.GetDirection()) ;
    Vec3 left = raydir * (direct*raydir).length() ;
    double dis = sqrt(direct.length_square() - left.length_square()) ;
    if(dis > radius)  return -1.0 ;
    return
}

Color ray_color_norm(const  Ray& r )
{

}

Color ray_color(const Ray& r)
{
    if(hit_sphere(Point3(0,0,-1),0.2,r))
    {
        std::cout<<r.GetOrigin()<<" "<<r.GetDirection()<<" hit color: "<<std::endl ;
        return Color(1,0,0) ;
    }
    Vec3 unit_direction = unit_vector(r.GetDirection()) ;
    auto t = 0.5 * (unit_direction.y() + 1.0) ;
    return (1.0 - t) * Color(1.0,1.0, 1.0 ) + t*Color(0.5,0.7,1.0) ;
}



#endif //PATHTRACER_UTIL_H
