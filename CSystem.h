#pragma once
#include "Canvas.h"
#include "MyMath.h"


class BaseStateMode {

};


class CSys {
public:
	~CSys() { 
		delete canvas_; 
	}
	CSys() {}

	void Initialize();

	void Update();

	void Draw();

	void CreateCanvas(const int width, const int height);

	void Output();

private:
	Canvas* canvas_ = nullptr;

	int canvasWidth_ = 80;
	int canvasHeight_ = 45;
	
	std::vector<std::vector<uint32_t>> tmpData_;

	// 
	char keys_[256]{};
	char preKeys_[256]{};

	InVector2 mausePos_{};
};