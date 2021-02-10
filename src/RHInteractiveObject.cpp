//
//  RHInteractiveObject.cpp
//
//  Created by Ryo Hajika on 16/08/20.
//

#include "RHInteractiveObject.h"


// MARK:- WeavyButterfly
WeavyButterfly::WeavyButterfly(){
    noises.resize(bts.size());
}
WeavyButterfly::~WeavyButterfly(){

}

void WeavyButterfly::setup(float size_w, float size_h, float size_d){
    scale.set(size_w, size_h, size_d);
    baseColor.set(100, 150, 200, 150);
    edgeColor.set(100, 200, 200);
}

void WeavyButterfly::update(float vol){
    noises.pop_front();
    noises.push_back(vol);
}

float WeavyButterfly::draw(){
    ofPushMatrix();
    ofScale(scale);
        drawBody();
        drawSmallWings(noises[0]);
        drawLargeWings(noises[5]);
    ofPopMatrix();
    
    return noises[0];
}

void WeavyButterfly::drawBody(){
    float t = ofGetElapsedTimef();
            
    ofPushStyle();
        ofSetColor(edgeColor);
        ofDrawSphere(0, 0.6, -noises[0]+noises[1]/3, 0.1);
        ofDrawSphere(0, 0.3, -noises[0], 0.1);
        ofPushMatrix();
        ofRotateXDeg(noises[5]*20);
        ofDrawCone(0, -0.2, -noises[0]-noises[5]/4, 0.1, 0.6);
        ofPopMatrix();
        ofPushMatrix();
        ofTranslate(0, 0.4, -noises[0]*1.3);
            for(int i=-1; i<2; i+=2){
                glBegin(GL_LINE_STRIP);
                    for(int j=0; j<8; j++){
                        float n = ofSignedNoise(t, j, i);
                        glVertex3f(j*i*0.1+(j>=2?n/10:0), bts[j].y+j/10, (bts[j].x+noises[j])/3+n/10);
                    }
                glEnd();
            }
        ofPopMatrix();
    ofPopStyle();
}

void WeavyButterfly::drawSmallWings(float angle){
    ofPushStyle();
    //ofPushMatrix();
        for(int i=-1; i<2; i+=2){
            ofPushMatrix();
                ofRotateYDeg(60*i*angle);
                ofRotateDeg(angle, 10, 0, i*10);
                ofTranslate(0, 0.4, 0);
                ofSetColor(baseColor);
                ofFill();
                glBegin(GL_POLYGON);
                {
                    for(int j=0; j<pts.size(); j++){
                        glVertex3f(pts[j].x, pts[j].y, i*noises[j]);
                    }
                }
                glEnd();
                ofSetColor(edgeColor);
                ofNoFill();
                glBegin(GL_TRIANGLE_FAN);
                {
                    for(int j=0; j<pts.size(); j++){
                        glVertex3f(pts[j].x, pts[j].y, i*noises[j]);
                    }
                }
                glEnd();
            ofPopMatrix();
            ofRotateDeg(180, 0, 1, 0);
        }
    //ofPopMatrix();
    ofPopStyle();
}

void WeavyButterfly::drawLargeWings(float angle){
    ofPushStyle();
    //ofPushMatrix();
        for(int i=-1; i<2; i+=2){
            ofPushMatrix();
                ofRotateYDeg(60*i*angle);
                ofRotateDeg(angle, 20, 0, i*20);
                ofTranslate(0, 0.2, 0);
                ofRotateZDeg(-25);
                ofSetColor(baseColor);
                ofFill();
                glBegin(GL_POLYGON);
                {
                    for(int j=0; j<bts.size(); j++){
                        glVertex3f(bts[j].x, bts[j].y, i*noises[j]);
                    }
                }
                glEnd();
                ofSetColor(edgeColor);
                ofNoFill();
                glBegin(GL_TRIANGLE_FAN);
                {
                    for(int j=0; j<bts.size(); j++){
                        glVertex3f(bts[j].x, bts[j].y, i*noises[j]);
                    }
                }
                glEnd();
            ofPopMatrix();
            ofRotateDeg(180, 0, 1, 0);
        }
    //ofPopMatrix();
    ofPopStyle();
}

// MARK:- ThreeDGridSystem
ThreeDGridSystem::ThreeDGridSystem(){
}

ThreeDGridSystem::~ThreeDGridSystem(){
    pts.clear();
    ptsidx.clear();
}

