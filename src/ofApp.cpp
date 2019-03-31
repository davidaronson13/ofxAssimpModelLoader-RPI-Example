#include "ofApp.h"

//--------------------------------------------------------------


void ofApp::setup(){
	
	keyPressed('1');

	glEnable(GL_DEPTH_TEST);

	light.enable();

	animationTime = 0.0;

	contador = 0;

}

//--------------------------------------------------------------
void ofApp::update(){
	
if ( model.getAnimationCount() > 0) {
		animationTime += ofGetLastFrameTime();
		if(animationTime >= model.getDuration(0)){
			animationTime = 0.0;
			contador = 0;
		}
		model.setTime(animationTime); //change from  model.setNormalizedTime(animationTime);
	}

	model.setPosition(ofGetWidth() * 4 / 6, (float)ofGetHeight() * 0.75, 0);

	ofPoint actualScale = model.getScale();
	ofPoint actualSceneCenter = model.getSceneCenter();

	text1.assign("keys 1-5 load models. Actual model is "
		+ ofToString(actualModelNumber));
	text1.append("\nkeys t for FILL, g for POINTS or b for WIREFRAME display");
	text1.append("\nNumber of meshes contained: "
		+ ofToString(model.getNumMeshes()));
	text1.append("\nkeys e,r rotate in x. X rotation: "
		+ ofToString(actualXRotation));
	text1.append("\nkeys d,f rotate in y. Y rotation: "
		+ ofToString(actualYRotation));
	text1.append("\nkeys c,v rotate in z. Z rotation: "
		+ ofToString(actualZRotation));
	text1.append("\nactual scale: x (" + ofToString(actualScale.x) + "), y ("
		+ ofToString(actualScale.y) + "), z ("
		+ ofToString(actualScale.z) + ")");
	text1.append("\nkeys q,w scale in x.\nkeys a,s scale in y.\nkeys z,x scale in z.");
	text1.append("\nscene center: x ("
		+ ofToString(actualSceneCenter.x) + "), y ("
		+ ofToString(actualSceneCenter.y) + "), z ("
		+ ofToString(actualSceneCenter.z) + ")");

	for (int i = 0; i < model.getAnimationCount(); i++) {
		text1.append("\n duration for animation " + ofToString(i+1) + ": "
			+ ofToString(model.getDuration(i)));
	}

	text1.append("\n ofGetLastFrameTime: " + ofToString(ofGetLastFrameTime()));
	text1.append("\n__Counter: " + ofToString(++contador));
	text1.append("\nanimation count: " + ofToString(model.getAnimationCount()));

	// This is just to count text1 lines. This is needed in draw()
	int tmp = 0;
	numberOfLinesInText = 0;
	while ((tmp = text1.find('\n', tmp)) < text1.length()){
		numberOfLinesInText++;
		tmp++;
	}

}
//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0, 0, 0, 0);
	ofSetColor(255, 255, 255, 255);

	switch(actualRenderMode){
		case RENDER_MODE_FILL:
			model.draw(OF_MESH_FILL); //change from  model.drawFaces(); for pi
			break;
		case RENDER_MODE_POINTS:
			model.draw(OF_MESH_POINTS); // change from as model.drawVertices(); for pi
			break;
		case RENDER_MODE_WIREFRAME:
			model.draw(OF_MESH_WIREFRAME); // change from as model.drawWireframe(); for pi
			break;
	}

	ofDrawBitmapString(text1, 10, 15);

	for(int i = 0; i < model.getNumMeshes(); i++){
		model.getTextureForMesh(i).draw(10 + (160 * (i % 2))
			, 10 + 15 * numberOfLinesInText  + 160 * (i / 2), 150, 150);
	}

}
void ofApp::initializeModelVariables(int aModel){
	
	actualModelNumber = aModel;actualXRotation = 0;
	actualYRotation = 0;
	actualZRotation = 0;

	tex = model.getTextureForMesh(0);

}
	

void inline ofApp::updateRotation(void){

	model.setRotation(0, actualXRotation, 1, 0, 0);
	model.setRotation(1, actualYRotation, 0, 1, 0);
	model.setRotation(2, actualZRotation, 0, 0, 1);

}
//------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key){
		case '1':
			model.loadModel("astroBoy_walk.dae");
			initializeModelVariables(key);
			break;
		case '2':
			model.loadModel("TurbochiFromXSI.dae");
			initializeModelVariables(key);
			break;
		case '3':
			model.loadModel("dwarf.x");
			initializeModelVariables(key);
			break;
		case '4':
			model.loadModel("monster-animated-character-X.X");
			initializeModelVariables(key);
			break;
		case '5':
			model.loadModel("squirrel/NewSquirrel.3ds");
			initializeModelVariables(key);
			break;
		case 'e':
			actualXRotation -= ROTATION_STEP;
			updateRotation();
			break;
		case 'r':
			actualXRotation += ROTATION_STEP;
			updateRotation();
			break;
		case 'd':
			actualYRotation -= ROTATION_STEP;
			updateRotation();
			break;
		case 'f':
			actualYRotation += ROTATION_STEP;
			updateRotation();
			break;
		case 'c':
			actualZRotation -= ROTATION_STEP;
			updateRotation();
			break;
		case 'v':
			actualZRotation += ROTATION_STEP;
			updateRotation();
			break;
		case 'q':
			model.setScale(model.getScale().x - SCALE_STEP, model.getScale().y
				, model.getScale().z);
			break;
		case 'w':
			model.setScale(model.getScale().x + SCALE_STEP, model.getScale().y
				, model.getScale().z);
			break;
		case 'a':
			model.setScale(model.getScale().x, model.getScale().y - SCALE_STEP
				, model.getScale().z);
			break;
		case 's':
			model.setScale(model.getScale().x, model.getScale().y + SCALE_STEP
				, model.getScale().z);
			break;
		case 'z':
			model.setScale(model.getScale().x, model.getScale().y
				, model.getScale().z - SCALE_STEP);
			break;
		case 'x':
			model.setScale(model.getScale().x, model.getScale().y
				, model.getScale().z + SCALE_STEP);
			break;
		case 't':
			actualRenderMode = RENDER_MODE_FILL;
			break;
		case 'g':
			actualRenderMode = RENDER_MODE_POINTS;
			break;
		case 'b':
			actualRenderMode = RENDER_MODE_WIREFRAME;
			break;
		case ' ':
			break;
		default:
			return;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
