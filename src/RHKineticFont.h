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
    FONT_DRAW_BUBBLY,
    FONT_DRAW_TEXTURE
};

enum FONT_NOISE_SOURCE {
    FONT_NOISE_ELAPSEDTIMEF = 0,
    FONT_NOISE_ELAPSEDTIMEMILLIS,
    FONT_NOISE_ELAPSEDTIMEMICROS,
    FONT_NOISE_NOISE,
    FONT_NOISE_SIGNEDNOISE,
    FONT_NOISE_RANDOM,
    FONT_NOISE_VALUE
};

namespace RHKineticFont {
/*
 * Flow:
 * FontManagementSystem -> init
 * then add KineticFontBase based objects by addObject
 */

class KineticFontBase {
    public:
        virtual ~KineticFontBase() = 0;
        
        virtual void setup() = 0;
        virtual bool update(float noiseAmt) = 0;
        virtual void draw() = 0;
        
        virtual void setVanishMS(float time) = 0;
        virtual void setMovingDir(ofVec3f direction) = 0;
    private:
        unsigned _font_id;
};

//class FontManagementSystem {
//    public:
//        FontManagementSystem(){
//
//        }
//        ~FontManagementSystem(){
//
//        }
//
//        void setup(std::vector<ofTrueTypeFontSettings> settings){
//            for(ofTrueTypeFontSettings& setting : settings){
//                //this->setup(setting);
//            }
//        }
//        void setup(ofTrueTypeFontSettings settings){
//
//        }
//
//        void update(float noiseAmt){
//            for(KineticFontBase& object : _fontObjects){
//                object.update();
//            }
//        }
//
//        void draw(){
//            for(KineticFontBase& object : _fontObjects){
//                object.draw();
//            }
//        }
//
//        inline unsigned getRegisteredFontCount(){
//            return _fonts.size();
//        }
//
//
//    private:
//        void addFont(ofTrueTypeFontSettings setting){
//            _fonts.push_back(std::make_shared<ofTrueTypeFont>(setting));
//        }
//
//        std::vector<std::shared_ptr<ofTrueTypeFont>> _fonts;
//        std::vector<KineticFontBase> _fontObjects;
//};
//
//class SmokyFont : public KineticFontBase {
//    public:
//        SmokyFont(){
//
//        }
//        ~SmokyFont(){
//
//        }
//
//        void setup(){
//        }
//        bool update(float noiseAmt){
//        }
//        void draw(){
//        }
//
//        void setVanishMS(float time){
//        }
//        void setMovingDir(ofVec3f direction){
//        }
//};

};  // namespace RHKineticFont

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
        maxLineLength = std::max(maxLineLength, currentLineLength);
    }
    
    int padding = 4;
    int fontSize = 8;
    float leading = 1.7;
    int height = lines.size() * fontSize * leading - 1;
    int width = maxLineLength * fontSize;
    return ofRectangle(0, -fontSize-1, width, height);
}

// MARK:- FontComplex
class FontComplex {
    public:
        FontComplex();
        ~FontComplex();
        
        void setup(unsigned channels);
        unsigned getChannels();
        void loadString(unsigned which, vector<ofPath> path, ofRectangle bbox);
        void update(float elapsed_time_f, uint64_t elapsed_time_macros);
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
        ofVec3f update(float elapsed_time_f);
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
