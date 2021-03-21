//
// Created by 李源 on 2021-02-21.
//

#ifndef PATHTRACER_TEXTURE_H
#define PATHTRACER_TEXTURE_H

#include "util.h"
#include "perlin.h"
#include "usingImage.h"
#include "stb_image.h"

#include <iostream>

class Texture
{
public:
    virtual Color value(double x, double y, const Vec3& p) const = 0 ;
};

class ColorTexture: public Texture
{
private:
    Color color_value;

public:
    ColorTexture() {}
    ColorTexture(Color c) : color_value(c) {}

    ColorTexture(double red, double green, double blue)
            : ColorTexture(Color(red,green,blue)) {}

    virtual Color value(double u, double v, const Vec3& p) const override {
        return color_value;
    }

};

class BufferTexture: public Texture
{
public:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;

public:
    BufferTexture() {}

    BufferTexture(shared_ptr<Texture> t0, shared_ptr<Texture> t1)
    : even(t0), odd(t1) {}

    BufferTexture(Color c1, Color c2)
    : even(make_shared<ColorTexture>(c1)) , odd(make_shared<ColorTexture>(c2)) {}

    virtual Color value(double u, double v, const Vec3& p) const override {
        auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
        if (sines < 0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }

};


class NoiseTexture: public Texture
{

private:
    PerlinNoise_3D noise ;
    double scale ;
public:

    NoiseTexture() {}
    NoiseTexture(double sc): scale(sc) {}

    virtual Color value(double u, double v, const Vec3& p) const override{
        return Color(1,1,1) * 0.5 *(1 + sin(scale*p.z() + 10*noise.turb(p)));
    }
};

class ImageTexture: public Texture
{
private:
    unsigned char *data ;
    int width, height ;
    int one_line_buffer_size ;
public:
    const static int bytes_per_pixel = 3 ;
    ImageTexture()
    : data(nullptr), width(0), height(0){}
    ImageTexture(const char* filename)
    {
        auto components_per_pixel = bytes_per_pixel ;
        data = stbi_load(
                filename, &width, &height, &components_per_pixel, components_per_pixel) ;
        if (!data) {
            std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
            width = height = 0;
        }

        one_line_buffer_size = bytes_per_pixel * width;
    }

    ~ImageTexture(){
        delete data ;
    }

    virtual Color value(double u, double v, const Vec3& p) const override {
        if (data == nullptr)
            return Color(0,1,1) ;
        u = clamp(u,0.0,1.0) ;
        v = clamp(v,0.0,1.0) ;

        auto i = static_cast<int>(u*height) >= height? height-1 :static_cast<int>(u*height) ;
        auto j = static_cast<int>(v*width) >= width? width-1 : static_cast<int>(v*width) ;

        const auto color_scale = 1.0 / 255.0 ;
        auto pixel = data + j * one_line_buffer_size +i * bytes_per_pixel ;
        return Color(color_scale * pixel[0], color_scale*pixel[1], color_scale*pixel[2] ) ;
    }
};


#endif //PATHTRACER_TEXTURE_H
