//
// Created by 李源 on 2021-02-20.
//

#ifndef PATHTRACER_PERLIN_H
#define PATHTRACER_PERLIN_H


#include "util.h"

// Need more clear
//Perlin noise
class PerlinNoise_3D{
private:
    //
    static const int BlockCount = 256 ;
    Vec3* ranvec ;
    int* perm_x ;
    int* perm_y ;
    int* perm_z ;

    static int *perlin_generate_perm()
    {
        auto p = new int[BlockCount] ;
        for(int i = 0 ; i < BlockCount; i++){ p[i] = i ; }
        permute_shuffle(p,BlockCount) ;
        return p ;
    }

    static void permute_shuffle(int* p, int n)
    {
        // using random to shuffle
        for (int i = n-1; i > 0; i--)
        {
            int target = random_int(0,i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }

    inline static double perlin_interp(Vec3 c[2][2][2], double u, double v, double w)
    {
        auto uu = u*u*(3-2*u);
        auto vv = v*v*(3-2*v);
        auto ww = w*w*(3-2*w);
        auto accum = 0.0;

        for (int i=0; i < 2; i++)
            for (int j=0; j < 2; j++)
                for (int k=0; k < 2; k++) {
                    Vec3 weight_v(u-i, v-j, w-k);
                    accum += (i*uu + (1-i)*(1-uu))*
                             (j*vv + (1-j)*(1-vv))*
                             (k*ww + (1-k)*(1-ww))*dot(c[i][j][k], weight_v);
                }
        return accum;
    }

public:
    PerlinNoise_3D()
    {
        ranvec = new Vec3[BlockCount] ;
        // initial gradient vector for each block
        for(int i = 0; i < BlockCount;i++)
        {
            ranvec[i] = unit_vector(Vec3::random(-1,1)) ;
        }
        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }

    ~PerlinNoise_3D(){
        delete ranvec ;
        delete perm_x ;
        delete perm_y ;
        delete perm_z ;
    }

    double GenerateNoise(const Point3& p) const
    {
        auto u = p.x() - floor(p.x());
        auto v = p.y() - floor(p.y());
        auto w = p.z() - floor(p.z());
        auto i = static_cast<int>(floor(p.x()));
        auto j = static_cast<int>(floor(p.y()));
        auto k = static_cast<int>(floor(p.z()));

        Vec3 c[2][2][2];

        // according to permute_shuffle to init all data in all points of a cube
        for (int di=0; di < 2; di++)
            for (int dj=0; dj < 2; dj++)
                for (int dk=0; dk < 2; dk++)
                    c[di][dj][dk] = ranvec[
                            perm_x[(i+di) & 255] ^
                            perm_y[(j+dj) & 255] ^
                            perm_z[(k+dk) & 255]
                    ];
        // according to all points  of a cube to interpolution
        return perlin_interp(c, u, v, w);
    }

    double turb(const Point3& p, int depth=7) const
    {
        auto accum = 0.0;
        auto temp_p = p;
        auto weight = 1.0;

        for (int i = 0; i < depth; i++) {
            accum += weight * GenerateNoise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }

        return fabs(accum);
    }
};


#endif //PATHTRACER_PERLIN_H
