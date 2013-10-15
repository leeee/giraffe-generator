#ifndef BLOB_H
#define BLOB_H

#include "ofMain.h"

class Blob
{
    public:
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
			
        Blob();
		virtual ~Blob(){};

        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		void addRepulsionForce(Blob &p, float radius, float scale);
		void addAttractionForce(Blob &p, float radius, float scale);
		
		void addDampingForce();
        
		void setInitialCondition(float px, float py, float vx, float vy);
        void update();
        void draw();
	
		void bounceOffWalls();
	
	
		float damping;
  
    ofPoint vertices[10];
    float radius;
    int nCurveVertices;
    ofPoint originalPos;

    protected:
    private:
};

#endif // BLOB_H
