//
//  RHCamera.h
//
//  Created by Ryo Hajika on 30/12/20.
//

#pragma once

#include "ofEasyCam.h"

namespace ofxRHUtilities {


// From ofxAnimationPrimitives by Satoru Higa
// https://github.com/satoruhiga/ofxAnimationPrimitives
// I putted "static" in order to avoid the confusion with
// the original implementation when you use this alongside
// ofxAnimationPrimitives in your project

static struct Expo
{
	inline static float easeIn(const float t)
	{
		return powf(2, 10 * (t - 1));
	}
	
	inline static float easeOut(const float t)
	{
		return 1.0 - powf(2, -10 * t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

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
        
        setGlobalPosition(ofMap(tween.easeOut(tweenVal), 0.0, 1.0,
                                myCamGlobalPos.getGlobalPosition().x, myCamDestPos.getGlobalPosition().x),
                          ofMap(tween.easeOut(tweenVal), 0.0, 1.0,
                                myCamGlobalPos.getGlobalPosition().y, myCamDestPos.getGlobalPosition().y),
                          ofMap(tween.easeOut(tweenVal), 0.0, 1.0,
                                myCamGlobalPos.getGlobalPosition().z, myCamDestPos.getGlobalPosition().z));

        myCamCurrentLook.slerp(tween.easeOut(tweenVal),
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
    ofxRHUtilities::Expo    tween;
    ofNode          myCamGlobalPos;
    ofNode          myCamDestPos;
    ofQuaternion    myCamCurrentLook;
    float           tweenVal;
    float           updateVal;
};

}; // namespace ofxRHUtilities
