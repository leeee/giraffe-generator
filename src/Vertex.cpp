#include "Vertex.h"
#include "ofMain.h"

//------------------------------------------------------------
Vertex::Vertex(){
	setInitialCondition(0,0,0,0,0,0);
	damping = 0.12f;
}

//------------------------------------------------------------
void Vertex::resetForce(){
  // we reset the forces every frame
  frc.set(0,0);
}

//------------------------------------------------------------
void Vertex::addForce(float x, float y){
  // add in a force in X and Y for this frame.
  frc.x = frc.x + x;
  frc.y = frc.y + y;
}

//------------------------------------------------------------
void Vertex::addRepulsionForce(float x, float y, float radius, float scale){
  
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
void Vertex::addAttractionForce(float x, float y, float radius, float scale){
  
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
void Vertex::addRepulsionForce(Vertex &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Vertex p is:
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
void Vertex::addAttractionForce(Vertex & p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Vertex p is:
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
void Vertex::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity
	// damping is a force operating in the oposite direction of the
	// velocity vector
	
  frc.x = frc.x - vel.x * damping;
  frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void Vertex::setInitialCondition(float bx, float by, float ox, float oy, float vx, float vy){
  originalOffset.set(ox,oy);
  pos.set(bx + ox, by + oy);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void Vertex::update(){
	vel = vel + frc;
	pos = pos + vel;
  bounceOffWalls();
}

//------------------------------------------------------------
void Vertex::draw(){
  // drawn by parent
}


//------------------------------------------------------------
void Vertex::bounceOffWalls(){
	
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
