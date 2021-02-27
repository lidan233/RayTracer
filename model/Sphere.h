//
// Created by lidan on 2021/2/24.
//

#ifndef PATHTRACER_SPHERE_H
#define PATHTRACER_SPHERE_H

#include "Model.h"

class sphere: public Model{
private:
    Point3 _center ;
    double radius ;
    shared_ptr<material>  mat_ptr ;

public:
    sphere() {}
    sphere(Point3 center, double radius, shared_ptr<matrial>) ;
    bool hit(const Ray& ray,std::pair<double,double> range, )

};

#endif //PATHTRACER_SPHERE_H
