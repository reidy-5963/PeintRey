#pragma once
#include <vector>
#include "RGBA.h"
#include "MyMath.h"

class Canvas;

class BaseMode {
public:
	virtual void Initialize() {};
	virtual void Update() {};

	virtual void SetCanvas(Canvas* canvas) {
		canvas_ = canvas;
	}
	virtual void SetCanvasData(std::vector<uint32_t>* canvasData) {
		/*for (int i = 0; i < canvasWidth_; i++) {
			for (int j = 0; j < canvasHeight_; j++) {
				canvasData_ = canvasData;
			}
		}*/
		canvasData_ = canvasData;
	}
	virtual std::vector<uint32_t>* GetCanvasData() {
		return canvasData_;
	}
	virtual void SetMausePos(InVector2 pos) {
		mausePos = pos;
	}
	virtual void SetMauseprePos(InVector2 prepos) {
		preMausePos = prepos;
	}
	void SetCanvasPos(InVector2 pos) {
		canPos = pos;
	}

	virtual void SetIndex(int x, int y) {
		xIndex_ = x;
		yIndex_ = y;
	}
	virtual void SetColor(uint32_t color) {
		color_ = color;
	}
	virtual uint32_t GetColor() {
		return color_;
	}
	virtual void SetKeys(char keys, char preKeys) {
		keys_ = keys;
		preKeys_ = preKeys;
	}

	virtual void SetCanDotSize(int dotSize) {
		canvasDot_ = dotSize;
	}

	virtual void SetCanSize(int width, int height, int dotSize) {
		canvasWidth_ = width;
		canvasHeight_ = height;
		SetCanDotSize(dotSize);
	}

	virtual void SetLeftMause(bool leftMause) {
		leftMause_ = leftMause;
	}

	virtual void SetLeftMauseTori(bool leftMause) {
		leftMauseTri_ = leftMause;
	}

protected:
	Canvas* canvas_ = nullptr;

	std::vector<uint32_t>* canvasData_ = nullptr;
	//std::vector<MYRGBA>* map_ = nullptr;

	int xIndex_{};
	int yIndex_{};

	InVector2 mausePos{};
	InVector2 preMausePos{};
	InVector2 canPos{};

	char keys_{};
	char preKeys_{};

	uint32_t color_{};

	bool leftMause_ = false;
	bool leftMauseTri_ = false;

	int canvasWidth_{};
	int canvasHeight_{};
	int canvasDot_{};

	bool isAllData = false;
};

class Bucket : public BaseMode {
	struct BufferStr {
		int sx;
		int sy;
	};

public:
	

	void Update();
	
	void Solid(int xIndex, int yIndex);

	void ScanLine(int leftX, int rightX, int y, uint32_t col);

	void Paint(int x, int y, uint32_t color);

private:
	static constexpr int MaxBuff = 2000;
	struct BufferStr* sIdx{}, * eIdx{};
	BufferStr buff[MaxBuff]{};


};

class WriteMode : public BaseMode {
public:
	void Update();

};

class Erayser : public BaseMode {
public:
	void Update();

};