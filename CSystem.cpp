#include "CSystem.h"
#include <Novice.h>
#include <stdio.h>
void CSys::Initialize() {
	
	if (canvas_ == nullptr) {
		canvas_ = new Canvas();
		canvas_->Initialize({400, 0 }, canvasWidth_, canvasHeight_, dotSize_);
		isSwich[1] = true;
	}
	
	swichPos[0] = { SwichListPos.x + 20 + SwichSize.x / 2, SwichListPos.y + 20 + SwichSize.y / 2 };
	swichPos[1] = { swichPos[0].x + 40 + SwichSize.x , swichPos[0].y};
	swichPos[2] = { swichPos[1].x + 40 + SwichSize.x , swichPos[0].y };

	WidGauge = { 20 + list.x, 20 + list.y};
	WidHandle = { canvasWidth_, WidGauge.y + gaugeHalfHeight };

	HeiGauge = { WidGauge.x ,  WidGauge.y + 20 };
	HeiHandle = { canvasHeight_ , HeiGauge.y + gaugeHalfHeight };

	DotGauge = { HeiGauge.x , HeiGauge.y + 20 };
	DotHandle = { dotSize_ , DotGauge.y + gaugeHalfHeight  };

}

bool CSys::M2Swich(InVector2 pos, InVector2 size, InVector2 mausePos) {
	if (pos.x + size.x / 2 > mausePos.x && pos.y + size.y / 2 > mausePos.y &&
		pos.x - size.x / 2 < mausePos.x && pos.y - size.y / 2 < mausePos.y) {
		return true;
	}
	return false;
}


void CSys::Update() {
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);

	Novice::GetMousePosition(&mausePos_.x, &mausePos_.y);

	if (!isSwich[2]) {
		swichColor[2] = 0x444444ff;
	}
	else if (isSwich[2]) {
		swichColor[2] = 0xff0000ff;
	}

	for (int i = 0; i < 2; i++) {
		if (!isSwich[i]) {
			swichColor[i] = 0x444444ff;
		}
		else if (isSwich[i]) {
			swichColor[i] = 0xff0000ff;
		}
	}

	if (canvas_ != nullptr) {
		canvas_->Update();
		canvas_->SetMausePos(mausePos_);
		canvas_->SetKeys(keys_, preKeys_);
		
		if (!isSwich[0]) {
			if (M2Swich(swichPos[0], SwichSize, mausePos_)) {
				swichColor[0] = 0xaaaaaaff;

				if (Novice::IsTriggerMouse(0)) {
					isSwich[0] = true;
					isSwich[1] = false;
					delete canvas_;
					canvas_ = nullptr;
					swichColor[0] = 0xff0000ff;
				}
			}

			if (keys_[DIK_D] && !preKeys_[DIK_D]) {
				isSwich[0] = true;
				isSwich[1] = false;
				delete canvas_;
				canvas_ = nullptr;
			}
		}
		if (!isSwich[2]) {
			if (M2Swich(swichPos[2], SwichSize, mausePos_)) {
				swichColor[2] = 0xaaaaaaff;

				if (Novice::IsTriggerMouse(0)) {
					
					Output(canvas_->GetCanvasData(), "./test.png", canvasWidth_, canvasHeight_);
					swichColor[2] = 0xff0000ff;
				}
			}

			if (keys_[DIK_Y] && !preKeys_[DIK_Y]) {
				
				Output(canvas_->GetCanvasData(), "./test.png", canvasWidth_, canvasHeight_);
			}
		}

	}
	else if (canvas_ == nullptr) {
		if (!isSwich[1]) {
			if (M2Swich(swichPos[1], SwichSize, mausePos_)) {
				swichColor[1] = 0xaaaaaaff;

				if (Novice::IsTriggerMouse(0)) {
					isSwich[0] = false;
					isSwich[1] = true;
					CreateCanvas(canvasWidth_, canvasHeight_, dotSize_);
					swichColor[1] = 0xff0000ff;
				}
			}

			if (keys_[DIK_Q] && !preKeys_[DIK_Q]) {
				isSwich[0] = false;
				isSwich[1] = true;
				CreateCanvas(canvasWidth_, canvasHeight_, dotSize_);
			}
		}

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

		
		CheckHandle(isWidClick, WidHandle, canvasWidth_, 400);
		CheckHandle(isHeiClick, HeiHandle, canvasHeight_,400);
		CheckHandle(isDotClick, DotHandle, dotSize_, 100);
	}
	preMausePos_ = mausePos_;
}
void CSys::CheckHandle(bool& isClick, InVector2& handle, int& colorD, int maxGauge) {
	if (!isClick) {
		if (Novice::IsPressMouse(0) && M2Swich(handle, { handleHalfWidth * 2, handleHalfHeight * 2 }, { mausePos_.x - 20, mausePos_.y })) {
			isClick = true;
		}
	}
	else if (isClick) {
		if (!Novice::IsPressMouse(0)) {
			isClick = false;
		}
		if (handle.x < 0 && handle.x > maxGauge) {
			isClick = false;
		}
		handle.x = mausePos_.x - 20;
	}

	if (handle.x >= maxGauge) {
		handle.x = maxGauge - 1;
	}
	if (handle.x < 1) {
		handle.x = 1;
	}


	colorD = handle.x;

}

