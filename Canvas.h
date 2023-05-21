#pragma once

#include <vector>
#include "RGBA.h"
#include "MyMath.h"
#include "PenMode.h"
#include "Color.h"


class Canvas {
public:
	enum Mode {
		NONE,
		WRITE,
	};


	~Canvas() { delete mode_; delete colorData_; }

	void Initialize(InVector2 pos, const int kWidth, const int kHeight, int canvasDotSize);

	void Update();

	void Draw();

	void CanvasDraw(InVector2 pos, const int canWidth, const int canHeight, const int dotSize);

	void SetMausePos(InVector2 mausePos);

	void SetKeys(char keys[256], char preKeys[256]) {
		for (int i = 0; i < 256; i++) {
			keys_[i] = keys[i];
			preKeys_[i] = preKeys[i];

		}
	}

	void SetDotSize(int dotSize) {
		canvasDotSize_ = dotSize;
	}

	void SetPos(InVector2 pos) {
		pos_ = pos;
	}

	void BModeIni();

	std::vector<uint32_t> *GetCanvasData() {
		return &canvasData_;
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

		return color;
	}

	bool M2Swich(InVector2 pos, InVector2 size, InVector2 mausePos);

	bool M2List(InVector2 pos, InVector2 size, InVector2 mausePos);

private:

	int canvasWidth_;
	int canvasHeight_;
	int textureHandle_;

	InVector2 SwichSize{60, 60};
	InVector2 SwichListPos{40, 170};
	InVector2 swichListSize{ 100 , 260 };
	InVector2 swichPos[3];
	uint32_t swichColor[3]{ 0x000000FF };
	bool isSwich[3];
	
	bool MoveCanvas = true;
	bool isPeint = false;

	
	std::vector<uint32_t> canvasData_;
	std::vector<uint32_t> tmpCanvasData_;


	Color* colorData_ = nullptr;
	InVector2 nowPos{};
	InVector2 pos_{};

	InVector2 nP2P{};

	uint32_t color_;
	int canvasDotSize_;

	char keys_[256]{};
	char preKeys_[256]{};
	InVector2 mausePos_{};
	InVector2 SystemMausePos_{};

	BaseMode* mode_;

	int mauseWheel = canvasDotSize_ * 120;

};