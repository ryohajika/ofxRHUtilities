//
//  RHKineticFont.cpp
//  bonsai_for_yolkfest
//
//  Created by Ryo Hajika on 10/02/21.
//

#include "RHKineticFont.h"

// MARK:- FontComplex
FontComplex::FontComplex(){
    chs = 0;
    amp_vec.set(1,1,1);
    noise_amt = 0.f;
    wire_color.set(255);
    body_color.set(255);
    bounding_color.set(255);
    bgbody_color.set(0);
    bNoise = false;
    bBackground = false;
    random_fact = ofRandom(1000.f);
}

FontComplex::~FontComplex(){
    data.clear();
}

void FontComplex::setup(unsigned channels){
    chs = channels;
    if(data.size()){
        data.clear();
    }
    for(int i=0; i<chs; i++){
        font_complex_t f;
        f.mode = FONT_DRAW_WIREFRAME;
        data.push_back(f);
    }
}

unsigned FontComplex::getChannels(){
    return chs;
}

void FontComplex::loadString(unsigned which, vector<ofPath> path, ofRectangle bbox){
    if(which < chs){
        if(data[which].ps.size()){
            data[which].ps.clear();
        }
        data[which].ps = path;
        data[which].rect = bbox;
    }else{
        ofLogError("FontComplex", "Data channel out of range");
    }
}

void FontComplex::update(float elapsed_time_f, uint64_t elapsed_time_macros){
    for(int i=0; i<chs; i++){
        data[i].ms.clear();
        for(int j=0; j<data[i].ps.size(); j++){
            if(bSimplify){
                data[i].ps[j].simplify(simple_amt);
            }
            data[i].ms.push_back(data[i].ps[j].getTessellation());
        }
    }
    if(bNoise){
<<<<<<< HEAD
        float t = ofGetElapsedTimef();
        uint64_t tt = ofGetElapsedTimeMicros();
=======
        float t = elapsed_time_f;
        uint64_t tt = elapsed_time_macros;
>>>>>>> b6d973e1d9c7770016df181f2d9a5bee29bfb8bd
//        // http://www.cplusplus.com/forum/beginner/50659/
//        bool bool1, bool2, bool3 = true;
        
        for(int i=0; i<chs; i++){
            for(int j=0; j<data[i].ms.size(); j++){
                for(int k=0; k<data[i].ms[j].getVertices().size(); k++){
                    data[i].ms[j].getVertices()[k].x += ofSignedNoise(random_fact, t, k) * noise_amt;
                    data[i].ms[j].getVertices()[k].y += ofSignedNoise(random_fact, tt, k) * noise_amt;
                }
            }
        }
    }
}

void FontComplex::draw(unsigned ch){
//    float t = ofGetElapsedTimef();
//    unsigned tt = ofGetElapsedTimeMicros();
    
    if(ch < chs){
        ofPushMatrix();
        ofTranslate(data[ch].rect.width / -2.f,
                    data[ch].rect.height / -2.f,
                    0.0);
        ofScale(amp_vec);
            if(bBackground){
                ofPushStyle();
                    ofFill();
                    ofSetColor(bgbody_color);
                    ofDrawRectangle(data[ch].rect);
                    ofNoFill();
                    ofSetColor(bounding_color);
                    ofDrawRectangle(data[ch].rect);
                ofPopStyle();
            }
            ofPushStyle();
                for(auto m : data[ch].ms){
                    switch(data[ch].mode){
                        case FONT_DRAW_POINTS:
                            m.drawVertices();
                            break;
                        case FONT_DRAW_FILL:
                            m.drawFaces();
                            break;
                        case FONT_DRAW_WIREFRAME:
                            m.drawWireframe();
                            break;
                        case FONT_DRAW_TRIANGLES:
                            m.draw();
                            break;
                        default:
                            //tbd
                            break;
                    }
                }
            ofPopStyle();
        ofPopMatrix();
    }else{
        ofLogError("FontComplex", "Data channel out of range");
    }
}

void FontComplex::setNoiseAmt(float vol){
    noise_amt = vol;
}
float FontComplex::getNoiseAmt(){
    return noise_amt;
}

void FontComplex::setAspectVector(ofVec3f vol){
    amp_vec.set(vol.x, vol.y, vol.z);
}
ofVec3f FontComplex::getAspectVector(){
    return amp_vec;
}

void FontComplex::setWireColor(ofColor c){
    wire_color.set(c);
}
ofColor FontComplex::getWireCoolor(){
    return wire_color;
}

void FontComplex::setFaceColor(ofColor c){
    body_color.set(c);
}
ofColor FontComplex::getFaceColor(){
    return body_color;
}

void FontComplex::setBoundingBoxColor(ofColor c){
    bounding_color.set(c);
}
ofColor FontComplex::getBoundingBoxColor(){
    return bounding_color;
}

