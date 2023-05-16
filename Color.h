#pragma once

#include <vector>
#include "MyMath.h"

class Color {
public:
	void Initialize();

	void Update();

	void Draw();

	void GaugeDraw(InVector2 Gaugepos, InVector2 Handlepos, uint32_t color);
	void SetPos(InVector2 position) {
		colorList = position;
	}

	void SetColor(uint32_t color) {
		color_ = color;
	}

	void ColorR(int& redColor) {
		redColor = redColor << 24;
	}

	void ColorG(int& greenColor) {
		greenColor = greenColor << 16;
	}

	void ColorB(int& blueColor) {
		blueColor = blueColor << 8;
	}

	uint32_t GetColor() {
		return color_;
	}

	uint32_t ColorD(int blueColor, int greenColor, int redColor, int alpha) {
		uint32_t color;
		ColorR(redColor);
		ColorG(greenColor);
		ColorB(blueColor);
		color = (redColor | greenColor | blueColor | alpha);

		return color;
	}

	void SetMausePos(InVector2 mausePos);

	void SetKeys(char keys[256], char preKeys[256]) {
		for (int i = 0; i < 256; i++) {
			keys_[i] = keys[i];
			preKeys_[i] = preKeys[i];

		}
	}

	bool MauseToHandle(InVector2 Handle);

	void CheckHandle(bool& isClick, InVector2& handle, int &colorD);

private:
	char keys_[256]{};
	char preKeys_[256]{};
	InVector2 mausePos_{};

	InVector2 baseHandle_[2]{};

	InVector2 redGauge[2]{};
	InVector2 greenGauge[2]{};
	InVector2 blueGauge[2]{};
	InVector2 alphaGauge[2]{};

	InVector2 redHandle{};
	InVector2 greenHandle{};
	InVector2 blueHandle{};
	InVector2 alphaHandle{};

	const int handleHalfWidth = 5;
	const int handleHalfHeight = 10;

	const int gaugeHalfWidth = 128;
	const int gaugeHalfHeight = 5;
	InVector2 colorList{};

	uint32_t color_;

	int redD;
	int greenD;
	int blueD;
	int alphaD;

	bool isRedClick = false;
	bool isGreenClick = false;
	bool isBlueClick = false;
	bool isAlphaClick = false;
};
