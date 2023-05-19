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
		//color = (alphaColor | blueColor | greenColor | redColor);

		return color;
	}

private:

	int canvasWidth_;
	int canvasHeight_;
	int textureHandle_;

	//std::vector<MYRGBA> map_;
	/*std::vector<std::vector<int>> map_;*/
	std::vector<uint32_t> canvasData_;
	/*std::vector<std::vector<uint32_t>> canvasData_;*/

	Color* colorData_ = nullptr;

	InVector2 pos_{};

	uint32_t color_;
	int canvasDotSize_;

	char keys_[256]{};
	char preKeys_[256]{};
	InVector2 mausePos_{};

	BaseMode* mode_;
};