void FontComplex::setBackgroundColor(ofColor c){
    bgbody_color.set(c);
}
ofColor FontComplex::getBackgroundColor(){
    return bgbody_color;
}

void FontComplex::setNoiseEnable(bool state){
    bNoise = state;
}
bool FontComplex::getNoiseEnable(){
    return bNoise;
}

void FontComplex::setBackgroundEnable(bool state){
    bBackground = state;
}
bool FontComplex::getBackgroundEnable(){
    return bBackground;
}

void FontComplex::setSimplifyEnable(bool state){
    bSimplify = state;
}
bool FontComplex::getSimplifyEnable(){
    return bSimplify;
}

void FontComplex::setSimplifyRate(float vol){
    simple_amt = vol;
}
float FontComplex::getSimplifyRate(){
    return simple_amt;
}

void FontComplex::setDrawingMode(FONT_DRAW_MODE mode){
    for(int i=0; i<data.size(); i++){
        data[i].mode = mode;
    }
}

// MARK:- WordsSystem
WordsSystem::WordsSystem(){

}
WordsSystem::~WordsSystem(){
    cpx.clear();
    mvt.clear();
    words.clear();
}

void WordsSystem::setup(std::string font_path, std::string phrase, float interval_ms){
    // https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
    std::stringstream ss(phrase);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    words = std::vector<std::string>(begin, end);
    word_count = 0;
    
    itvl = interval_ms;
    bfre = ofGetElapsedTimef();
    bWordAddingPhase = true;
    
    font.load(font_path,
              64, true, true, true, 0.5f, 72);
}

<<<<<<< HEAD
ofVec3f WordsSystem::update(){
    float elapsed_time_f = ofGetElapsedTimef();
    
=======
ofVec3f WordsSystem::update(float elapsed_time_f){
//    cout << ofGetElapsedTimef() - bfre << endl;
    uint64_t elapsed_time_micros = ofGetElapsedTimeMicros();
	
>>>>>>> b6d973e1d9c7770016df181f2d9a5bee29bfb8bd
    if(bWordAddingPhase && (elapsed_time_f - bfre) > itvl){
        bfre = elapsed_time_f;
        cpx.push_back(FontComplex());
        cpx.back().setup(1);
        cpx.back().loadString(0,
                              font.getStringAsPoints(words[word_count], true, false),
                              font.getStringBoundingBox(words[word_count], 0, 0));
        cpx.back().setSimplifyEnable(true);
        cpx.back().setSimplifyRate(1.0);
        cpx.back().setBackgroundEnable(true);
        cpx.back().setNoiseEnable(true);
        cpx.back().setNoiseAmt(ofRandom(2.0, 7.0));
        cpx.back().setDrawingMode((FONT_DRAW_MODE)ofRandom(4));
        word_count++;
        
        object_movement_t m;
        m.spot.setGlobalPosition(0,0,0);
        m.amt.set(ofRandom(-6.,6.), ofRandom(-6.,6.), ofRandom(-6.,6.));
        m.delta = 1.0;
        m.isDead = false;
        mvt.push_back(m);
        if(cpx.size() > 1){
            cpx[cpx.size() - 2].setBackgroundEnable(false);
        }
        if((word_count + 1) == words.size()){
            word_count = 0;
            bWordAddingPhase = false;
        }
    }
    if(cpx.size()){
        for(int i=0; i<cpx.size(); i++){
            cpx[i].update(elapsed_time_f, elapsed_time_micros);
            if(!mvt[i].isDead){
                mvt[i].spot.setGlobalPosition(mvt[i].spot.getGlobalPosition().x + cos(mvt[i].delta * HALF_PI) * mvt[i].amt.x,
                                         mvt[i].spot.getGlobalPosition().y + sin(mvt[i].delta * HALF_PI) * mvt[i].amt.y,
                                         mvt[i].spot.getGlobalPosition().z + sin(mvt[i].delta * HALF_PI) * mvt[i].amt.z);
                mvt[i].delta -= 0.01;
                if(mvt[i].delta < 0.0001){
                    mvt[i].isDead = true;
                }
            }
        }
        return mvt.back().spot.getGlobalPosition();
    }
}

void WordsSystem::draw(){
    if(cpx.size()){
        for(int i=0; i<cpx.size(); i++){
            ofPushMatrix();
                ofTranslate(mvt[i].spot.getGlobalPosition());
                cpx[i].draw(0);
            ofPopMatrix();
            if(i > 0){
                ofDrawLine(mvt[i-1].spot.getGlobalPosition(),
                           mvt[i].spot.getGlobalPosition());
            }
        }
    }
}

void WordsSystem::reset(){
    cpx.clear();
    mvt.clear();
    word_count = 0;
}