void ThreeDGridSystem::setup(ofVec3f gridspace, ofVec3f dotNumOnEachSide, float dotSize){
    gridSpaceSize.x = gridspace.x;
    gridSpaceSize.y = gridspace.y;
    gridSpaceSize.z = gridspace.z;
    dotNumbers.x = dotNumOnEachSide.x;
    dotNumbers.y = dotNumOnEachSide.y;
    dotNumbers.z = dotNumOnEachSide.z;
    lineLength = dotSize;
    
    intervalOnEachSide.x = gridSpaceSize.x / dotNumOnEachSide.x;
    intervalOnEachSide.y = gridSpaceSize.y / dotNumOnEachSide.y;
    intervalOnEachSide.z = gridSpaceSize.z / dotNumOnEachSide.z;
    
    unsigned ct = 0;
    for(int i=0; i<dotNumbers.x+2; i++){
        for(int j=0; j<dotNumbers.y; j++){
            for(int k=0; k<dotNumbers.z; k++){
                pts.push_back(glm::vec3(i*intervalOnEachSide.x-lineLength/2, j*intervalOnEachSide.y, k*intervalOnEachSide.z));
                pts.push_back(glm::vec3(i*intervalOnEachSide.x+lineLength/2, j*intervalOnEachSide.y, k*intervalOnEachSide.z));
                
                pts.push_back(glm::vec3(i*intervalOnEachSide.x, j*intervalOnEachSide.y-lineLength/2, k*intervalOnEachSide.z));
                pts.push_back(glm::vec3(i*intervalOnEachSide.x, j*intervalOnEachSide.y+lineLength/2, k*intervalOnEachSide.z));
                
                pts.push_back(glm::vec3(i*intervalOnEachSide.x, j*intervalOnEachSide.y, k*intervalOnEachSide.z-lineLength/2));
                pts.push_back(glm::vec3(i*intervalOnEachSide.x, j*intervalOnEachSide.y, k*intervalOnEachSide.z+lineLength/2));
                
                cout << ct << endl;
                for(int a=ct; a<ct+6; a++){
                    ptsidx.push_back(a);
                }
                ct+=6;
                cout << ct << endl;
            }
        }
    }
}

void ThreeDGridSystem::update(float transitionX){
    for(auto a : pts){
        a.x -= transitionX;
    }
    if(pts[0].x < -intervalOnEachSide.x){
        pts.erase(pts.begin(), pts.begin()+dotNumbers.y*dotNumbers.z-1);
        
        unsigned ct = (dotNumbers.x + 1) * dotNumbers.y * dotNumbers.z - 1;
        
        for(int j=0; j<dotNumbers.y; j++){
            for(int k=0; k<dotNumbers.z; k++){
                for(; ct<ct+6; ct++){
                    pts.push_back(glm::vec3(pts[ct].x, pts[ct].y, pts[ct].z+intervalOnEachSide.z));
                }
            }
        }
    }
}

void ThreeDGridSystem::draw(float x, float y, float z){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(x, y, z);
        glInterleavedArrays(GL_V3F, 0, pts.data());
        glDrawElements(GL_LINES, pts.size(), GL_UNSIGNED_INT, ptsidx.data());
    ofPopStyle();
    ofPopMatrix();
}

// MARK:- GradientElement
GradientElement::GradientElement(){
    frame_shape = GRADIENT_SHAPE_RECTANGLE;
    frame_motion = GRADIENT_MOTION_NONE;
    frame_move = GRADIENT_RECTANGLE_NONE;
    frame_duration = -1;
    frame_current = 0;
    ellipse_division = 16;
    bIgnite = false;
    bInMotion = false;
}
GradientElement::~GradientElement(){
    pts.clear();
}

