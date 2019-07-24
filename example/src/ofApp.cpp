#include "ofApp.h"

HWND m_hWnd;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);

	wheel.setup(0);

	gui1.setup();
	gui1.add(sliderGroup);
	gui1.setPosition(0, 0);

	gui2.setup();
	gui2.add(buttonsGroup);
	gui2.setPosition(gui1.getPosition().x + gui1.getWidth(), 0);

	gui3.setup();
	gui3.add(forceGroup);
	gui3.setPosition(gui2.getPosition().x + gui2.getWidth(), 0);
	for (auto& name : gui3.getControlNames()) {
		gui3.getGroup(name).minimizeAll();
	}

	springForce.addListener(this, &ofApp::onSpringForce);
	springForceOffset.addListener(this, &ofApp::onSpringForceValChanged);
	springForceSaturation.addListener(this, &ofApp::onSpringForceValChanged);
	springForceCoefficient.addListener(this, &ofApp::onSpringForceValChanged);

	constantForce.addListener(this, &ofApp::onConstantForce);
	constantForceMagnitude.addListener(this, &ofApp::onConstantForceValChanged);

	damperForce.addListener(this, &ofApp::onDamperForce);
	damperForceCoefficient.addListener(this, &ofApp::onDamperForceValChanged);

	sideCollisionForce.addListener(this, &ofApp::onSideCollisionForce);

	frontalCollisionForce.addListener(this, &ofApp::onFrontalCollisionForce);

	dirtRoadEffect.addListener(this, &ofApp::onDirtRoadEffect);
	dirtRoadEffectMagnitude.addListener(this, &ofApp::onDirtRoadEffectValChanged);

	bumpyRoadEffect.addListener(this, &ofApp::onBumpyRoadEffect);
	bumpyRoadEffectMagnitude.addListener(this, &ofApp::onBumpyRoadEffectValChanged);

	slipperyRoadEffect.addListener(this, &ofApp::onSlipperyRoadEffect);
	slipperyRoadEffectMagnitude.addListener(this, &ofApp::onSlipperyRoadEffectValChanged);

	surfaceEffect.addListener(this, &ofApp::onSurfaceEffect);
	surfaceEffectType.addListener(this, &ofApp::onSurfaceEffectTypeChanged);
	surfaceEffectMagnitude.addListener(this, &ofApp::onSurfaceEffectValChanged);
	surfaceEffectPeriodMs.addListener(this, &ofApp::onSurfaceEffectValChanged);

	carAirborne.addListener(this, &ofApp::onCarAirborne);
	
	softstopForce.addListener(this, &ofApp::onSoftstopForce);
	softstopForceUsableRange.addListener(this, &ofApp::onSoftstopForceValChanged);
}

//--------------------------------------------------------------
void ofApp::update(){

	handle = wheel.handle;
	accel = wheel.accel;
	brake = wheel.brake;
	clutch = wheel.clutch;

	buttonUp = wheel.buttonUp;
	buttonDown = wheel.buttonDown;
	buttonLeft = wheel.buttonLeft;
	buttonRight = wheel.buttonRight;
	buttonHut = wheel.buttonHut;
	buttonHutDir = wheel.buttonHutDir;

	buttonA = wheel.buttonA;
	buttonB = wheel.buttonB;
	buttonX = wheel.buttonX;
	buttonY = wheel.buttonY;
	buttonL1 = wheel.buttonL1;
	buttonL2 = wheel.buttonL2;
	buttonL3 = wheel.buttonL3;
	buttonR1 = wheel.buttonR1;
	buttonR2 = wheel.buttonR2;
	buttonR3 = wheel.buttonR3;
	buttonPlus = wheel.buttonPlus;
	buttonMinus = wheel.buttonMinus;
	buttonShare = wheel.buttonShare;
	buttonOption = wheel.buttonOption;
	buttonPS = wheel.buttonPS;
	buttonEnter = wheel.buttonEnter;
	buttonSelectL = wheel.buttonSelectL;
	buttonSelectR = wheel.buttonSelectR;
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui1.draw();
	gui2.draw();
	gui3.draw();
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
