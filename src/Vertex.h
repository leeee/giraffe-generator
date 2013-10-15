//
//  vertex.h
//  holes
//
//  Created by Le Wei on 10/15/13.
//
//

#ifndef __holes__vertex__
#define __holes__vertex__

#include "ofMain.h"
#include "Blob.h"

class Vertex
{
  public:
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
    
    Vertex();
    virtual ~Vertex(){};
    
    void resetForce();
    void addForce(float x, float y);
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addAttractionForce(float x, float y, float radius, float scale);
    void addRepulsionForce(Vertex &p, float radius, float scale);
    void addAttractionForce(Vertex &p, float radius, float scale);
    
    void addDampingForce();
    
    void setInitialCondition(float bx, float by, float ox, float oy, float vx, float vy);
    void update();
    void draw();
    
    void bounceOffWalls();
    
    
    float damping;
    
    float radius;
    ofPoint originalOffset; // offset from parent Blob center
    
  protected:
  private:

};

#endif /* defined(__holes__vertex__) */
