#pragma once

#include <vector>
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

	void Initialize(const int kWidth, const int kHeight, int canvasDotSize);

	void Update();

	void Draw();

	void CanvasDraw(const int canWidth, const int canHeight, const int dotSize);

	void SetMausePos(InVector2 mausePos);

	void SetKeys(char keys[256], char preKeys[256]) {
		for (int i = 0; i < 256; i++) {
			keys_[i] = keys[i];
			preKeys_[i] = preKeys[i];

		}
	}

	void BModeIni();

	std::vector<std::vector<uint32_t>> GetCanvasData() {
		return canvasData_;
	}

private:

	int canvasWidth_;
	int canvasHeight_;
	

	std::vector<int> mapX_;
	std::vector<std::vector<int>> map_;
	std::vector<uint32_t> canvasDataX_;
	std::vector<std::vector<uint32_t>> canvasData_;

	Color* colorData_ = nullptr;


	uint32_t color_;
	int canvasDotSize_;

	char keys_[256]{};
	char preKeys_[256]{};
	InVector2 mausePos_{};

	BaseMode* mode_;
};