//
//  RHInteractiveBase.hpp
//  text_vis_system
//
//  Created by Ryo Hajika on 1/03/21.
//

#pragma once

#include "ofMain.h"

namespace ofxRHUtilities {

class GenericObjectBase {
    public:
        virtual GenericObjectBase();
        virtual ~GenericObjectBase();
        
        virtual void setup() = 0;
        virtual void exit();
        virtual void update();
        virtual void draw();
};

class DrawableObjectColorBase {
    public:
        virtual void setContourColor(ofColor color);
        virtual void setContourColor(ofFloatColor color);
        virtual void setContourColor(int hexcolor);
        virtual void setContourColor(unsigned grayscale);
        virtual void setContourColor(unsigned r, unsigned g, unsigned b, unsigned a);
        virtual void setContourColor(float r, float g, float b, float a);
        virtual ofColor getContourColor();
        virtual unsigned getContourColorR();
        virtual unsigned getContourColorG();
        virtual unsigned getContourColorB();
        virtual unsigned getContourColorA();
        virtual float getContourColorRFloat();
        virtual float getContourColorGFloat();
        virtual float getContourColorBFloat();
        virtual float getContourColorAFloat();
        
        virtual void setBodyColor(ofColor color);
        virtual void setBodyColor(ofFloatColor color);
        virtual void setBodyColor(int hexcolor);
        virtual void setBodyColor(unsigned grayscale);
        virtual void setBodyColor(unsigned r, unsigned g, unsigned b, unsigned a);
        virtual void setBodyColor(float r, float g, float b, float a);
        virtual ofColor getBodyColor();
        virtual unsigned getBodyColorR();
        virtual unsigned getBodyColorG();
        virtual unsigned getBodyColorB();
        virtual unsigned getBodyColorA();
        virtual float getBodyColorRFloat();
        virtual float getBodyColorGFloat();
        virtual float getBodyColorBFloat();
        virtual float getBodyColorAFloat();
};

class DrawableObjectBase : virtual public GenericObjectBase,
                           virtual public DrawableObjectColorBase {
    public:
        virtual ~DrawableObjectBase();
        
        virtual void setup() = 0;
        virtual void exit();
        virtual void update() = 0;
        virtual void draw() = 0;
        
        virtual void setContourDraw(bool val);
        virtual bool getContourDraw();
        virtual void setContourColor(ofColor color);
        virtual void setContourColor(unsigned grayscale);
        virtual void setContourColor(unsigned r, unsigned g, unsigned b, unsigned a);
        virtual ofColor getContourColor();
        
        virtual void setContourDraw(bool val);
        virtual bool getContourDraw();
        virtual void setBodyColor(ofColor color);
        virtual void setBodyColor(unsigned grayscale);
        virtual void setBodyColor(unsigned r, unsigned g, unsigned b, unsigned a);
        virtual ofColor getBodyColor();
};

class DataObjectBase : virtual public GenericObjectBase,
                       public ofThread {
    public:
        virtual ~DataObjectBase();
        
        virtual void open() = 0;
        virtual void close() = 0;
        virtual void init() = 0;
        virtual void cleanup() = 0;
        
        virtual void addDataPath(std::string path);
        virtual std::vector<std::string> getDataPath();
        virtual void addDataExtension(std::string ext);
        virtual std::vector<std::string> getDataExtension();
};

};      // namespace ofxRHUtilities
