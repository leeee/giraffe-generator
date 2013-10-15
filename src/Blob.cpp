#include "Blob.h"
#include "ofMain.h"

//------------------------------------------------------------
Blob::Blob(){
	setInitialCondition(0,0,0,0);
	damping = 0.12f;
}

//------------------------------------------------------------
void Blob::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void Blob::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void Blob::addRepulsionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void Blob::addAttractionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void Blob::addRepulsionForce(Blob &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Blob p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
					frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
					p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void Blob::addAttractionForce(Blob & p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Blob p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
		p.frc.x = p.frc.x + diff.x * scale * pct;
        p.frc.y = p.frc.y + diff.y * scale * pct;
    }
	
}


//------------------------------------------------------------
void Blob::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void Blob::setInitialCondition(float px, float py, float vx, float vy){
  originalPos.set(px,py);
  pos.set(px,py);
	vel.set(vx,vy);
  radius = ofRandom(200);
  float noiseCursor = ofRandom(1);
  float noiseStep = ofRandom(1);
  nCurveVertices = 10;
  
  for (int i = 0; i < nCurveVertices; i++) {
    float distance = ofNoise(noiseCursor) * radius;
    float angle   = TWO_PI/10 * i;
    vertices[i] = ofVec2f(distance * cos(angle), distance * sin(angle));
    noiseCursor += noiseStep;
  }

}

//------------------------------------------------------------
void Blob::update(){	
	vel = vel + frc;
	pos = pos + vel;
  bounceOffWalls();
}

//------------------------------------------------------------
void Blob::draw(){
  ofPushMatrix();
  ofTranslate(pos.x, pos.y);
  //    if ( b==0) {
  //    cout << blob.center.pos.x << " " << blob.center.pos.y << endl;
  //    }
  ofBeginShape();
  
  for (int i = 0; i < nCurveVertices; i++){
    
    
    // sorry about all the if/states here, but to do catmull rom curves
    // we need to duplicate the start and end points so the curve acutally
    // goes through them.
    
    // for i == 0, we just call the vertex twice
    // for i == nCurveVertices-1 (last point) we call vertex 0 twice
    // otherwise just normal ofCurveVertex call
    
    if (i == 0){
      ofCurveVertex(vertices[0].x, vertices[0].y); // we need to duplicate 0 for the curve to start at point 0
      ofCurveVertex(vertices[0].x, vertices[0].y); // we need to duplicate 0 for the curve to start at point 0
    } else if (i == nCurveVertices-1){
      ofCurveVertex(vertices[i].x, vertices[i].y);
      ofCurveVertex(vertices[0].x, vertices[0].y);	// to draw a curve from pt 6 to pt 0
      ofCurveVertex(vertices[0].x, vertices[0].y);	// we duplicate the first point twice
    } else {
      ofCurveVertex(vertices[i].x, vertices[i].y);
    }
  }
  
  ofEndShape();
  ofPopMatrix();
}


//------------------------------------------------------------
void Blob::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x > maxx){
		pos.x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (pos.y > maxy){
		pos.y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}
