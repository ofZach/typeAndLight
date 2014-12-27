#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    
    font.loadFont("Apercu-Bold.otf", 150, true, false, true);
    
    
    vector<ofTTFCharacter> chars = font.getStringAsPoints("2015");
    for (int i = 0; i < chars.size(); i++){
        vector < ofPolyline > temp = chars[i].getOutline();
        lines.insert(lines.end(), temp.begin(), temp.end());
    }
    for (int i= 0; i < lines.size(); i++){
        for (int j = 0; j < lines[i].size(); j++){
            lines[i][j] += ofPoint(100, 500);
            
            //lines[i][j] = lines[i]
        }
        
        lines[i] = lines[i].getResampledBySpacing(1.0);
        //lines[i] = lines[i].getSmoothed(3);
    }
    
    float width = ofGetWidth();
    float height = ofGetHeight();
    borders.addVertex( ofPoint(0,0));
    borders.addVertex( ofPoint(width,0));
    borders.addVertex( ofPoint(width, height));
    borders.addVertex( ofPoint(0,height));
    borders.addVertex( ofPoint(0,0));
    
    borders2 = borders;
    borders2 = borders2.getResampledByCount(ofGetWidth());
    
}

//--------------------------------------------------------------
void ofApp::update(){

}



ofPoint ofApp::randomPtForSize(ofRectangle rect, int side){
    
    ofPoint aa = ofPoint(rect.x, rect.y);
    ofPoint bb = ofPoint(rect.x + rect.width, rect.y);
    ofPoint cc = ofPoint(rect.x + rect.width, rect.y + rect.height);
    ofPoint dd = ofPoint(rect.x, rect.y + rect.height);
    
    if (side == 0){
        return aa + ofRandom(0,1) * (bb-aa);
    } else if (side == 1){
        return bb + ofRandom(0,1) * (cc-bb);
    } else if (side == 2){
        return cc + ofRandom(0,1) * (dd-cc);
    } else {
        return dd + ofRandom(0,1) * (aa-dd);
    }
    return ofPoint(0,0);

}


ofPoint  reflect(ofPoint vector, ofPoint normal)
{
    return vector - 2 * normal.dot(vector) * normal;
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    
   if (ofGetMousePressed())ofBackground(0);
    
    
    cout << ofGetFrameRate() << endl;
    
    //ofSetColor(255,255,255,180);
    
    
    //ofSeedRandom(mouseX);
    
    
    
    ofRectangle rect(0,0,ofGetWidth(), ofGetHeight());
    
    for (int z = 0; z < 100; z ++){
    int side = ofRandom(0,4);
    int sideb = ofRandom(0,4);
    
    if (side != sideb){
        
        ofPoint a = borders2[ (mouseX+borders2.size()/2) % borders2.size() ]; // //borders2[ mouseX % borders2.size() ];; //borders2[  ]; //ofPoint(0, mouseY); ///randomPtForSize(rect, side);
        ofPoint b = randomPtForSize(rect, side); //ofPoint(ofGetWidth(), mouseY); ///randomPtForSize(rect, sideb);
        
        
        bool bNoMoreIntersects = false;
        int count = 0;
        while (!bNoMoreIntersects && count < 100){
            
            bool bIntersectsWord = false;
            float minDistance = 10000000;
            ofPoint pos;
            ofPoint newAngle;
            float angleIntersection;
            ofPoint perp;
            
            for (int i= 0; i < lines.size(); i++){
                for (int j = 0; j < lines[i].size()-1; j++){
                
                    ofPoint intersection;
                    
                    if (ofLineSegmentIntersection(a, b, lines[i][j], lines[i][j+1], intersection)){
                        float distance = (a - intersection).length();
                        if (distance > 0.01){
                            if (distance < minDistance){
                                minDistance = distance;
                                pos = intersection;
                                bIntersectsWord = true;
                                
                                
                                ofPoint diff = lines[i][j+1] - lines[i][j];
                                //ofPoint perp;
                                perp.set(diff.y, -diff.x);
                                
                                angleIntersection = atan2(perp.y, perp.x);
                            }
                        }
                    }
                }
            }
            
            if (bIntersectsWord == false){
                
                ofMesh temp;
                temp.setMode(OF_PRIMITIVE_LINES);
                temp.addColor(ofColor(255,255,255,10));
                temp.addVertex(a);
                temp.addColor(ofColor(255,255,255,10));
                temp.addVertex(b);
                temp.draw();
                
                //ofLine(a,b);
                bNoMoreIntersects = true;
            } else {
                
                
                
                ofMesh temp;
                temp.setMode(OF_PRIMITIVE_LINES);
                temp.addColor(ofColor(255,255,255,10));
                temp.addVertex(a);
                temp.addColor(ofColor(255,255,255,10));
                temp.addVertex(pos);
                temp.draw();
                
                
                //ofLine(a, pos);
                
                ofPoint diff = pos - a;
                float angleMe = atan2(diff.y, diff.x);
                
                a = pos;
                
                float angleDiff = 2*angleIntersection - angleMe;
                
                //R = 2W - P
                
                diff.normalize();
                perp.normalize();
                
                ofPoint tempPt = reflect(diff, perp);
                
                float angle =  atan2(tempPt.y, tempPt.x);
                //angle += ofRandom(-0.002, 0.002);
                b = pos + ofPoint(1000 * cos(angle), 1000 * sin(angle));
                
                //cout << count << " " << a << " " << b << endl;
            }
            
            count++;
           
            
        }
        
//        
//        if (bIntersectsMe){
//            ofSetColor(0,0,0,10);
//            ofLine(a,b);
//        } else {
//            ofSetColor(255,255,255,10);
//            ofLine(a,b);
//        }
    }
    }
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