void GradientElement::setup(GRADIENT_SHAPE shape,
                            float width, float height, float depth,
                            GRADIENT_MOTION_TYPE motion, float duration, bool bStart){
    frame_shape = shape;
    frame_motion = motion;
    frame_move = GRADIENT_RECTANGLE_NONE;
    frame_duration = duration;
    bIgnite = bStart;
    
    switch(frame_shape){
        case GRADIENT_SHAPE_RECTANGLE:
            {
                float x1 = -width / 2;
                float x2 = width / 2;
                float y1 = -height / 2;
                float y2 = height / 2;
                ofFloatColor c1 = color_gen.getRandomColor();
                ofFloatColor c2 = color_gen.getRandomColor();
                for(int i=0; i<4; i++){
                    pts.push_back(std::pair<ofPoint, ofFloatColor>());
                }
                pts[0].first.set(x1, y1);
                pts[1].first.set(x1, y2);
                pts[2].first.set(x2, y2);
                pts[3].first.set(x2, y1);
                pts[0].second = c1;
                pts[1].second = c2;
                pts[2].second = c2;
                pts[3].second = c1;
            }
            break;
        case GRADIENT_SHAPE_TRIANGLE:
            {
                float x1 = -width / 2;
                float x2 = width / 2;
                float y1 = -height / 2;
                float y2 = height / 2;
                unsigned first_corner = (unsigned)ofRandom(2);
                unsigned second_corner = (unsigned)ofRandom(4);
                ofFloatColor c1 = color_gen.getRandomColor();
                ofFloatColor c2 = color_gen.getRandomColor();
                ofFloatColor c3 = color_gen.getRandomColor();
                for(int i=0; i<3; i++){
                    pts.push_back(std::pair<ofPoint, ofFloatColor>());
                }
                switch(first_corner){
                    case 0:
                        {
                            pts[0].first.set(x1, y1);
                            if(second_corner == 0){
                                pts[1].first.set(x1, ofRandom(y1, y2));
                                pts[2].first.set(x2, ofRandom(y1, y2));
                            }
                            else if(second_corner == 1){
                                pts[1].first.set(ofRandom(x1, x2), y2);
                                pts[2].first.set(x2, ofRandom(y1, y2));
                            }
                            else if(second_corner == 2){
                                pts[1].first.set(ofRandom(x1, x2), y1);
                                pts[2].first.set(x2, ofRandom(y1, y2));
                            }
                            else if(second_corner == 3){
                                pts[1].first.set(ofRandom(x1, x2), y1);
                                pts[2].first.set(x2, ofRandom(y1, y2));
                            }
                        }
                        break;
                    case 1:
                        {
                            pts[0].first.set(x1, y2);
                            if(second_corner == 0){
                                pts[1].first.set(x1, ofRandom(y1, y2));
                                pts[2].first.set(x2, ofRandom(y1, y2));
                            }
                            else if(second_corner == 1){
                                pts[1].first.set(ofRandom(x1, x2), y2);
                                pts[2].first.set(x2, ofRandom(y1, y2));
                            }
                            else if(second_corner == 2){
                                pts[1].first.set(ofRandom(x1, x2), y1);
                                pts[2].first.set(x2, ofRandom(y1, y2));
                            }
                            else if(second_corner == 3){
                                pts[1].first.set(ofRandom(x1, x2), y1);
                                pts[2].first.set(x2, ofRandom(y1, y2));
                            }
                        }
                        break;
                }
                pts[0].second = c1;
                pts[1].second = c2;
                pts[2].second = c3;
            }
            break;
        case GRADIENT_SHAPE_ELLIPSE:
            {
                float angle = 360.0 / (float)ellipse_division;
                float half_width = width / 2;
                float half_height = height / 2;
                ofFloatColor c = color_gen.getRandomColor();
                for(float total_angle = 0.0f; total_angle < 360.0f; total_angle+=angle){
                    pts.push_back(std::pair<ofPoint, ofFloatColor>());
                    pts.back().first.set(cos(glm::radians(total_angle))*half_width,
                                         sin(glm::radians(total_angle))*half_height);
                    pts.back().second = c;
                }
            }
            break;
        case GRADIENT_SHAPE_BOX:
            {
                float x1 = -width / 2;
                float x2 = width / 2;
                float y1 = -height / 2;
                float y2 = height / 2;
                float z1 = depth / 2;
                float z2 = -depth / 2;
                ofFloatColor c1 = color_gen.getRandomColor();
                ofFloatColor c2 = color_gen.getRandomColor();
                for(int i=0; i<24; i++){
                    pts.push_back(std::pair<ofPoint, ofFloatColor>());
                }
                //top
                pts[0].first.set(x1, y1, z1);
                pts[1].first.set(x1, y2, z1);
                pts[2].first.set(x2, y2, z1);
                pts[3].first.set(x2, y1, z1);
                pts[0].second = c1;
                pts[1].second = c2;
                pts[2].second = c2;
                pts[3].second = c1;
                //bottom
                pts[4].first.set(x1, y1, z2);
                pts[5].first.set(x1, y2, z2);
                pts[6].first.set(x2, y2, z2);
                pts[7].first.set(x2, y1, z2);
                pts[4].second = c1;
                pts[5].second = c2;
                pts[6].second = c2;
                pts[7].second = c1;
                //left_side
                pts[8].first.set(x1, y1, z2);
                pts[9].first.set(x1, y2, z2);
                pts[10].first.set(x1, y2, z1);
                pts[11].first.set(x1, y1, z1);
                pts[8].second = c1;
                pts[9].second = c2;
                pts[10].second = c2;
                pts[11].second = c1;
                //right_side
                pts[12].first.set(x2, y1, z1);
                pts[13].first.set(x2, y2, z1);
                pts[14].first.set(x2, y2, z2);
                pts[15].first.set(x2, y1, z2);
                pts[12].second = c1;
                pts[13].second = c2;
                pts[14].second = c2;
                pts[15].second = c1;
                //top_side
                pts[16].first.set(x1, y1, z1);
                pts[17].first.set(x1, y1, z2);
                pts[18].first.set(x2, y1, z2);
                pts[19].first.set(x2, y1, z1);
                pts[16].second = c1;
                pts[17].second = c1;
                pts[18].second = c1;
                pts[19].second = c1;
                //bottom_side
                pts[20].first.set(x1, y2, z2);
                pts[21].first.set(x1, y2, z1);
                pts[22].first.set(x2, y2, z1);
                pts[23].first.set(x2, y2, z2);
                pts[20].second = c2;
                pts[21].second = c2;
                pts[22].second = c2;
                pts[23].second = c2;
            }
            break;
    }
}