void CSys::Draw() {
	if (canvas_ != nullptr) {
		canvas_->Draw();
	}
	if (canvas_ == nullptr) {
		Novice::ScreenPrintf(0, 0, "W : %d, H : %d, D : %d", canvasWidth_, canvasHeight_, dotSize_);
		GaugeDraw(WidGauge, WidHandle, BLACK, 400);
		GaugeDraw(HeiGauge, HeiHandle, BLACK, 400);
		GaugeDraw(DotGauge, DotHandle, BLACK, 100);
	}


	Novice::DrawBox(SwichListPos.x, SwichListPos.y, swichListSize.x, swichListSize.y, 0.0f, 0x000000aa, kFillModeSolid);

	for (int i = 0; i < 3; i++) {
		Novice::DrawBox(swichPos[i].x - SwichSize.x / 2, swichPos[i].y - SwichSize.y / 2, SwichSize.x, SwichSize.y, 0.0f, swichColor[i], kFillModeSolid);
	}
	Novice::ScreenPrintf(swichPos[0].x - SwichSize.x / 2, swichPos[0].y - SwichSize.y / 2, "Delete");
	Novice::ScreenPrintf(swichPos[1].x - SwichSize.x / 2, swichPos[1].y - SwichSize.y / 2, "Create");
	Novice::ScreenPrintf(swichPos[2].x - SwichSize.x / 2, swichPos[2].y - SwichSize.y / 2, "Output");

}
void CSys::GaugeDraw(InVector2 Gaugepos, InVector2 Handlepos, uint32_t color, int MaxGauge) {
	Novice::DrawBox(Gaugepos.x + list.x, Gaugepos.y + list.y, MaxGauge, 10, 0.0f, 0xAAAAAAFF, kFillModeSolid);
	Novice::DrawBox(Handlepos.x - handleHalfWidth + 20, Handlepos.y - handleHalfHeight, handleHalfWidth * 2, handleHalfHeight * 2, 0.0f, color, kFillModeSolid);

}
void CSys::CreateCanvas(const int width, const int height, const int dotSize) {
	if (canvas_ == nullptr) {
		canvas_ = new Canvas();
		canvas_->Initialize({ 400, 0 }, width, height, dotSize);
	}
}

void CSys::Output(std::vector<uint32_t> *canvasData,const char* file, const int width, const int height) {
	PngData* pngData = new PngData();
	pngData->WritePng(file, width, height, canvasData);
	delete pngData;
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