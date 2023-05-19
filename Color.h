#pragma once

#include <vector>
#include "RGBA.h"
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

	void SetColor(MYRGBA color) {
		color_ = color;
	}

	MYRGBA GetColor() {
		return color_;
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

	void SetLeftMause(bool leftMause) {
		leftMause_ = leftMause;
	}

	void SetLeftMauseTori(bool leftMause) {
		leftMauseTri_ = leftMause;
	}

	uint32_t ColorR(int redColor) {
		redColor = redColor << 24;
		return redColor;
	}

	uint32_t  ColorG(int greenColor) {
		greenColor = greenColor << 16;
		return greenColor;

	}

	uint32_t  ColorB(int blueColor) {
		blueColor = blueColor << 8;
		return blueColor;

	}

	uint32_t ColorD(MYRGBA colorD) {
		uint32_t color;
		uint32_t redColor = ColorR(colorD.r);
		uint32_t greenColor = ColorG(colorD.g);
		uint32_t blueColor = ColorB(colorD.b);
		uint32_t alphaColor = uint32_t(colorD.a);
		color = (redColor | greenColor | blueColor | alphaColor);
		//color = (alphaColor | blueColor | greenColor | redColor);

		return color;
	}

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

	InVector2 colorBox{};

	const int handleHalfWidth = 5;
	const int handleHalfHeight = 10;

	const int gaugeHalfWidth = 128;
	const int gaugeHalfHeight = 5;
	InVector2 colorList{};

	MYRGBA color_;

	int redD;
	int greenD;
	int blueD;
	int alphaD;

	bool isRedClick = false;
	bool isGreenClick = false;
	bool isBlueClick = false;
	bool isAlphaClick = false;

	bool leftMause_ = false;
	bool leftMauseTri_ = false;
};
