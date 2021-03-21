#include <iostream>
#include "util.h"
#include "Camera.h"


typedef int int4 ;


int renderBasicColor() {
    const int4 image_width = 256 ;
    const int4 image_height = 256 ;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; j-- )
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0 ; i < image_width ; i++)
        {
            auto r = double(i) / (image_width - 1) ;
            auto g = double(j) / (image_height - 1) ;
            auto b = 0.25 ;

            int ir = static_cast<int>(255.999*r)  ;
            int ig = static_cast<int>(255.999*r) ;
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return 0 ;
}

int main()
{
    srand( time(NULL)) ;
    const auto aspect_ratio = 16.0/9.0 ;
    const int image_width = 32 ;
    const int image_height = static_cast<int>(image_width/aspect_ratio) ;
    const int samples_per_pixel = 10 ;
    const int max_depth = 50 ;

    Point3 origin(0,0,0);
    Point3 lookat(0,0,-1);
    Point3 viewup(0,1,0) ;

    auto dist_focus = 10.0 ;
    auto aperture = 0.1 ;

    Camera cam(origin,lookat,viewup,20,aspect_ratio,aperture,dist_focus) ;

    std::cout<<"P3/n"<<image_width<<' '<<image_height<<"\n255\n" ;

    for(int i = image_height; i >= 0 ; i--)
    {
        std::cerr<<"\rScanlines remaining"<<i<<' '<<std::flush ;
        for(int j = 0 ; j <image_width; j++)
        {
            Color pixel_color(0,0,0) ;
            for(int s = 0; s < samples_per_pixel ; ++s)
            {
                auto u = (i + random_double()) / (image_height - 1) ;
                auto v = (j + random_double()) / (image_width - 1) ;
                Ray r = cam.get_Ray(u,v) ;
                pixel_color += ray_color(r) ;
                std::cout<<r.GetOrigin()<<" "<<r.GetDirection()<<" color: "<<ray_color(r)<<std::endl ;
            }
            write_color(std::cout, pixel_color, samples_per_pixel ) ;
        }
    }
    std::cerr<<"\n Done" ;
}