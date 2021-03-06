#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  ofBackgroundHex(0xFFEB0A);
  ofSetFrameRate(60);
  
  nCurveVertices = 10;
  nBlobs = 30;
  Blob blob;

  for (int b = 0; b < nBlobs; b++) {
    blobs.push_back(blob);
    blob.setInitialCondition(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 0, 0);
  }

}

//--------------------------------------------------------------
void testApp::update(){
	// on every frame
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < nBlobs; i++){
		blobs[i].resetForce();
	}
	
	
	for (int i = 0; i < nBlobs; i++){
		
		blobs[i].addRepulsionForce(mouseX, mouseY, 200, 4);
//    blobs[i].addAttractionForce(blobs[i].originalPos.x, blobs[i].originalPos.y, ofGetHeight() + ofGetWidth(), 0.1);
		
		for (int j = 0; j < i; j++){
			blobs[i].addRepulsionForce(blobs[j], blobs[j].radius + blobs[i].radius, 4);
		}
		//for (int j = 0; j < i; j++){
    //			if (bRepel){
    //				particles[i].addRepulsionForce(particles[j], radius, strength);
    //			} else {
    //				particles[i].addAttractionForce(particles[j], radius, strength);
    //			}
    //		}
	}
	
	for (int i = 0; i < nBlobs; i++){
		blobs[i].addDampingForce();
		blobs[i].update();
//    if ( i==0) {
//      cout << particles[i]->pos.x << " " << particles[i]->pos.y << endl;
//    }

	}
}

//--------------------------------------------------------------
void testApp::draw(){
//  ofSetColor(43, 219, 230, 150);
  ofSetColor(113, 76, 19, 200);
  for (int b = 0; b < nBlobs; b++) {
    Blob blob = blobs[b];
    blob.draw();
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
