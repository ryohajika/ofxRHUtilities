//
//  RHColors.h
//
//  Created by Ryo Hajika on 30/12/20.
//

#pragma once

#include <vector>
#include "ofColor.h"

namespace ofxRHUtilities {

// MARK:- PantoneColorSystem
class PantoneColorSystem {
    public:
        // Pantone's color of year for the last 20 years
        ofFloatColor cerulean = ofColor(152, 180, 212, 150);        // CotY 2000
        ofFloatColor fuchsia_rose = ofColor(195, 68, 122, 150);     // 2001
        ofFloatColor true_red = ofColor(188, 36, 60, 150);          // 2002
        ofFloatColor aqua_sky = ofColor(127, 205, 205, 150);        // 2003
        ofFloatColor tigerlily = ofColor(226, 88, 62, 150);         // 2004
        ofFloatColor blue_turquoise = ofColor(83, 176, 174, 150);   // 2005
        ofFloatColor sand_dollar = ofColor(223, 207, 190, 150);     // 2006
        ofFloatColor chili_pepper = ofColor(155, 35, 53, 150);      // 2007
        ofFloatColor blue_iris = ofColor(91, 94, 166, 150);         // 2008
        ofFloatColor mimosa = ofColor(239, 192, 80, 150);           // 2009
        ofFloatColor turquoise = ofColor(69, 184, 172, 150);        // 2010
        ofFloatColor honeysuckle = ofColor(214, 80, 118, 150);      // 2011
        ofFloatColor tangerine_tango = ofColor(221, 65, 36, 150);   // 2012
        ofFloatColor emerald = ofColor(0, 152, 116, 150);           // 2013
        ofFloatColor radiant_orchid = ofColor(173, 94, 153, 150);   // 2014
        ofFloatColor marsala = ofColor(150, 79, 76, 150);           // 2015
        ofFloatColor serenity = ofColor(147, 169, 209, 150);        // 2016 - 1
        ofFloatColor rose_quartz = ofColor(247, 202, 202, 150);     // 2016 - 2
        ofFloatColor greenery = ofColor(136, 176, 75, 150);         // 2017
        ofFloatColor ultra_violet = ofColor(95, 75, 139, 150);      // 2018
        ofFloatColor living_coral = ofColor(250, 114, 104, 150);    // 2019
        ofFloatColor classic_blue = ofColor(15, 76, 129, 150);      // 2020
        ofFloatColor ultimate_gray = ofColor(147, 149, 151, 150);   // 2021 - 1
        ofFloatColor illuminating = ofColor(245, 223, 77, 150);     // 2021 - 2

        PantoneColorSystem(){
            colors.push_back(cerulean);
            colors.push_back(fuchsia_rose);
            colors.push_back(true_red);
            colors.push_back(aqua_sky);
            colors.push_back(tigerlily);
            colors.push_back(blue_turquoise);
            colors.push_back(sand_dollar);
            colors.push_back(chili_pepper);
            colors.push_back(blue_iris);
            colors.push_back(mimosa);
            colors.push_back(turquoise);
            colors.push_back(honeysuckle);
            colors.push_back(tangerine_tango);
            colors.push_back(emerald);
            colors.push_back(radiant_orchid);
            colors.push_back(marsala);
            colors.push_back(serenity);
            colors.push_back(rose_quartz);
            colors.push_back(greenery);
            colors.push_back(ultra_violet);
            colors.push_back(living_coral);
            colors.push_back(classic_blue);
            colors.push_back(ultimate_gray);
            colors.push_back(illuminating);
        }
        ~PantoneColorSystem(){
            colors.erase(colors.begin(), colors.end());
        }
        ofFloatColor getRandomColor(){
            return colors[(unsigned)ofRandom(colors.size())];
        }
        ofFloatColor getRandomMixedColor(){
            return this->getRandomColor().lerp(this->getRandomColor(), 0.5);
        }
    private:
        std::vector<ofFloatColor> colors;
};

}; // namespace ofxRHUtilities