void GradientElement::update(){
    if(bInMotion){
    
    }
}

void GradientElement::draw(ofPoint center_position){
    this->draw(center_position.x, center_position.y, center_position.z);
}

void GradientElement::draw(float center_x, float center_y, float center_z){
    ofPushMatrix();
    ofTranslate(center_x, center_y, center_z);
        switch(frame_shape){
            case GRADIENT_SHAPE_RECTANGLE:
            case GRADIENT_SHAPE_TRIANGLE:
            case GRADIENT_SHAPE_ELLIPSE:
                glBegin(GL_POLYGON);
                    for(auto & p : pts){
                        glColor4f(p.second.r, p.second.g, p.second.b, p.second.a);
                        glVertex3fv(p.first.getPtr());
                    }
                glEnd();
                break;
            case GRADIENT_SHAPE_BOX:
                glBegin(GL_QUADS);
                    for(auto & p : pts){
                        glColor4f(p.second.r, p.second.g, p.second.b, p.second.a);
                        glVertex3fv(p.first.getPtr());
                    }
                glEnd();
                break;
        }
    ofPopMatrix();
}

//void GradientElement::igniteAnimation();
//bool GradientElement::isAnimationActive();
//
//void GradientElement::setRectangleMoveType(GRADIENT_RECTANGLE_MOVE move);
//GRADIENT_RECTANGLE_MOVE GradientElement::getRectangleMoveType();
//void GradientElement::setBoxDepth(float depth);
//float GradientElement::getBoxDepth();
//void GradientElement::setMotionType(GRADIENT_MOTION_TYPE motion);
//GRADIENT_MOTION_TYPE GradientElement::getMotionType();
//void GradientElement::setMoveDuration(float sec);
//float GradientElement::getMoveDuration();
//
//void setGradientColor(ofFloatColor c1);
//void setGradientColor(ofFloatColor c1, ofFloatColor c2);
//void setGradientColor(ofFloatColor c1, ofFloatColor c2, ofFloatColor c3);
//void setGradientColor(ofFloatColor c1, ofFloatColor c2, ofFloatColor c3, ofFloatColor c4);
//
//void setRadius(float radius_px);
//void setPoints(ofPoint p1, ofPoint p2, ofPoint p3);
//void setPoints(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4);
//
//std::vector<std::pair<ofPoint, ofColor>> * GradientElement::getPointsData()


// MARK:- DelaunayedImage
DelaunayedImage::DelaunayedImage(){
    detector = cv::ORB::create();
    keypts.resize(0);
    triangles.resize(0);
    rate = 1.0f;
}
DelaunayedImage::~DelaunayedImage(){
    detector.release();
//    delaunay.reset();
    mesh.clear();
    keypts.clear();
    triangles.clear();
}

