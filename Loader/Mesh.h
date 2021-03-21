//
// Created by lidan on 2021/3/21.
//

#ifndef PATHTRACER_MESH_H
#define PATHTRACER_MESH_H
#include "EigenLidan.h"

struct Vertex{
    Vec3 pos ;
    Vec3 normal ;
    Vec2 texture_coord ;
};

struct Face{
    unsigned int a, b, c ;
};


struct Material{
    Material()
    {
        name;
        Ns = 0.0f;
        Ni = 0.0f;
        d = 0.0f;
        illum = 0;
    }

    // Material Name
    std::string name;
    // Ambient Color
    Vector3 Ka;
    // Diffuse Color
    Vector3 Kd;
    // Specular Color
    Vector3 Ks;
    // Specular Exponent
    float Ns;
    // Optical Density
    float Ni;
    // Dissolve
    float d;
    // Illumination
    int illum;
    // Ambient Texture Map
    std::string map_Ka;
    // Diffuse Texture Map
    std::string map_Kd;
    // Specular Texture Map
    std::string map_Ks;
    // Specular Hightlight Map
    std::string map_Ns;
    // Alpha Texture Map
    std::string map_d;
    // Bump Map
    std::string map_bump;
};


class Mesh {

private:
    std::string name ;
    std::vector<Vertex> vertices ;
    std::vector<Face> faces ;
    Material meshMaterial ;

public:

    Mesh() {}
    Mesh(std::vector<Vertex>& _Vertex, std::vector<Face>& _faces)
    {
        vertices = _Vertex ;
        faces = _faces ;
    }


};


#endif //PATHTRACER_MESH_H
