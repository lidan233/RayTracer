//
// Created by lidan on 2021/2/24.
//

#ifndef PATHTRACER_MODEL_H
#define PATHTRACER_MODEL_H

#include "Ray.h"
#include <utility>

class Model{
public:
    virtual bool hit(const Ray& ray, std::pair<double, double> timerange, const Vec3& outward_normal ) ;
};


#endif //PATHTRACER_MODEL_H
