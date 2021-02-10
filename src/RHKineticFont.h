//
//  RHKineticFont.h
//  bonsai_for_yolkfest
//
//  Created by Ryo Hajika on 10/02/21.
//

#include "ofMain.h"

enum FONT_DRAW_MODE {
    FONT_DRAW_POINTS = 0,
    FONT_DRAW_FILL,
    FONT_DRAW_WIREFRAME,
    FONT_DRAW_TRIANGLES,
    FONT_DRAW_TEXTURE
};

struct font_complex_t {
    vector<ofPath> ps;
    vector<ofMesh> ms;
    ofRectangle rect;
    FONT_DRAW_MODE mode;
};

struct object_movement_t {
    ofNode spot;
    ofVec3f amt;
    float delta;
    bool isDead;
};

// https://forum.openframeworks.cc/t/how-to-get-size-of-ofdrawbitmapstring/22578/6
static ofRectangle getBitmapStringBoundingBox(std::string text){
    std::vector<std::string> lines = ofSplitString(text, "\n");
    int maxLineLength = 0;
    for(int i = 0; i < (int)lines.size(); i++) {
        // tabs are not rendered
        const string & line(lines[i]);
        int currentLineLength = 0;
        for(int j = 0; j < (int)line.size(); j++) {
            if (line[j] == '\t') {
                currentLineLength += 8 - (currentLineLength % 8);
            } else {
                currentLineLength++;
            }
        }
        maxLineLength = MAX(maxLineLength, currentLineLength);
    }
    
    int padding = 4;
    int fontSize = 8;
    float leading = 1.7;
    int height = lines.size() * fontSize * leading - 1;
    int width = maxLineLength * fontSize;
    return ofRectangle(0,-fontSize-1,width, height);
}

// MARK:- FontComplex
class FontComplex {
    public:
        FontComplex();
        ~FontComplex();
        
        void setup(unsigned channels);
        unsigned getChannels();
        void loadString(unsigned which, vector<ofPath> path, ofRectangle bbox);
        void update();
        void draw(unsigned ch);
        
        void setNoiseAmt(float vol);
        float getNoiseAmt();
        
        void setAspectVector(ofVec3f vol);
        ofVec3f getAspectVector();
        
        void setWireColor(ofColor c);
        ofColor getWireCoolor();
        
        void setFaceColor(ofColor c);
        ofColor getFaceColor();
        
        void setBoundingBoxColor(ofColor c);
        ofColor getBoundingBoxColor();
        
        void setBackgroundColor(ofColor c);
        ofColor getBackgroundColor();
        
        void setNoiseEnable(bool state);
        bool getNoiseEnable();
        
        void setBackgroundEnable(bool state);
        bool getBackgroundEnable();
        
        void setSimplifyEnable(bool state);
        bool getSimplifyEnable();
        void setSimplifyRate(float vol);
        float getSimplifyRate();
        
        void setDrawingMode(FONT_DRAW_MODE mode);
        
    private:
        vector<font_complex_t> data;
        unsigned chs;
        ofVec3f amp_vec;
        ofColor wire_color;
        ofColor body_color;
        ofColor bounding_color;
        ofColor bgbody_color;
        bool bNoise;
        bool bBackground;
        bool bSimplify;
        float noise_amt;
        float simple_amt;
        float random_fact;
};

// MARK:- WordsSystem
class WordsSystem {
    public:
        WordsSystem();
        ~WordsSystem();
        
        void setup(std::string font_path, std::string phrase, float interval_ms);
        ofVec3f update();
        void draw();
        void reset();
    
    private:
        ofTrueTypeFont font;
        std::vector<FontComplex> cpx;
        std::vector<object_movement_t> mvt;
        std::vector<std::string> words;
        float itvl;
        float bfre;
        unsigned word_count;
        bool bWordAddingPhase;
};