void DelaunayedImage::load(ofImage * image){
    this->load(&image->getPixels());
}
void DelaunayedImage::load(ofPixels * pixels){
    pix = pixels;
    
    if(keypts.size()) keypts.clear();
    detector->detect(toCv(*pix), keypts);
    this->generateTriangles();
}
void DelaunayedImage::load(std::string image_file){
    ofImage img;
    img.load(image_file);
    this->load(&img);
}

void DelaunayedImage::setRating(float zero_to_one){
    rate = 1.0 - zero_to_one;
}
float DelaunayedImage::getRating(){
    return 1.0 - rate;
}

void DelaunayedImage::draw(ofPoint x_y){
    this->draw(x_y.x, x_y.y, 1.0, 1.0);
}
void DelaunayedImage::draw(float x, float y){
    this->draw(x, y, 1.0, 1.0);
}
void DelaunayedImage::draw(ofPoint x_y, ofVec2f scale){
    this->draw(x_y.x, x_y.y, scale.x, scale.y);
}
void DelaunayedImage::draw(float x, float y, float scale_x, float scale_y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale_x, scale_y, 1.0);
        mesh.drawFaces();
//        delaunay.getMesh()->drawFaces();
    glPopMatrix();
    glColor3f(1, 1, 1);
}

void DelaunayedImage::generateTriangles(){
    cv::Rect cvRect(0,0,pix->getWidth(),pix->getHeight());
    subdiv.initDelaunay(cvRect);
    if(triangles.size()) triangles.clear();
    
    subdiv.insert(cv::Point2f(1,1));
    subdiv.insert(cv::Point2f(1,(int)pix->getHeight()-1));
    subdiv.insert(cv::Point2f((int)pix->getWidth()-1,(int)pix->getHeight()-1));
    subdiv.insert(cv::Point2f((int)pix->getWidth()-1,1));
    
    unsigned interval = (int)keypts.size() / ((int)keypts.size() * rate);
    
    for(int i=0; i<keypts.size(); i+=interval){
        subdiv.insert(keypts[i].pt);
    }
    unsigned ctr = 0;
    std::vector<cv::Vec6f> pts;
    subdiv.getTriangleList(pts);
    for(cv::Vec6f & v : pts){
        if(cvRect.contains(cv::Point(v[0], v[1]))
            && cvRect.contains(cv::Point(v[2], v[3]))
            && cvRect.contains(cv::Point(v[4], v[5]))){
                triangles.push_back(triangle_data_t());
                triangles.back().p1.set(v[0], v[1]);
                triangles.back().p2.set(v[2], v[3]);
                triangles.back().p3.set(v[4], v[5]);
                float region_x, region_y, region_w, region_h = 0;
                region_x = std::min(v[0], v[2]);
                region_x = std::min(v[4], region_x);
                region_y = std::min(v[1], v[3]);
                region_y = std::min(v[5], region_y);
                region_w = std::max(v[0], v[2]);
                region_w = std::max(v[4], region_w) - region_x;
                region_h = std::max(v[1], v[3]);
                region_h = std::max(v[5], region_h) - region_y;
                if(region_w * region_h > 2){
                    ofPixels sample;
                    pix->cropTo(sample, region_x, region_y, region_w, region_h);
                    cv::Mat samp;
                    toCv(sample).convertTo(samp, CV_32F);
                    samp = samp.reshape(1, samp.total());
                    cv::Mat labels, centers;
                    cv::kmeans(samp, 2, labels, cv::TermCriteria(CV_TERMCRIT_ITER, 10, 1.0), 1,
                               cv::KMEANS_PP_CENTERS, centers);
                    centers = centers.reshape(1, centers.rows);
                    triangles.back().color.set(centers.at<cv::Vec3f>(0,0)[0],
                                               centers.at<cv::Vec3f>(0,0)[1],
                                               centers.at<cv::Vec3f>(0,0)[2]);
                }else{
                    triangles.back().color.set(pix->getColor(region_x, region_y));
                }
            }
        }
        
        mesh.clear();
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        for(auto & t : triangles){
            mesh.addColors({t.color,t.color,t.color});
            mesh.addVertices({t.p1, t.p2, t.p3});
        }
    //}
    return;
}

std::vector<triangle_data_t> * DelaunayedImage::getTriangles(){
    return &triangles;
}

inline ofMesh * DelaunayedImage::getMesh(){
    return &mesh;
//    return delaunay.getMesh();
}


