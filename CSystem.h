#pragma once
#include "Canvas.h"
#include "PngData.h"
//#define STBI_MSC_SECURE_CRT
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include <stb_image.h>
//#include <stb_image_write.h>
//
//class BaseStateMode {
//
//};


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

	void Output(std::vector<uint32_t> *canvasData,const char *file, const int width, const int height);

	/*void SetTmpCanvas(std::vector<std::vector<uint32_t>> *canvasData) {
		tmpData_ = canvasData;
	}*/

	uint32_t crcText(uint32_t crc, size_t d, uint32_t magic) {
		int i;
		for (i = 0; i < 8; i++) {
			int b = (crc & 1);
			crc >>= 1;
			if ((d >> i) & 1) crc |= UINT32_C(0x80000000);
			if (b) crc ^= magic;
		}
		return crc;
	}

	/*uint32_t reverce(uint32_t x) {
		int i;
		uint32_t res = 0;
		for (i = 0; i < 32; i++) {
			if ((x >> i) & 1) res |= UINT32_C(1) << (31 - i);
		}
		return res;
	}*/

	uint32_t crcKen(size_t* data) {
		const uint32_t magicNum = UINT32_C(0xedb88320);
		uint32_t crc = 0;

		int i, j;
		for (i = 0; data[i]; i++) {
			crc = crcText(crc, data[i] ^ (i < 4 ? 0xff : 0), magicNum);
		}
		for (j = 0; j < 4; j++) {
			crc = crcText(crc, i + j < 4 ? 0xff : 0, magicNum);
		}

		return ~crc;
	}

private:
	Canvas* canvas_ = nullptr;

	int canvasWidth_ = 64;
	int canvasHeight_ = 64;
	int dotSize_ = 10;
	
	std::vector<std::vector<uint32_t>> *tmpData_;

	// 
	char keys_[256]{};
	char preKeys_[256]{};

	InVector2 mausePos_{};                    

//	PngData* pngData_ = nullptr;
	bool isOutputPng = false;
};