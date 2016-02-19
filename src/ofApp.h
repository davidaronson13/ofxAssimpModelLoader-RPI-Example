#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	private:
		void initializeModelVariables(int aModel);
		void inline updateRotation(void);

		char actualModelNumber;

		string text1;
		int numberOfLinesInText;

		int contador;
		ofxAssimpModelLoader model;


#define RENDER_MODE_FILL 0
#define RENDER_MODE_POINTS 1
#define RENDER_MODE_WIREFRAME 2
		char actualRenderMode;

#define ROTATION_STEP 5
		int actualXRotation;
		int actualYRotation;
		int actualZRotation;

#define SCALE_STEP 0.05

		double animationTime;

		ofTexture tex;

		ofLight	light;

};
