#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "ofxLogitechGamingSteeringWheel.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void exit() {
			LogiSteeringShutdown();
		}

		SteeringWheel wheel;


		ofxPanel gui1;
		ofxPanel gui2;
		ofxPanel gui3;

		ofParameter<float> handle{ "HANDLE", 0, -1, 1 };
		ofParameter<float> accel{ "ACCEL", 0, 0, 1 };
		ofParameter<float> brake{ "BRAKE", 0, 0, 1 };
		ofParameter<float> clutch{ "CLUTCH", 0, 0, 1 };
		ofParameterGroup sliderGroup{
			"HANDLE/PEDAL",
			handle,
			accel,
			brake,
			clutch
		};

		ofParameter<bool>  buttonUp{ "UP", false };
		ofParameter<bool>  buttonDown{ "DOWN", false };
		ofParameter<bool>  buttonLeft{ "LEFT", false };
		ofParameter<bool>  buttonRight{ "RIGHT", false };
		ofParameter<bool>  buttonHut{ "HUT", false };
		ofParameter<float> buttonHutDir{ "HUT DIR", 0, 0, 360 };
		ofParameter<bool>  buttonA{ "BUTTON A", false };
		ofParameter<bool>  buttonB{ "BUTTON B", false };
		ofParameter<bool>  buttonX{ "BUTTON X", false };
		ofParameter<bool>  buttonY{ "BUTTON Y", false };
		ofParameter<bool>  buttonL1{ "BUTTON L1", false };
		ofParameter<bool>  buttonL2{ "BUTTON L2", false };
		ofParameter<bool>  buttonL3{ "BUTTON L3", false };
		ofParameter<bool>  buttonR1{ "BUTTON R1", false };
		ofParameter<bool>  buttonR2{ "BUTTON R2", false };
		ofParameter<bool>  buttonR3{ "BUTTON R3", false };
		ofParameter<bool>  buttonPlus{ "BUTTON +", false };
		ofParameter<bool>  buttonMinus{ "BUTTON -", false };
		ofParameter<bool>  buttonShare{ "BUTTON SHARE", false };
		ofParameter<bool>  buttonOption{ "BUTTON OPTION", false };
		ofParameter<bool>  buttonPS{ "BUTTON PS", false };
		ofParameter<bool>  buttonEnter{ "BUTTON ENTER", false };
		ofParameter<bool>  buttonSelectL{ "BUTTON SELECT L", false };
		ofParameter<bool>  buttonSelectR{ "BUTTON SELECT R", false };
		ofParameterGroup buttonsGroup{
			"BUTTONS",
			buttonUp,
			buttonDown,
			buttonLeft,
			buttonRight,
			buttonHut,
			buttonHutDir,
			buttonA,
			buttonB,
			buttonX,
			buttonY,
			buttonL1,
			buttonL2,
			buttonL3,
			buttonR1,
			buttonR2,
			buttonR3,
			buttonPlus,
			buttonMinus,
			buttonShare,
			buttonOption,
			buttonPS,
			buttonEnter,
			buttonSelectL,
			buttonSelectR,
		};

		ofParameter<bool>  springForce{ "SPRING FORCE ON", false };
		ofParameter<float> springForceOffset{ "OFFSET", 0, -1, 1 };
		ofParameter<float> springForceSaturation{ "SATURATION", 0, 0, 1 };
		ofParameter<float> springForceCoefficient{ "COEFFICIENT", 0, -1, 1 };
		ofParameterGroup springForceGroup{
			"SPRING FORCE",
			springForce,
			springForceOffset,
			springForceSaturation,
			springForceCoefficient
		};
		void onSpringForce(bool& isON) { changeSpringForce(); }
		void onSpringForceValChanged(float &val) { changeSpringForce(); }
		void changeSpringForce() {
			if (springForce) {
				wheel.playSpringForce(springForceOffset, springForceSaturation, springForceCoefficient);
			}
			else {
				wheel.stopSpringForce();
			}
		}

		ofParameter<bool>  constantForce{ "CONSTANT FORCE ON", false };
		ofParameter<float> constantForceMagnitude{ "MAGNITUDE", 0, -1, 1 };
		ofParameterGroup constantForceGroup {
			"CONSTANT FORCE",
			constantForce,
			constantForceMagnitude
		};
		void onConstantForce(bool& isON) { changeConstantForce(); }
		void onConstantForceValChanged(float &val) { changeConstantForce(); }
		void changeConstantForce() {
			if (constantForce) {
				wheel.playConstantForce(constantForceMagnitude);
			}
			else {
				wheel.stopConstantForce();
			}
		}

		ofParameter<bool>  damperForce{ "DAMPER FORCE ON", false };
		ofParameter<float> damperForceCoefficient{ "COEFFICIENT", 0, -1, 1 };
		ofParameterGroup damperForceGroup{
			"DAMPER FORCE",
			damperForce,
			damperForceCoefficient
		};
		void onDamperForce(bool& isON) { changeDamperForce(); }
		void onDamperForceValChanged(float& val) { changeDamperForce(); }
		void changeDamperForce() {
			if (damperForce) {
				wheel.playDamperForce(damperForceCoefficient);
			}
			else {
				wheel.stopDamperForce();
			}
		}

		ofParameter<void>  sideCollisionForce{ "SIDE COLLISION" };
		ofParameter<float> sideCollisionForceMagnitude{ "MAGNITUDE", 0, -1, 1 };
		ofParameterGroup sideCollisionForceGroup{
			"SIDE COLLISION FORCE",
			sideCollisionForce,
			sideCollisionForceMagnitude
		};
		void onSideCollisionForce() {
			wheel.playSideCollisionForce(sideCollisionForceMagnitude);
		}

		ofParameter<void>  frontalCollisionForce{ "FRONTAL COLLISION" };
		ofParameter<float> frontalCollisionForceMagnitude{ "MAGNITUDE", 0, 0, 1 };
		ofParameterGroup frontalCollisionForceGroup{
			"FRONTAL COLLISION FORCE",
			frontalCollisionForce,
			frontalCollisionForceMagnitude,
		};
		void onFrontalCollisionForce() {
			wheel.playFrontalCollisionForce(frontalCollisionForceMagnitude);
		}

		ofParameter<bool>  dirtRoadEffect{ "DIRT ROAD EFFECT ON", false };
		ofParameter<float> dirtRoadEffectMagnitude{ "MAGNITUDE", 0, 0, 1 };
		ofParameterGroup dirtRoadEffectGruop{
			"DIRT ROAD EFFECT",
			dirtRoadEffect,
			dirtRoadEffectMagnitude
		};
		void onDirtRoadEffect(bool &isON) { changeDirtRoadEffect(); }
		void onDirtRoadEffectValChanged(float& val) { changeDirtRoadEffect(); }
		void changeDirtRoadEffect() {
			if (dirtRoadEffect) {
				wheel.playDirtRoadEffect(dirtRoadEffectMagnitude);
			}
			else {
				wheel.stopDirtRoadEffect();
			}
		}

		ofParameter<bool>  bumpyRoadEffect{ "BUMPY ROAD EFFECT ON", false };
		ofParameter<float> bumpyRoadEffectMagnitude{ "MAGNITUDE", 0, 0, 1 };
		ofParameterGroup bumpyRoadEffectGroup{
			"BUMPY ROAD EFFECT",
			bumpyRoadEffect,
			bumpyRoadEffectMagnitude
		};
		void onBumpyRoadEffect(bool& isON) { changeBumpyRoadEffect(); }
		void onBumpyRoadEffectValChanged(float& val) { changeBumpyRoadEffect(); }
		void changeBumpyRoadEffect() {
			if (bumpyRoadEffect) {
				wheel.playBumpyRoadEffect(bumpyRoadEffectMagnitude);
			}
			else {
				wheel.stopBumpyRoadEffect();
			}
		}

		ofParameter<bool>  slipperyRoadEffect{ "SLIPPERY ROAD EFFECT ON", false };
		ofParameter<float> slipperyRoadEffectMagnitude{ "MAGNITUDE", 0, 0, 1 };
		ofParameterGroup slipperyRoadEffectGroup{
			"SLIPPERY ROAD EFFECT",
			slipperyRoadEffect,
			slipperyRoadEffectMagnitude
		};
		void onSlipperyRoadEffect(bool& isON) { changeSlipperyRoadEffect(); }
		void onSlipperyRoadEffectValChanged(float& val) { changeSlipperyRoadEffect(); }
		void changeSlipperyRoadEffect() {
			if (slipperyRoadEffect) {
				wheel.playSlipperyRoadEffect(slipperyRoadEffectMagnitude);
			}
			else {
				wheel.stopSlipperyRoadEffect();
			}
		}

		ofParameter<bool>  surfaceEffect{ "SURFACE EFFECT ON", false };
		ofParameter<int>   surfaceEffectType{ "TYPE", 0, 0, 2 };
		ofParameter<float> surfaceEffectMagnitude{ "MAGNITUDE", 0, 0, 1 };
		ofParameter<float> surfaceEffectPeriodMs{ "PERIOD MS", 0, 0, 150 };
		ofParameterGroup surfaceEffectGroup{
			"SURFACE EFFECT GROUP",
			surfaceEffect,
			surfaceEffectType,
			surfaceEffectMagnitude,
			surfaceEffectPeriodMs,
		};

		void onSurfaceEffect(bool& isON) { changeSurfaceEffect(); }
		void onSurfaceEffectTypeChanged(int& val) { changeSurfaceEffect(); }
		void onSurfaceEffectValChanged(float& val) { changeSurfaceEffect(); }
		void changeSurfaceEffect() {
			if (surfaceEffect) {
				wheel.playSurfaceEffect(surfaceEffectType, surfaceEffectMagnitude, surfaceEffectPeriodMs);
			}
			else {
				wheel.stopSurfaceEffect();
			}
		}

		ofParameter<bool> carAirborne{ "CAR AIRBORNE ON", false };
		ofParameterGroup carAirborneGroup{
			"CAR AIRBORNE",
			carAirborne
		};
		void onCarAirborne(bool& isON) {
			if (carAirborne) {
				wheel.playCarAirborne();
			}
			else {
				wheel.stopCarAirborne();
			}
		}

		ofParameter<bool>  softstopForce{ "SOFT STOP ON", false };
		ofParameter<float> softstopForceUsableRange{ "USABLE RANGE", 0, -1, 1 };
		ofParameterGroup softstopForceGroup{
			"SOFT STOP FORCE",
			softstopForce,
			softstopForceUsableRange
		};
		void onSoftstopForce(bool& isON) { changeSoftstopForce(); }
		void onSoftstopForceValChanged(float& val) { changeSoftstopForce(); }
		void changeSoftstopForce() {
			if (softstopForce) {
				wheel.playSoftstopForce(softstopForceUsableRange);
			}
			else {
				wheel.stopSoftstopForce();
			}
		}

		ofParameterGroup forceGroup{
			"FORCE/EFFECT",
			springForceGroup,
			constantForceGroup,
			damperForceGroup,
			sideCollisionForceGroup,
			frontalCollisionForceGroup,
			dirtRoadEffectGruop,
			bumpyRoadEffectGroup,
			slipperyRoadEffectGroup,
			surfaceEffectGroup,
			carAirborneGroup,
			softstopForceGroup,
		};
};