// MARK:- NoiseForest
NoiseForest::NoiseForest(){

}
NoiseForest::~NoiseForest(){
    mesh.clear();
}

void NoiseForest::setup(){
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    float et = ofGetElapsedTimef();
    for(int i=0; i<k_mesh_size; i++){
        for(int j=0; j<k_mesh_size; j++){
            mesh.addVertex(ofVec3f((i*k_mesh_interval, ofSignedNoise(i+j, et/10)*50, j*k_mesh_interval)));
            mesh.addColor(ofFloatColor(ofNoise(i*j, i*80+j),ofNoise(i*j, i+j*90),ofNoise(i*j, i*100+j*100),0.3));
        }
    }
    for(int i=0; i<k_mesh_size-1; i++){
        for(int j=0; j<k_mesh_size; j++){
            if(!(i%2)){	//even
                if(i!=0){
                    if(j==0){
                        mesh.addIndex(j+i*k_mesh_size);
                        mesh.addIndex(j+1+i*k_mesh_size);
                        mesh.addIndex(j+(i+1)*k_mesh_size);
                        mesh.addIndex(j+1+(i+1)*k_mesh_size);
                    }else{
                        mesh.addIndex(j+i*k_mesh_size);
                        mesh.addIndex(j+(i+1)*k_mesh_size);
                    }
                }else{
                    mesh.addIndex(j+i*k_mesh_size);
                    mesh.addIndex(j+(i+1)*k_mesh_size);
                }
            }else{		//odd
                if(j==0){
                    mesh.addIndex(k_mesh_size-1+i*k_mesh_size);
                    mesh.addIndex(k_mesh_size-2+i*k_mesh_size);
                    mesh.addIndex(k_mesh_size-1+(i+1)*k_mesh_size);
                    mesh.addIndex(k_mesh_size-2+(i+1)*k_mesh_size);
                }else{
                    mesh.addIndex(k_mesh_size-1-j+i*k_mesh_size);
                    mesh.addIndex(k_mesh_size-1-j+(i+1)*k_mesh_size);
                }
            }
        }
    }
}

void NoiseForest::update(){
    float t = ofGetElapsedTimef();
    
    for(int i=0; i<k_mesh_size; i++){
        for(int j=0; j<k_mesh_size; j++){
            mesh.getVertices()[i*k_mesh_size+j] = ofVec3f(j*k_mesh_interval,
                                                          ofSignedNoise(i+j,t/10)*50*ofSignedNoise(i+5,t/100)*100,
                                                          i*k_mesh_interval);
        }
    }
}

void NoiseForest::draw(){
    mesh.draw();
}

// MARK:- NightCity
Buildings::Buildings(){
    bldgColor.set(ofColor::black);
    edgeColor.set(ofColor::white);
    
    num = 200;
    widest = 100;
    deepest = 100;
    lowest = 10;
    highest = 400;
    planeWidth = 1000;
    planeHeight = 1000;
    
    speed = 10.0f;
}
Buildings::~Buildings(){
    if(bldgData.size()) bldgData.clear();
}

void Buildings::setBldgsNum(unsigned number){
    num = number;
}

void Buildings::setBldgsHeightRange(unsigned _lowest, unsigned _highest){
    lowest = _lowest;
    highest = _highest;
}

void Buildings::setEdgeColor(ofColor color){
    edgeColor = color;
}

void Buildings::setBldgColor(ofColor color){
    bldgColor = color;
}

void Buildings::setSpeed(float _speed){
    speed = _speed;
}

void Buildings::setPlaneSize(unsigned w, unsigned h){
    planeWidth = w;
    planeHeight = h;
}

void Buildings::setup(){
    if(bldgData.size()) bldgData.clear();
    
    for(int i = 0; i < num; i++){
        bldgData.push_back(building_data_t());
        if(i%2){
            bldgData.back().startingPoint.set(ofRandom(planeWidth/2-100),
                                              0,
                                              ofRandom(planeHeight));
        }else{
            bldgData.back().startingPoint.set(ofRandom(planeWidth/2+100, planeWidth),
                                              0,
                                              ofRandom(planeHeight));
        }
        bldgData[i].orig_w = ofRandom(10, widest);
        bldgData[i].orig_d = ofRandom(10, deepest);
        bldgData[i].orig_h = ofRandom(lowest, highest);
        bldgData[i].currentHeight = 0.0;
    }
}

