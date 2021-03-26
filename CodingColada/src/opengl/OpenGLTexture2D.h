#pragma once 

#include <map>
#include <string>


class OpenGLTexture2D
{

public:
    unsigned int id_;

    unsigned int width_;
    unsigned int height_;


    unsigned int internal_format_;   // format of texture object
    unsigned int image_format_;      // format of loaded image

    unsigned int wrap_s_; // wrapping mode on S axis
    unsigned int wrap_t_; // wrapping mode on T axis
    unsigned int filter_min_; // filtering mode if texture pixels < screen pixels
    unsigned int filter_max_; // filtering mode if texture pixels > screen pixels

    OpenGLTexture2D();

    void Generate(unsigned int width, unsigned int height, unsigned char* data);

    void Bind() const;


    // loads (and generates) a texture from file
    static OpenGLTexture2D LoadTextureFromFile(const char* file, bool alpha);
};