#include "PngData.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include "MyMath.h"
 
//void PngData::SetSize(int canWidth, int canHeight) {
//	//width_ = std::size_t(canWidth);
//	//height_ = std::size_t(canHeight);
//	//dotWidth_ = canWidth;
//	//dotHeight_ = canHeight;
//}

//void PngData::Initialize() {
//	/*for (uint32_t i = 0; i < width_; i++) {
//		rgbaX_.emplace_back(i);
//		
//		rgbaX_[i].a = 0x00;
//		rgbaX_[i].r = 0x00;
//		rgbaX_[i].g = 0x00;
//		rgbaX_[i].b = 0x00;
//
//	}
//	for (uint32_t i = 0; i < height_; i++) {
//		rgba_.emplace_back(i);
//		
//		rgba_[i] = rgbaX_;
//	}*/
//
//}

//void PngData::SetCanvasData(std::vector<uint32_t> canpasData) {
//	canpasData_ = canpasData;
//}

void PngData::WritePng(const char *file, const int width, const int height, std::vector<uint32_t> *canvas) {
	
	ColorChange(width, height, canvas);
	/*std::size_t width_{ size_t(width) };
	 std::size_t height_{ size_t(height) };*/

	// std::unique_ptr<MYRGBA[][width_]> rgba(new(std::nothrow) MYRGBA[height_][width_]);
	// if (!rgba) return;

	//for (std::size_t row{}; row < height; ++row) {
		stbi_write_png(file, static_cast<int>(width), static_cast<int>(height), static_cast<int>(sizeof(uint32_t)), canvas->data(), 0/* static_cast<int>(height)*/);

	//}
		//for (std::size_t col{}; col < width_; ++col) {
		//	rgba[row][col].r = 255; //
		//	rgba[row][col].g = 0;
		//	rgba[row][col].b = 0;
		//	rgba[row][col].a = 255; //
		//}
	ColorChange(width, height, canvas);
}

//void PngData::ColorChange(uint32_t color) {
//	uint32_t redChecker = 0xFF000000;
//	uint32_t greenChecker = 0x00FF0000;
//	uint32_t blueChecker = 0x0000FF00;
//	uint32_t alphaChecker = 0x000000FF;
//	red = color & redChecker;
//	green = color & greenChecker;
//	blue = color & blueChecker;
//	alpha = color & alphaChecker;
//
//	ColorR(red);
//	ColorG(green);
//	ColorB(blue);
//}

uint32_t PngData::ColorInverse(uint32_t colorD) {
	uint32_t redChecker = 0xFF000000;
	uint32_t greenChecker = 0x00FF0000;
	uint32_t blueChecker = 0x0000FF00;
	uint32_t alphaChecker = 0x000000FF;
	uint32_t red = colorD & redChecker;
	uint32_t green = colorD & greenChecker;
	uint32_t blue = colorD & blueChecker;
	uint32_t alpha = colorD & alphaChecker;

	ColorR(red);
	ColorG(green);
	ColorB(blue);
	ColorA(alpha);

	uint32_t resultColor = ( red | green | blue | alpha);
	return resultColor;
}


void PngData::ColorChange(const int width, const int height, std::vector<uint32_t>* canvas) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			canvas->at((width * i) + j) = ColorInverse(canvas->at((width * i) + j));
		}
	}

}

