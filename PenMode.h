#pragma once
#include <vector>

class Canvas;

class BaseMode {
public:
	virtual void Initialize() {};
	virtual void Update() {};

	virtual void SetCanvas(Canvas* canvas) {
		canvas_ = canvas;
	}
	virtual void SetCanvasData(std::vector<std::vector<uint32_t>>* canvasData) {
		/*for (int i = 0; i < canvasWidth_; i++) {
			for (int j = 0; j < canvasHeight_; j++) {
				canvasData_ = canvasData;
			}
		}*/
		canvasData_ = canvasData;
	}
	virtual std::vector<std::vector<uint32_t>>* GetCanvasData() {
		return canvasData_;
	}
	virtual void SetMap(std::vector<std::vector<int>>* map) {
		map_ = map;
	}
	virtual std::vector<std::vector<int>>* GetMap() {
		return map_;
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

	virtual void SetCanSize(int width, int height) {
		canvasWidth_ = width;
		canvasHeight_ = height;
	}

protected:
	Canvas* canvas_ = nullptr;

	std::vector<std::vector<uint32_t>>* canvasData_ = nullptr;
	std::vector<std::vector<int>>* map_ = nullptr;

	int xIndex_{};
	int yIndex_{};

	char keys_{};
	char preKeys_{};

	uint32_t color_{};

	int canvasWidth_{};
	int canvasHeight_{};

	bool isAllData = false;
};

class Bucket : public BaseMode {
public:
	void Update();
	void Solid(int xIndex, int yIndex);
};

class WriteMode : public BaseMode {
public:
	void Update();

};

class Erayser : public BaseMode {
public:
	void Update();

};