//
//  RHInteractiveObject.h
//
//  Created by Ryo Hajika on 16/08/20.
//

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "opencv2/features2d.hpp"
#include "opencv2/flann/flann.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "RHColors.h"

#define RH_INTERACTIVE_COLOR_DUB_START ofEnableBlendMode(OF_BLENDMODE_ADD);
#define RH_INTERACTIVE_COLOR_DUB_END ofDisableBlendMode();

// MARK:- WeavyButterfly
class WeavyButterfly {
    public:
        WeavyButterfly();
        ~WeavyButterfly();
        
        void setup(float size_w, float size_h, float size_d);
        void update(float vol);
        float draw();
        
    private:
        void drawBody();
        void drawSmallWings(float angle);
        void drawLargeWings(float angle);
        
        vector<ofVec3f> pts = { ofVec3f(0, 0, 0),
                                ofVec3f(cos(PI/3), sin(PI/4)/2, 0),
                                ofVec3f(cos(PI/6), sin(PI/6)/2, 0),
                                ofVec3f(1, 0, 0),
                                ofVec3f(cos(PI/8), -sin(PI/8)/3, 0),
                                ofVec3f(cos(PI/7), -sin(PI/5)/2, 0),
                                ofVec3f(cos(PI/6), -sin(PI/4)/2, 0),
                                ofVec3f(cos(PI/3), -sin(PI/4)/2, 0)
                              };
        vector<ofVec3f> bts = { ofVec3f(0, 0, 0),
                                ofVec3f(cos(PI/4)/2, sin(PI/3)/2, 0),
                                ofVec3f(cos(PI/5), sin(PI/5), 0),
                                ofVec3f(1+cos(PI/6)/2, sin(PI/6)/2, 0),
                                ofVec3f(1+cos(PI/6), -sin(PI/6)/2, 0),
                                ofVec3f(1+cos(PI/6), -sin(5*PI/12)/2, 0),
                                ofVec3f(1+cos(PI/4)/2+cos(PI/6), -sin(PI/4)-sin(5*PI/12)/2, 0),
                                ofVec3f(3*cos(PI/4), -3*sin(PI/4), 0),
                                ofVec3f(2*cos(PI/4)+cos(PI/4)/2, -3*sin(PI/4)-sin(PI/4)/3, 0),
                                ofVec3f(2*cos(PI/4), -3*sin(PI/4), 0),
                                ofVec3f(cos(PI/3)/2, -sin(PI/3), 0)
                               };
        deque<float> noises;
        ofVec3f scale;
        ofColor baseColor;
        ofColor edgeColor;
};

// MARK:- ThreeDGridSystem
class ThreeDGridSystem {
private:
    glm::vec3 gridSpaceSize;
    glm::vec3 dotNumbers;
    glm::vec3 intervalOnEachSide;
    float lineLength;
    std::vector<glm::vec3> pts;
    std::vector<unsigned int> ptsidx;
    std::vector<glm::vec3>::iterator it;

public:
    ThreeDGridSystem();
    ~ThreeDGridSystem();
    
    void setup(ofVec3f gridspace, ofVec3f dotNumOnEachSide, float dotSize);
    void update(float transitionX);
    void draw(float x, float y, float z);
};

// MARK:- GradientElement
enum GRADIENT_RECTANGLE_MOVE {
    GRADIENT_RECTANGLE_LEFT_TO_RIGHT = 0,
    GRADIENT_RECTANGLE_RIGHT_TO_LEFT,
    GRADIENT_RECTANGLE_TOP_TO_BOTTOM,
    GRADIENT_RECTANGLE_BOTTOM_TO_TOP,
    GRADIENT_RECTANGLE_NONE
};

enum GRADIENT_MOTION_TYPE {
    GRADIENT_MOTION_IN = 0,
    GRADIENT_MOTION_OUT,
    GRADIENT_MOTION_INOUT,
    GRADIENT_MOTION_NONE
};

enum GRADIENT_SHAPE {
    GRADIENT_SHAPE_RECTANGLE = 0,
    GRADIENT_SHAPE_TRIANGLE,
    GRADIENT_SHAPE_ELLIPSE,
    GRADIENT_SHAPE_BOX
};
        
class GradientElement {
    public:
        GradientElement();
        ~GradientElement();
        
        void setup(GRADIENT_SHAPE shape,
                   float width, float height, float depth,
                   GRADIENT_MOTION_TYPE motion, float duration, bool bStart);
        void update();
        void draw(ofPoint center_position);
        void draw(float center_x, float center_y, float center_z);
        void igniteAnimation();
        bool isAnimationActive();
        
        void setRectangleMoveType(GRADIENT_RECTANGLE_MOVE move);
        GRADIENT_RECTANGLE_MOVE getRectangleMoveType();
        void setBoxDepth(float depth);
        float getBoxDepth();
        void setMotionType(GRADIENT_MOTION_TYPE motion);
        GRADIENT_MOTION_TYPE getMotionType();
        void setMoveDuration(float sec);
        float getMoveDuration();
        
        void setGradientColor(ofFloatColor c1);
        void setGradientColor(ofFloatColor c1, ofFloatColor c2);
        void setGradientColor(ofFloatColor c1, ofFloatColor c2, ofFloatColor c3);
        void setGradientColor(ofFloatColor c1, ofFloatColor c2, ofFloatColor c3, ofFloatColor c4);
        void setEllipseDivision(unsigned div);
        void setPoints(ofPoint p1, ofPoint p2, ofPoint p3);
        void setPoints(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4);
        
        std::vector<std::pair<ofPoint, ofFloatColor>> * getPointsData();
        
