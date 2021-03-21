//
// Created by 李源 on 2021-02-20.
//

#ifndef PATHTRACER_CAMERA_H
#define PATHTRACER_CAMERA_H

#include "util.h"

class Camera{
private:
    Point3 origin ;
    Point3 lower_left_corner ;
    Vec3 horizontal ;
    Vec3 vertical ;
    // this front is not front.
    // this front is just back.
    Vec3 right,up,front ;
    double lens_radius ;
    double time0, time1 ;

public:
    Camera() : Camera(Point3(0,0,-1),Point3(0,0,0), Vec3(0,1,0), 40, 1, 0, 10) {}
    Camera(
            Point3 origin,
            Point3 target,
            Vec3 view_up,
            double view_fov,
            double aspect_ratio,
            double aperture,
            double focus_dist ,
            double t0 = 0,
            double t1 = 0)
    {
        auto theta = degrees_to_radians(view_fov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        // left hand and pinhole imaging
        front = unit_vector(target - origin);
        right = unit_vector(cross(front, view_up));
        up = cross(right, front);

        this->origin  = origin;
        // horizontal
        horizontal = focus_dist * viewport_width * right;
        vertical = focus_dist * viewport_height * up;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*front;

        lens_radius = aperture / 2;
        time0 = t0;
        time1 = t1;
        std::cout<<" origin :"<<origin<<std::endl ;
        std::cout<<" front "<<front<<std::endl ;
        std::cout<<" right "<<right<<std::endl ;
        std::cout<<" up "<< up <<std::endl ;
        std::cout<<" honri "<< horizontal <<std::endl ;
        std::cout<<" vert "<< vertical <<std::endl ;
        std::cout<<"lower_left_corner: "<<lower_left_corner<<std::endl ;
    }

    Ray get_Ray(double s, double t) const {
        Vec3 rd = lens_radius * random_in_unit_disk() ;
        Vec3 offset = right*rd.x() + up*rd.y() ;
        std::cout<<offset<<" " ;
        // change the origin , define dir according to (s,t) and pos+offset, random time interval.
//        return Ray(origin + offset, origin+offset - lower_left_corner - s*horizontal -t * vertical, random_double(time0, time1)) ;
        return Ray(origin , origin - lower_left_corner - s*horizontal -t * vertical, random_double(time0, time1)) ;
    }

};

#endif //PATHTRACER_CAMERA_H
