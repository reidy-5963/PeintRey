#include "CSystem.h"
#include <Novice.h>
#include <stdio.h>
void CSys::Initialize() {
	
	if (canvas_ == nullptr) {
		canvas_ = new Canvas();
		canvas_->Initialize({ 0, 0 }, canvasWidth_, canvasHeight_, dotSize_);
	}
	
}

void CSys::Update() {
	//
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);

	Novice::GetMousePosition(&mausePos_.x, &mausePos_.y);

	if (canvas_ != nullptr) {
		canvas_->Update();
		canvas_->SetMausePos(mausePos_);
		canvas_->SetKeys(keys_, preKeys_);
		//SetTmpCanvas(&(canvas_->GetCanvasData()));

		if (keys_[DIK_Y] && !preKeys_[DIK_Y]) {
			Output(canvas_->GetCanvasData(), "./test.png", canvasWidth_, canvasHeight_);
		}

		if (keys_[DIK_D] && !preKeys_[DIK_D]) {
			delete canvas_;
			canvas_ = nullptr;
		}
	}
	else if (canvas_ == nullptr) {
		if (keys_[DIK_UPARROW] && !preKeys_[DIK_UPARROW]) {
			canvasHeight_++;
		}
		if (keys_[DIK_DOWNARROW] && !preKeys_[DIK_DOWNARROW]) {
			canvasHeight_--;
		}
		if (keys_[DIK_RIGHTARROW] && !preKeys_[DIK_RIGHTARROW]) {
			canvasWidth_++;
		}
		if (keys_[DIK_LEFTARROW] && !preKeys_[DIK_LEFTARROW]) {
			canvasWidth_--;
		}
		if (keys_[DIK_O] && !preKeys_[DIK_O]) {
			dotSize_++;
		}
		if (keys_[DIK_P] && !preKeys_[DIK_P]) {
			dotSize_--;
		}

		
		if (keys_[DIK_Q] && !preKeys_[DIK_Q]) {
			CreateCanvas(canvasWidth_, canvasHeight_, dotSize_);
		}

		
	}
}

void CSys::Draw() {
	if (canvas_ != nullptr) {
		canvas_->Draw();
	}
	if (canvas_ == nullptr) {
		Novice::ScreenPrintf(0, 0, "W : %d, H : %d, D : %d", canvasWidth_, canvasHeight_, dotSize_);
	}
}

void CSys::CreateCanvas(const int width, const int height, const int dotSize) {
	if (canvas_ == nullptr) {
		canvas_ = new Canvas();
		canvas_->Initialize({ 0, 0 }, width, height, dotSize);
	}
}

//void CSys::Output(std::vector<std::vector<uint32_t>> canvasData) {
//	if (canvasData.data() != nullptr && !isOutputPng) {
//		isOutputPng = true;
//
//		pngData_ = new PngData();
//		pngData_->SetCanvasData(canvas_->GetCanvasData());
//		pngData_->SetSize(canvasWidth_, canvasHeight_);
//		pngData_->Initialize();
//
//	}
//}
void CSys::Output(std::vector<uint32_t> *canvasData,const char* file, const int width, const int height) {
	PngData* pngData = new PngData();
	pngData->WritePng(file, width, height, canvasData);

}
//void CSys::Output(std::vector<uint32_t> canvasData/*, const int width, const int height*/) {
//	FILE* fp;
//	uint8_t pngCheck[] = { 0x89, 0x50, 0x4e, 0x47};
//	/*size_t pngCheck2 = 0x474e;
//	size_t pngCheck3 = 0x0a0d;
//	size_t pngCheck4 = 0x0a1a;*/
//
//
//
//	/*pngCheck2 = pngCheck2 << 16;
//	pngCheck3 = pngCheck3 << 32;
//	pngCheck4 = pngCheck4 << 48;
//	size_t pngCheck = (pngCheck1 | pngCheck2 | pngCheck3 | pngCheck4);*/
//
//	/*uint32_t IENDlength = 0x00000000;
//	uint32_t IENDtype = 0x49454e44;
//	size_t IENDdataAll[] = { IENDtype };
//	uint32_t IENDcrc = crcKen(IENDdataAll);*/
//
//	uint32_t IHDRlength = sizeof(canvasData.size());
//	uint32_t IHDRtype = 0x52444849;
//	uint32_t IHDRdataW = uint32_t(1280);
//	uint32_t IHDRdataH = uint32_t(720);
//	/*uint8_t IHDRdeapBit = 0x08;
//	uint8_t IHDRcolorType = 0x06;
//	uint8_t IHDRzipS = 0x00;
//	uint8_t IHDRfilterS = 0x00;
//	uint8_t IHDRinterS = 0x00;
//	size_t IHDRdataAll[] = { IHDRtype, IHDRdataW, IHDRdataH, IHDRdeapBit, IHDRcolorType, IHDRzipS, IHDRfilterS, IHDRinterS };
//	uint32_t IHDRcrc = crcKen(IHDRdataAll);
//	size_t IHDR[] = { IHDRtype, IHDRdataW, IHDRdataH, IHDRdeapBit, IHDRcolorType, IHDRzipS, IHDRfilterS, IHDRinterS, IHDRcrc};*/
//
//	
//
//	//IENDcrc;
//
//	////char buf[] = { char(pngCheck) };
//	//int dabuf[] = {
//	//	int(pngCheck1),int(pngCheck2),int(pngCheck3),int(pngCheck4),
//	//	int(IHDRlength), int(IHDRtype), int(IHDRdataW), int(IHDRdataH), int(IHDRdeapBit), int(IHDRcolorType), int(IHDRzipS), int(IHDRfilterS), int(IHDRinterS), int(IHDRcrc),
//
//	//	 int(IENDlength),  int(IENDtype),  int(IENDcrc)
//	//};
//
//	
//
//	fopen_s(&fp, "test.png", "wb");
//	if (!fp) {
//		return;
//	}
//
//	for (int i = 0; i < 4; i++) {
//		fwrite(&pngCheck[i], sizeof(pngCheck[i]), 1, fp);
//
//	}
//	fwrite(&IHDRlength, sizeof(IHDRlength), 1, fp);
//	fwrite(&IHDRtype, sizeof(IHDRtype), 1, fp);
//	fwrite(&IHDRdataW, sizeof(IHDRdataW), 1, fp);
//	fwrite(&IHDRdataH, sizeof(IHDRdataH), 1, fp);
//	fclose(fp);
//}