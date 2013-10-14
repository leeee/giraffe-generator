#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  ofBackground(255);
  ofSetFrameRate(60);
  
  nCurveVertices = 10;
  nBlobs = 20;
  Blob blob;
  float noiseCursor = 0.0;

  for (int b = 0; b < nBlobs; b++) {
    blobs.push_back(blob);
    blobs[b].radius = ofRandom(200);
    blobs[b].x = ofRandom(ofGetWidth());
    blobs[b].y = ofRandom(ofGetHeight());

    for (int i = 0; i < nCurveVertices; i++) {
      float distance = ofNoise(noiseCursor) * blobs[b].radius;
      float angle   = TWO_PI/nCurveVertices * i;
      blobs[b].vertices[i] = ofVec2f(distance * cos(angle), distance * sin(angle));
      cout << distance << endl;
      noiseCursor += 0.3;
    }
  }

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetColor(43, 219, 230, 150);
  for (int b = 0; b < nBlobs; b++) {
    Blob blob = blobs[b];
    ofPushMatrix();
      ofTranslate(blob.x, blob.y);
      ofBeginShape();

        for (int i = 0; i < nCurveVertices; i++){
          
          
          // sorry about all the if/states here, but to do catmull rom curves
          // we need to duplicate the start and end points so the curve acutally
          // goes through them.
          
          // for i == 0, we just call the vertex twice
          // for i == nCurveVertices-1 (last point) we call vertex 0 twice
          // otherwise just normal ofCurveVertex call
          
          if (i == 0){
            ofCurveVertex(blob.vertices[0].x, blob.vertices[0].y); // we need to duplicate 0 for the curve to start at point 0
            ofCurveVertex(blob.vertices[0].x, blob.vertices[0].y); // we need to duplicate 0 for the curve to start at point 0
          } else if (i == nCurveVertices-1){
            ofCurveVertex(blob.vertices[i].x, blob.vertices[i].y);
            ofCurveVertex(blob.vertices[0].x, blob.vertices[0].y);	// to draw a curve from pt 6 to pt 0
            ofCurveVertex(blob.vertices[0].x, blob.vertices[0].y);	// we duplicate the first point twice
          } else {
            ofCurveVertex(blob.vertices[i].x, blob.vertices[i].y);
          }
        }

      ofEndShape();
    ofPopMatrix();
  }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
