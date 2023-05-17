#pragma once
#include "Canvas.h"
#include "MyMath.h"
#include "PngData.h"

class BaseStateMode {

};


class CSys {
public:
	~CSys() { 
		delete canvas_; 
		//delete pngData_;
	}
	CSys() {}

	void Initialize();

	void Update();

	void Draw();

	void CreateCanvas(const int width, const int height, const int dotSize);

	//void Output(std::vector<std::vector<uint32_t>> canvasData);

	/*void SetTmpCanvas(std::vector<std::vector<uint32_t>> *canvasData) {
		tmpData_ = canvasData;
	}*/

private:
	Canvas* canvas_ = nullptr;

	int canvasWidth_ = 60;
	int canvasHeight_ = 60;
	int dotSize_ = 8;
	
	std::vector<std::vector<uint32_t>> *tmpData_;

	// 
	char keys_[256]{};
	char preKeys_[256]{};

	InVector2 mausePos_{};

//	PngData* pngData_ = nullptr;
	bool isOutputPng = false;
};