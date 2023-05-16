//#include "PngData.h"
//
//void PngData::SetSize(int canWidth, int canHeight) {
//	width_ = size_t(canWidth);
//	height_ = size_t(canHeight);
//	dotWidth_ = canWidth;
//	dotHeight_ = canHeight;
//}
//
//void PngData::Initialize() {
//	for (uint32_t i = 0; i < width_; i++) {
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
//	}
//
//}
//
//void PngData::SetCanvasData(std::vector<std::vector<uint32_t>> canpasData) {
//	canpasData_ = canpasData;
//}
//
//void PngData::WritePng(char aa) {
//	char fileName[8] = { aa };
//	char fileAfter[8] = { ".png" };
//
//	//strcat_s(fileName, fileAfter);
//	/* constexpr std::size_t width{ 1280 };*/
//	 /*constexpr std::size_t height{ 720};*/
//
//
//	//for (std::size_t row{}; row < height_; ++row)
//	//	for (std::size_t col{}; col < width_; ++col) {
//	//		rgba_[row][col].r = 255; //
//	//		rgba_[row][col].g = 0;
//	//		rgba_[row][col].b = 0;
//	//		rgba_[row][col].a = 255; //
//	//	}
//	//stbi_write_png(fileName, static_cast<int>(width_), static_cast<int>(height_), static_cast<int>(sizeof(RGBA)), rgba_.data(), 0);
//}
//
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
//
//
