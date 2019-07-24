#pragma once

#include "ofMain.h"
#include "LogitechSteeringWheelLib.h"


class SteeringWheel {
public:
	void setup(uint8_t controllerNo, bool isBackground = false) {
		ctrlNo = controllerNo;

		if (isBackground) {
			isInitOK = LogiSteeringInitialize(TRUE);
		}
		else {
			HWND hWnd = WindowFromDC(wglGetCurrentDC());
			isInitOK = LogiSteeringInitializeWithWindow(TRUE, hWnd);
		}
		if (!isInitOK) {
			ofLogError("ofxLogitechGamingSteeringWheel") << "Steering initialize error";
			return;
		}

		ofAddListener(ofGetWindowPtr()->events().update, this, &SteeringWheel::update, OF_EVENT_ORDER_APP);
	}

	void update(ofEventArgs & args) {
		if (!isInitOK) {
			ofLogWarning("ofxLogitechGamingSteeringWheel") << "Handle is not initialized.";
		}

		bool isOK = LogiUpdate();
		if (isOK) {

			DIJOYSTATE2* pState = LogiGetState(0);

			handle = ofMap(pState->lX, SHRT_MIN, SHRT_MAX, -1, 1);
			accel = ofMap(pState->lY, SHRT_MAX, SHRT_MIN, 0, 1);
			brake = ofMap(pState->lRz, SHRT_MAX, SHRT_MIN, 0, 1);
			clutch = ofMap(pState->rglSlider[0], SHRT_MAX, SHRT_MIN, 0, 1);

			for (auto& buttonPair : buttonTable) {
				auto buttonNo = buttonPair.first;
				auto buttonParam = buttonPair.second;
				*buttonParam = pState->rgbButtons[buttonNo] != 0;
			}

			buttonHutDir = pState->rgdwPOV[0] / 100.0;
			buttonHut = (buttonHutDir <= 315);
			buttonHutDir = buttonHut ? buttonHutDir : 0;

			buttonUp = buttonHut && ((buttonHutDir >= 315) || (buttonHutDir <= 45));
			buttonRight = buttonHut && (buttonHutDir >= 45) && (buttonHutDir <= 135);
			buttonDown = buttonHut && (buttonHutDir >= 135) && (buttonHutDir <= 225);
			buttonLeft = buttonHut && (buttonHutDir >= 225) && (buttonHutDir <= 315);
		}
	}

	void playSpringForce(float offset, float saturation, float coefficient) {
		LogiPlaySpringForce(ctrlNo,
			ofMap(offset, -1, 1, -100, 100, true),
			ofMap(saturation, 0, 1, 0, 100, true),
			ofMap(coefficient, -1, 1, -100, 100, true));
	}

	void stopSpringForce() {
		LogiStopSpringForce(ctrlNo);
	}

	void playConstantForce(float magnitude) {
		LogiPlayConstantForce(ctrlNo,
			ofMap(magnitude, -1, 1, -100, 100, true));
	}

	void stopConstantForce() {
		LogiStopConstantForce(ctrlNo);
	}

	void playDamperForce(float coefficient) {
		LogiPlayDamperForce(ctrlNo,
			ofMap(coefficient, -1, 1, -100, 100, true));
	}

	void stopDamperForce() {
		LogiStopDamperForce(ctrlNo);
	}

	void playSideCollisionForce(float magnitude) {
		LogiPlaySideCollisionForce(ctrlNo,
			ofMap(magnitude, -1, 1, -100, 100, true));
	}

	void playFrontalCollisionForce(float magnitude) {
		LogiPlayFrontalCollisionForce(ctrlNo,
			ofMap(magnitude, 0, 1, 0, 100, true));
	}

	void playDirtRoadEffect(float magnitude) {
		LogiPlayDirtRoadEffect(ctrlNo,
			ofMap(magnitude, 0, 1, 0, 100, true));
	}

	void stopDirtRoadEffect() {
		LogiStopDirtRoadEffect(ctrlNo);
	}

	void playBumpyRoadEffect(float magnitude) {
		LogiPlayBumpyRoadEffect(ctrlNo,
			ofMap(magnitude, 0, 1, 0, 100, true));
	}

	void stopBumpyRoadEffect() {
		LogiStopBumpyRoadEffect(ctrlNo);
	}

	void playSlipperyRoadEffect(float magnitude) {
		LogiPlaySlipperyRoadEffect(ctrlNo,
			ofMap(magnitude, 0, 1, 0, 100, true));
	}

	void stopSlipperyRoadEffect() {
		LogiStopSlipperyRoadEffect(ctrlNo);
	}

	void playSurfaceEffect(uint8_t type, float magnitude, float periodMs) {
		LogiPlaySurfaceEffect(ctrlNo,
			type,
			ofMap(magnitude, 0, 1, 0, 100, true),
			ofClamp(periodMs, 0, 150));
	}

	void stopSurfaceEffect() {
		LogiStopSurfaceEffect(ctrlNo);
	}

	void playCarAirborne() {
		LogiPlayCarAirborne(ctrlNo);
	}

	void stopCarAirborne() {
		LogiStopCarAirborne(ctrlNo);
	}

	void playSoftstopForce(float usableRange) {
		LogiPlaySoftstopForce(ctrlNo,
			ofMap(usableRange, -1, 1, -100, 100, true));
	}

	void stopSoftstopForce() {
		LogiStopSoftstopForce(ctrlNo);
	}


	float handle;
	float accel;
	float brake;
	float clutch;
	bool buttonUp;
	bool buttonDown;
	bool buttonLeft;
	bool buttonRight;
	bool buttonHut;
	float buttonHutDir;
	bool buttonA;
	bool buttonB;
	bool buttonX;
	bool buttonY;
	bool buttonL1;
	bool buttonL2;
	bool buttonL3;
	bool buttonR1;
	bool buttonR2;
	bool buttonR3;
	bool buttonPlus;
	bool buttonMinus;
	bool buttonShare;
	bool buttonOption;
	bool buttonPS;
	bool buttonEnter;
	bool buttonSelectL;
	bool buttonSelectR;

private:
	uint8_t ctrlNo;
	bool isInitOK;

	unordered_map<char, bool*> buttonTable = {
		{ 2,	&buttonA },
		{ 0,	&buttonB },
		{ 3,	&buttonX },
		{ 1,	&buttonY },
		{ 5,	&buttonL1 },
		{ 7,	&buttonL2 },
		{ 11,	&buttonL3 },
		{ 4,	&buttonR1 },
		{ 6,	&buttonR2 },
		{ 10,	&buttonR3 },
		{ 19,	&buttonPlus },
		{ 20,	&buttonMinus },
		{ 8,	&buttonShare },
		{ 9,	&buttonOption },
		{ 24,	&buttonPS },
		{ 23,	&buttonEnter },
		{ 22,	&buttonSelectL },
		{ 21,	&buttonSelectR },
	};
};