//
//  ITexture.h
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__ITexture__
#define __3DGameEngine__ITexture__

#include <string>
#include <cstdlib>
#include <iostream>
#include "lodepng.h"

enum
{
	eTEXTUREFILTER_NEAREST,
	eTEXTUREFILTER_LINEAR
};

enum
{
	eTEXTUREWRAP_REPEAT,
	eTEXTUREWRAP_CLAMP,
	eTEXTUREWRAP_CLAMPTOEDGE,
	eTEXTUREWRAP_CLAMPTOBORDER
};

typedef unsigned char Pixel_t;

struct STextureData2D
{
	int width, height;
	std::vector<Pixel_t> pixels;

	static STextureData2D LoadFromFile(const std::string &filename)
	{
	    std::vector<unsigned char> png;
	    std::vector<unsigned char> image;
	    unsigned int width, height;
	    
	    lodepng::load_file(png, filename);
	    
	    unsigned int error = lodepng::decode(image, width, height, png);
	    if (error)
	    {
	        std::cerr << "LODEPNG: Failed to load image" << std::endl;
	        std::cerr << "Error: " << error << " -> " << lodepng_error_text(error) << std::endl;
	        return STextureData2D();
	    }

	    return { (int)width, (int)height, image };
	}
};

struct STextureDataCubeMap
{
	int width, height;
	std::vector<Pixel_t> pixels[6];

	static STextureDataCubeMap LoadFromFile(const std::string &filename, bool singleTexture = false)
	{
		STextureDataCubeMap data;

		if (singleTexture)
	    {
	        std::vector<unsigned char> png;
	        std::vector<unsigned char> image;
	        unsigned int width, height;
	        
	        lodepng::load_file(png, filename);
	        
	        unsigned int error = lodepng::decode(image, width, height, png);
	        if (error)
	        {
	            std::cerr << "LODEPNG: Failed to load image" << std::endl;
	            std::cerr << "Error: " << error << " -> " << lodepng_error_text(error) << std::endl;
	        	return STextureDataCubeMap();
	   		 }
	        
	        int sideImageWidth = (width >> 2);
	        int sideImageNumPixels = (sideImageWidth * sideImageWidth) << 2;

	        data.width=sideImageWidth;
	        data.height=sideImageWidth;
	        
	        struct point
	        {
	            int x, y;
	        };
	        
	        static point startPoints[] =
	        {
	            { sideImageWidth * 2, sideImageWidth },
	            { 0, sideImageWidth },
	            { sideImageWidth, 0 },
	            { sideImageWidth, sideImageWidth * 2 },
	            { sideImageWidth, sideImageWidth },
	            { sideImageWidth * 3, sideImageWidth },
	        };

	        for (int i = 0; i < 6; ++i)
	        {
	            std::vector<unsigned char> sideImage(sideImageNumPixels);
	            
	            point startPoint = startPoints[i];
	            
	            for (int x = startPoint.x; x < startPoint.x + sideImageWidth; ++x)
	            {
	                int nx = x - startPoint.x;
	                
	                for (int y = startPoint.y; y < startPoint.y + sideImageWidth; ++y)
	                {
	                    int ny = y - startPoint.y;
	                    
	                    for (int j = 0; j < 4; ++j)
	                    {
	                        sideImage[((nx + ny * sideImageWidth) << 2) + j] = image[((x + y * width) << 2) + j];
	                    }
	                }
	            }

		    	data.pixels[i]=sideImage;
	        }
	    }
	    else
	    {
	        static const std::string filenameSuffix[] = { "x+.png", "x-.png", "y+.png", "y-.png", "z+.png", "z-.png" };
	        
	        for (int i = 0; i < 6; ++i)
	        {
	            std::vector<unsigned char> png;
	            std::vector<unsigned char> image;
	            unsigned int width, height;

	            lodepng::load_file(png, filename + filenameSuffix[i]);
	            
	            unsigned int error = lodepng::decode(image, width, height, png);
	            if (error)
	            {
	                std::cerr << "LODEPNG: Failed to load image" << std::endl;
	                std::cerr << "Error: " << error << " -> " << lodepng_error_text(error) << std::endl;
	        		return STextureDataCubeMap();
	            }

	            data.width=(int)width;
	            data.height=(int)height;
		    	data.pixels[i]=image;
	        }
	    }

	    return data;
	}
};

class ITexture
{
public:
	ITexture() {  }
	virtual ~ITexture() {  }

	virtual void Bind(int textureSlot = 0) const = 0;
};

#endif