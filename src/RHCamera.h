//
//  RHCamera.h
//
//  Created by Ryo Hajika on 30/12/20.
//

#pragma once

#include "ofEasyCam.h"
#include "easing.h"

namespace ofxRHUtilities {

// MARK:- EasingCamera
class EasingCamera : public ofEasyCam{
public:
    EasingCamera(){}
    ~EasingCamera(){}
    
    void setup(ofVec3f originalGlobalPosition,
               ofQuaternion originalGlobalOrientation){
        myCamGlobalPos.setGlobalPosition(originalGlobalPosition);
        myCamGlobalPos.setGlobalOrientation(originalGlobalOrientation);
        myCamDestPos = myCamGlobalPos;
        tweenVal = 0.0f;
    }
    void update(){
        if(tweenVal < 1.0f){
            tweenVal += updateVal;
        }
        
        setGlobalPosition(ofMap(easeOutExpo(tweenVal), 0.0, 1.0,
                                myCamGlobalPos.getGlobalPosition().x, myCamDestPos.getGlobalPosition().x),
                          ofMap(easeOutExpo(tweenVal), 0.0, 1.0,
                                myCamGlobalPos.getGlobalPosition().y, myCamDestPos.getGlobalPosition().y),
                          ofMap(easeOutExpo(tweenVal), 0.0, 1.0,
                                myCamGlobalPos.getGlobalPosition().z, myCamDestPos.getGlobalPosition().z));

        myCamCurrentLook.slerp(easeOutExpo(tweenVal),
                               myCamGlobalPos.getGlobalOrientation(),
                               myCamDestPos.getGlobalOrientation());

        setGlobalOrientation(myCamCurrentLook);
    }
    
    void setNextPhase(ofVec3f nextPos, ofVec3f nextLookAt){
        myCamGlobalPos = myCamDestPos;
        myCamDestPos.setGlobalPosition(nextPos);
        myCamGlobalPos.lookAt(nextLookAt);
        myCamDestPos.lookAt(nextLookAt);
        tweenVal = 0.0f;
    }
    void setUpdateDelta(float delta){
        updateVal = delta;
    }
    
private:
    ofNode          myCamGlobalPos;
    ofNode          myCamDestPos;
    ofQuaternion    myCamCurrentLook;
    float           tweenVal;
    float           updateVal;
};

}; // namespace ofxRHUtilities