void Buildings::draw(){
    ofPushStyle();
    glEnable(GL_DEPTH_TEST);
    
    for(int i = 0; i < num; i++){
        if(bldgData[i].startingPoint.z > planeHeight){
            bldgData[i].startingPoint.z = 0;
        }else{
            bldgData[i].startingPoint.z++;
        }
        
        if(bldgData[i].startingPoint.z < sqrt(bldgData[i].orig_h)){
            bldgData[i].currentHeight = powf(bldgData[i].startingPoint.z, 2);
        }
        else if(planeHeight-bldgData[i].startingPoint.z < sqrt(bldgData[i].orig_h)){
            bldgData[i].currentHeight = powf(planeHeight - bldgData[i].startingPoint.z, 2);
        }
        
        ofPushMatrix();
        ofTranslate(bldgData[i].startingPoint);
        ofSetColor(bldgColor);
        ofFill();
        ofDrawBox(0, bldgData[i].currentHeight/2, 0,
                  bldgData[i].orig_w, -bldgData[i].currentHeight, bldgData[i].orig_d);
        ofSetColor(edgeColor);
        ofNoFill();
        ofDrawBox(0, bldgData[i].currentHeight/2, 0,
                  bldgData[i].orig_w, -bldgData[i].currentHeight, bldgData[i].orig_d);
        ofPopMatrix();
    }
    
    glDisable(GL_DEPTH_TEST);
    ofPopStyle();
}

void Buildings::draw(float x, float y, float z){
    ofPushMatrix();
    ofTranslate(x, y, z);
    this->draw();
    ofPopMatrix();
}

Stars::Stars(){
    starColor.set(ofColor::white);
    direction.set(0, 1, 2);
    num = 100;
    
    smallest = 1;
    largest = 5;
    magnitude = 0.5;
    
    area_w = 1000.f;
    area_h = 500.f;
    area_d = 1000.f;
    
    bBlinkingEnabled = false;
}

Stars::~Stars(){
    if(starsData.size()) starsData.clear();
}

void Stars::setStarsNum(unsigned number){
    num = number;
}

void Stars::setStarsColor(ofColor color){
    starColor = color;
}

void Stars::setStarSizeRange(float _smallest, float _largest){
    smallest = _smallest;
    largest = _largest;
}

void Stars::setRandomSizeChange(float mag){
    magnitude = mag;
}

void Stars::setStarsDrawArea(float w, float h, float d){
    area_w = w;
    area_h = h;
    area_d = d;
}

void Stars::setup(){
    if(starsData.size()) starsData.clear();
    
    for(int i = 0; i < num; i++){
        starsData.push_back(star_data_t());
        starsData.back().size = ofRandom(smallest, largest);
        starsData.back().point.set(ofRandom(area_w),
                                   ofRandom(area_h),
                                   ofRandom(area_d));
    }
}

void Stars::setSpeed(ofVec3f dir){
    direction = dir;
}

void Stars::setRandomBlink(bool blink){
    bBlinkingEnabled = blink;
}

void Stars::draw(){
    ofPushStyle();
    glEnable(GL_DEPTH_TEST);
    ofSetColor(starColor);
    
    for(int i = 0; i < num; i++){
        if(starsData[i].point.y < area_h){
            starsData[i].point.y += direction.y;
        }else{
            starsData[i].point.y = 0;
        }
        
        if(starsData[i].point.z > area_d){
            starsData[i].point.z = 0;
        }else{
            starsData[i].point.z += direction.z;
        }
        
        bBlinkingEnabled ? ofDrawSphere(starsData[i].point,
                                        starsData[i].size*ofRandom(magnitude))
                         : ofDrawSphere(starsData[i].point, starsData[i].size);
    }
    
    glDisable(GL_DEPTH_TEST);
    ofPopStyle();
}

void Stars::draw(float x, float y, float z){
    ofPushMatrix();
    ofTranslate(x, y, z);
    this->draw();
    ofPopMatrix();
}


NightCity::NightCity(){
    field.set(2000.f,1000.f,4000.f);
}
NightCity::~NightCity(){

}
void NightCity::setup(){
    this->setup(field);
}
void NightCity::setup(ofVec3f fieldSize){
    bldgs.setPlaneSize(fieldSize.x, fieldSize.z);
    bldgs.setup();
    
    stars.setSpeed(ofVec3f(0, 1, 3));
    stars.setStarsDrawArea(fieldSize.x, fieldSize.y, fieldSize.z);
    stars.setStarSizeRange(3.0, 8.0);
    stars.setStarsNum(80);
    stars.setup();
}
void NightCity::draw(float x, float y, float z){
    ofPushMatrix();
    ofTranslate(x,y,z);
        bldgs.draw();
        stars.draw();
    ofPopMatrix();
}