    private:
        std::vector<std::pair<ofPoint, ofFloatColor>> pts;
        GRADIENT_SHAPE frame_shape;
        GRADIENT_MOTION_TYPE frame_motion;
        GRADIENT_RECTANGLE_MOVE frame_move;
        float frame_duration;
        float frame_current;
        unsigned ellipse_division;
        bool bIgnite;
        bool bInMotion;
        
        ofxRHUtilities::PantoneColorSystem color_gen;
};


// MARK:- DelaunayedImage
struct triangle_data_t {
    ofPoint p1;
    ofPoint p2;
    ofPoint p3;
    ofColor color;
};

class DelaunayedImage {
    public:
        DelaunayedImage();
        ~DelaunayedImage();
        
        void load(ofImage * image);
        void load(ofPixels * pixels);
        void load(std::string image_file);
        
        void setRating(float zero_to_one); // zero: no filter, one: full filter
        float getRating();
        
        void draw(ofPoint x_y);
        void draw(float x, float y);
        void draw(ofPoint x_y, ofVec2f scale);
        void draw(float x, float y, float scale_x, float scale_y);
        
        std::vector<triangle_data_t> * getTriangles();
        ofMesh * getMesh();
        
    private:
        void generateTriangles();
        
        // referred
        // https://qiita.com/TatsuyaOGth/items/d4493446ba3e5e292753
        template <typename T>
        static cv::Mat toCv(ofPixels_<T>& pix)
        {
            int depth;
            switch(pix.getBytesPerChannel())
            {
                case 4: depth = CV_32F;
                case 2: depth = CV_16U;
                case 1: default: depth = CV_8U;
            }
            return cv::Mat(pix.getHeight(), pix.getWidth(),
                           CV_MAKETYPE(depth, pix.getNumChannels()), pix.getData(), 0);
        }
        
        cv::Ptr<cv::ORB> detector;
        std::vector<cv::KeyPoint> keypts;
        std::vector<triangle_data_t> triangles;
        cv::Subdiv2D subdiv;
        ofMesh mesh;
        ofPixels * pix;
        float rate;
};

// MARK:- NoiseForest
class NoiseForest {
    public:
        NoiseForest();
        ~NoiseForest();
        
        void setup();
        void update();
        void draw();
        
    private:
        ofVboMesh mesh;
        const unsigned k_mesh_size = 20;
        const unsigned k_mesh_interval = 100;
};

// MARK:- NightCity
class Buildings{
	public:
		struct building_data_t {
			ofVec3f startingPoint;
			float   currentHeight;
			float   orig_w, orig_d, orig_h;
			bool    bIsShrinking;
		};
		
	public:
		Buildings();
		~Buildings();
		
		void setBldgsNum(unsigned number);
		void setBldgsHeightRange(unsigned _lowest,
                                 unsigned _highest);
        void setSpeed(float _speed);
		void setPlaneSize(unsigned w, unsigned h);
		
		void setEdgeColor(ofColor color);
		void setBldgColor(ofColor color);
		
		void setup();
		
		void draw();
		void draw(float x, float y, float z);
		
	private:
		ofColor     bldgColor, edgeColor;
		unsigned    num;
		unsigned    widest, deepest;
		unsigned    lowest, highest;
		unsigned    planeWidth, planeHeight;
		float       speed;
		
		std::vector<building_data_t> bldgData;
};

class Stars{
	public:
		struct star_data_t {
			ofVec3f point;
			float   size;
		};
		
	public:
		Stars();
		~Stars();
		
		void setStarsNum(unsigned number);
		void setStarsColor(ofColor color);
		void setStarSizeRange(float _smallest, float _largest);
		void setRandomSizeChange(float mag);
		void setStarsDrawArea(float w, float h, float d);
		
		void setup();
		void setSpeed(ofVec3f dir);
		void setRandomBlink(bool blink);
		void draw();
		void draw(float x, float y, float z);
		
	private:
		ofColor starColor;
		ofVec3f direction;
		unsigned    num;
		bool        bBlinkingEnabled;
		
		float       smallest, largest;
		float       magnitude;
		float       area_w, area_h, area_d;
		
		std::vector<star_data_t> starsData;
};

class NightCity {
    public:
        NightCity();
        ~NightCity();
        
        void setup();
        void setup(ofVec3f fieldSize);
        void draw(float x, float y, float z);
        
    private:
        Buildings bldgs;
        Stars stars;
        ofVec3f field;
};

//// MARK:- BiquadTriangles
//class BiquadTriangles {
//    public:
//        BiquadTriangles();
//        ~BiquadTriangles();
//
//        void setup(std::vector<triangle_data_t> * data);
//        void update(float x, float y, float z);
//        void draw();
//
//        void setDistMax(float size);
//        float getDistMax();
//        void setFcMax(float size);
//        float getFcMax();
//
//    private:
//        std::vector<triangle_data_t> * triangles;
//        std::vector<ofxBiquadFilter3f> filt;
//        std::vector<ofVec3f> dist;
//        ofVec3f center;
//        float dist_max;
//        float fc_max;
//};

// MARK:- TriangleParticle
class TriangleParticle {
    private:
        ofVec3f direction;
        ofPoint center;
        ofPoint current;
        float distanceLimit;
        bool  isAlive;
        unsigned alphaDecrement;
        
        triangle_data_t tri_data;
        ofVec3f rotation;
        ofVec3f currentRot;
        
    public:
        TriangleParticle();
        ~TriangleParticle();
        
        void setup(ofVec3f dir_and_acc,
                   triangle_data_t & data,
                   float far_maximum,
                   ofVec3f rot_deg,
                   unsigned alpha_dec);
        bool update();
        void draw();
};