//// MARK:- BiquadTriangles
//BiquadTriangles::BiquadTriangles(){
//    dist_max = 100.;
//    fc_max = 2.;
//}
//BiquadTriangles::~BiquadTriangles(){
//    filt.clear();
//    dist.clear();
//}
//
//void BiquadTriangles::setup(std::vector<triangle_data_t> * data){
//    triangles = data;
//    for(int i=0; i<triangles->size(); i++){
//        filt.push_back(ofxBiquadFilter3f());
//        dist.push_back(ofVec3f());
//        unsigned mode = (unsigned)ofRandom(4);
//        switch(mode){
//            case 0:
//                filt.back().setType(OFX_BIQUAD_TYPE_LOWPASS);
//                break;
//            case 1:
//                filt.back().setType(OFX_BIQUAD_TYPE_HIGHPASS);
//                break;
//            case 2:
//                filt.back().setType(OFX_BIQUAD_TYPE_BANDPASS);
//                break;
//            case 3:
//                filt.back().setType(OFX_BIQUAD_TYPE_NOTCH);
//                break;
//        }
//        filt.back().setFc(ofRandom(fc_max));
//        dist.back().set(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
//        dist.back() *= dist_max;
//    }
//}
//void BiquadTriangles::update(float x, float y, float z){
//    center.set(x, y, z);
//    for(int i=0; i<filt.size(); i++){
//        filt[i].update(dist[i]+center);
//    }
//}
//void BiquadTriangles::draw(){
//    ofPushStyle();
//    ofVec3f point;
//    for(int i=0; i<triangles->size(); i++){
//        ofVec3f pts[3] = {triangles->at(i).p1, triangles->at(i).p2, triangles->at(i).p3};
//        point.average(pts, 3);
//        ofSetColor(triangles->at(i).color);
//        ofPushMatrix();
//        ofTranslate(filt[i].value());
//        ofDrawTriangle(triangles->at(i).p1-point, triangles->at(i).p2-point, triangles->at(i).p3-point);
//        ofPopMatrix();
//    }
//    ofPopStyle();
//}
//
//void BiquadTriangles::setDistMax(float size){
//    dist_max = size;
//}
//float BiquadTriangles::getDistMax(){
//    return dist_max;
//}
//void BiquadTriangles::setFcMax(float size){
//    fc_max = size;
//}
//float BiquadTriangles::getFcMax(){
//    return fc_max;
//}


// MARK:- TriangleParticle
TriangleParticle::TriangleParticle(){};
TriangleParticle::~TriangleParticle(){};

void TriangleParticle::setup(ofVec3f dir_and_acc,
                             triangle_data_t & data,
                             float far_maximum,
                             ofVec3f rot_deg,
                             unsigned alpha_dec){
    direction = dir_and_acc;
    center = (data.p1+data.p2+data.p3)/3;
    current = center;
    distanceLimit = far_maximum;
    tri_data.color = data.color;
    currentRot.set(0.,0.,0.);
    rotation = rot_deg;
    alphaDecrement = alpha_dec;
    tri_data.p1.set(data.p1-center);
    tri_data.p2.set(data.p2-center);
    tri_data.p3.set(data.p3-center);
    isAlive = true;
}

bool TriangleParticle::update(){
    if(tri_data.color.a > 0){
        tri_data.color.a -= alphaDecrement;
    }
    if(current.distance(center) > distanceLimit &&
       tri_data.color.a == 0){
        isAlive = false;
        return false;
    }else{
        current += direction;
        currentRot += rotation;
        return true;
    }
}

void TriangleParticle::draw(){
    if(isAlive){
        ofPushMatrix();
        ofPushStyle();
            ofTranslate(current);
            ofSetColor(tri_data.color);
            ofRotateXDeg(currentRot.x);
            ofRotateYDeg(currentRot.y);
            ofRotateZDeg(currentRot.z);
            ofDrawTriangle(tri_data.p1, tri_data.p2, tri_data.p3);
        ofPopStyle();
        ofPopMatrix();
    }
}
