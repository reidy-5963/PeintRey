#include "Canvas.h"
#include "Novice.h"


void Canvas::Initialize(InVector2 pos, const int kWidth, const int kHeight, int canvasDotSize) {
	pos_ = pos;
	canvasWidth_ = kWidth;
	canvasHeight_ = kHeight;
	canvasDotSize_ = canvasDotSize;

	swichPos[0] = { SwichListPos.x + 20 + SwichSize.x / 2, SwichListPos.y + 20 + SwichSize.y / 2 };
	swichPos[1] = { SwichListPos.x + 20 + SwichSize.x / 2, swichPos[0].y + SwichSize.y / 2 + 20 + SwichSize.y / 2 };
	swichPos[2] = { SwichListPos.x + 20 + SwichSize.x / 2, swichPos[1].y + SwichSize.y / 2 + 20 + SwichSize.y / 2 };

	for (int i = 0; i < canvasHeight_; i++) {
		for (int j = 0; j < canvasWidth_; j++) {
			/*map_.emplace_back((canvasHeight_ * i) + j).r = 0x00;
			map_.emplace_back((canvasHeight_ * i) + j).g = 0x00;
			map_.emplace_back((canvasHeight_ * i) + j).b = 0x00;
			map_.emplace_back((canvasHeight_ * i) + j).a = 0x00;*/
			canvasData_.emplace_back((i * canvasWidth_) + j) = 0;
			/*mapX_[i] = NONE;
			canvasDataX_[i] = 0x00000000;*/
		}
	}
	//for (int i = 0; i < canvasHeight_ ; i++) {
	//	map_.emplace_back(i) = mapX_;
	//	canvasData_.emplace_back(i) = canvasDataX_;
	//	/*map_[i] = mapX_;
	//	canvasData_[i] = canvasDataX_;*/
	//}
	

	mode_ = new WriteMode();
	BModeIni();
	swichColor[0] = 0xff0000ff;
	isSwich[0] = true;

	colorData_ = new Color();
	colorData_->SetPos({ 40, 20 });

	colorData_->Initialize();
	textureHandle_ = Novice::LoadTexture("./Resources/WhiteBase.png");

	mauseWheel = canvasDotSize_ * 120;
}

void Canvas::BModeIni() {
	mode_->SetCanvas(this);
	mode_->SetCanSize(canvasWidth_, canvasHeight_, canvasDotSize_);
	mode_->SetCanvasData(&canvasData_);
	//mode_->SetMap(&map_);
}
bool Canvas::M2List(InVector2 pos, InVector2 size, InVector2 mausePos) {
	if (pos.x + size.x > mausePos.x && pos.y + size.y > mausePos.y &&
		pos.x  < mausePos.x && pos.y < mausePos.y) {
		return true;
	}
	return false;
}

bool Canvas::M2Swich(InVector2 pos, InVector2 size, InVector2 mausePos) {
	if (pos.x + size.x / 2 > mausePos.x && pos.y + size.y / 2 > mausePos.y &&
		pos.x - size.x / 2 < mausePos.x && pos.y - size.y / 2 < mausePos.y) {
		return true;
	}
	return false;
}

void Canvas::Update() {
	mauseWheel += Novice::GetWheel();
	if(mauseWheel > 100 * 120){
		mauseWheel = 100 * 120;
	}

	if (mauseWheel <= 0) {
		mauseWheel = 0;
		canvasDotSize_ = 1;
	}
	else {
		canvasDotSize_ = (mauseWheel / 120);
	}
	//canvasDotSize_ = mauseWheel;
	colorData_->SetKeys(keys_, preKeys_);
	colorData_->SetMausePos({mausePos_.x + pos_.x,mausePos_.y + pos_.y});
	colorData_->SetLeftMause(Novice::IsPressMouse(0));
	colorData_->SetLeftMauseTori(Novice::IsTriggerMouse(0));


	if (!isPeint){
		colorData_->Update();
	}
	color_ = ColorD(colorData_->GetColor());

	int xIndex = mausePos_.x / canvasDotSize_;
	int yIndex = mausePos_.y / canvasDotSize_;
	if (yIndex >= 0 && xIndex >= 0 &&
		yIndex < canvasHeight_ && xIndex < canvasWidth_ )
	{

		mode_->SetIndex(xIndex, yIndex);
		mode_->SetKeys(keys_[DIK_R], preKeys_[DIK_R]);
		mode_->SetColor(color_);
		mode_->SetLeftMause(Novice::IsPressMouse(0));
		mode_->SetLeftMauseTori(Novice::IsTriggerMouse(0));
		mode_->SetCanDotSize(canvasDotSize_);
		mode_->SetMausePos(mausePos_);

		if (keys_[DIK_LSHIFT]) {
			if (Novice::IsPressMouse(0)) {
				//if (MoveCanvas) {
					pos_.x = nP2P.x + SystemMausePos_.x;
					pos_.y = nP2P.y + SystemMausePos_.y;
				//}
				/*else if (!MoveCanvas) {
					nowPos.x = SystemMausePos_.x;
					nowPos.y = SystemMausePos_.y;
					nP2P.x = pos_.x - nowPos.x;
					nP2P.y = pos_.y - nowPos.y;
					MoveCanvas = true;
				}*/
			}
			else if (!Novice::IsPressMouse(0)) {
				nowPos.x = SystemMausePos_.x;
				nowPos.y = SystemMausePos_.y;

				nP2P.x = pos_.x - nowPos.x;
				nP2P.y = pos_.y - nowPos.y;

			}
			
		}
		else if (!keys_[DIK_LSHIFT]) {
			if (!M2List(SwichListPos, swichListSize, SystemMausePos_) &&
				!M2List(colorData_->GetColListPos(), colorData_->GetColListSize(), SystemMausePos_)) 
			{
				MoveCanvas = false;
				mode_->Update();
				color_ = mode_->GetColor();

				if (Novice::IsPressMouse(0)) {
					isPeint = true;
				}


			}
			
		}

	}

	if (!Novice::IsPressMouse(0)) {
		isPeint = false;
	}

	for (int i = 0; i < 3; i++) {
		if (!isSwich[i]) {
			swichColor[i] = 0x444444ff;

		}
		else if (isSwich[i]) {
			swichColor[i] = 0xff0000ff;
		}
	}

	if (!isSwich[0]) {
		if (M2Swich(swichPos[0], SwichSize, SystemMausePos_)) {
			swichColor[0] = 0xaaaaaaff;

			if (Novice::IsTriggerMouse(0)) {
				isSwich[0] = true;
				isSwich[1] = false;
				isSwich[2] = false;
				delete mode_;
				mode_ = new WriteMode();
				BModeIni();
				swichColor[0] = 0xff0000ff;
			}
		}
		if (keys_[DIK_1]) {
			isSwich[0] = true;
			isSwich[1] = false;
			isSwich[2] = false;
			delete mode_;
			mode_ = new WriteMode();
			BModeIni();
		}

	}
	
	if (!isSwich[1]) {
		if (M2Swich(swichPos[1], SwichSize, SystemMausePos_)) {
			swichColor[1] = 0xaaaaaaff;

			if (Novice::IsTriggerMouse(0)) {
				isSwich[0] = false;
				isSwich[1] = true;
				isSwich[2] = false;
				delete mode_;
				mode_ = new Erayser();
				BModeIni();
				swichColor[1] = 0xff0000ff;
			}
		}

		if (keys_[DIK_2]) {
			isSwich[0] = false;
			isSwich[1] = true;
			isSwich[2] = false;
			delete mode_;
			mode_ = new Erayser();
			BModeIni();
		}
	}
	
	if (!isSwich[2]) {
		if (M2Swich(swichPos[2], SwichSize, SystemMausePos_)) {
			swichColor[2] = 0xaaaaaaff;

			if (Novice::IsTriggerMouse(0)) {
				isSwich[0] = false;
				isSwich[1] = false;
				isSwich[2] = true;
				delete mode_;
				mode_ = new Bucket();
				BModeIni();
				swichColor[2] = 0xff0000ff;
			}
		}

		if (keys_[DIK_3]) {
			isSwich[0] = false;
			isSwich[1] = false;
			isSwich[2] = true;
			delete mode_;
			mode_ = new Bucket();
			BModeIni();
		}
	}


}

void Canvas::SetMausePos(InVector2 mausePos) {
	mausePos_.x = mausePos.x - pos_.x;
	mausePos_.y = mausePos.y - pos_.y;
	SystemMausePos_ = mausePos;
}

void Canvas::Draw() {
	/*for (int i = 0; i < canvasHeight_; i++) {
		for (int j = 0; j < canvasWidth_; j++) {
			Novice::DrawBox(i * canvasDotSize_, j * canvasDotSize_, canvasDotSize_, canvasDotSize_, 0.0f, WHITE, kFillModeWireFrame);
		}
	}*/
	
	CanvasDraw(pos_, canvasWidth_, canvasHeight_, canvasDotSize_);
	
	
	for (int i = 0; i < canvasHeight_; i++) {
		for (int j = 0; j < canvasWidth_; j++) {
			if (canvasData_[(canvasWidth_ * i) + j] != 0x00000000) {
				//Novice::DrawBox(j * canvasDotSize_, i * canvasDotSize_, canvasDotSize_, canvasDotSize_, 0.0f, canvasData_[i][j], kFillModeSolid);
			
				Novice::DrawQuad(
					pos_.x + j * canvasDotSize_, pos_.y + i * canvasDotSize_,
					pos_.x + j * canvasDotSize_ + canvasDotSize_, pos_.y + i * canvasDotSize_,
					pos_.x + j * canvasDotSize_, pos_.y + i * canvasDotSize_ + canvasDotSize_,
					pos_.x + j * canvasDotSize_ + canvasDotSize_, pos_.y + i * canvasDotSize_ + canvasDotSize_,
					0, 0, canvasDotSize_, canvasDotSize_, textureHandle_, canvasData_[(canvasWidth_ * i) + j]
				);
			}
		}
	}

	Novice::DrawBox(SwichListPos.x, SwichListPos.y, swichListSize.x, swichListSize.y, 0.0f, 0x000000aa, kFillModeSolid);

	for (int i = 0; i < 3; i++) {
		Novice::DrawBox(swichPos[i].x - SwichSize.x / 2, swichPos[i].y - SwichSize.y / 2, SwichSize.x, SwichSize.y, 0.0f, swichColor[i], kFillModeSolid);
	}
	Novice::ScreenPrintf(swichPos[0].x - SwichSize.x / 2, swichPos[0].y - SwichSize.y / 2, "Line");
	Novice::ScreenPrintf(swichPos[1].x - SwichSize.x / 2, swichPos[1].y - SwichSize.y / 2, "Erayser");
	Novice::ScreenPrintf(swichPos[2].x - SwichSize.x / 2, swichPos[2].y - SwichSize.y / 2, "Bucket");

	//MausePos
	Novice::DrawBox(int(mausePos_.x) - (canvasDotSize_ / 2) + pos_.x, int(mausePos_.y) - (canvasDotSize_ / 2) + pos_.y, canvasDotSize_, canvasDotSize_, 0.0f, color_, kFillModeSolid);


	colorData_->Draw();
}

void Canvas::CanvasDraw(InVector2 pos, const int canWidth, const int canHeight, const int dotSize) {
	const int kWidthSubdivi = canWidth + 1;
	const int kHeightSubdivi = canHeight + 1;
	const int kGridEvery = dotSize;
	

	for (int y = 0; y < kHeightSubdivi; y++) {
		InVector2 yLine[2]{};
		yLine[0] = { 0 + pos.x, kGridEvery * y + pos.y };
		yLine[1] = { kGridEvery * canWidth + pos.x, kGridEvery * y + pos.y };

		Novice::DrawLine(yLine[0].x, yLine[0].y, yLine[1].x, yLine[1].y, 0xffffffaa);
	}
	for (int x = 0; x < kWidthSubdivi; x++) {
		InVector2 xLine[2]{};
		xLine[0] = { kGridEvery * x + pos.x ,0 + pos.y };
		xLine[1] = { kGridEvery * x + pos.x,kGridEvery * canHeight + pos.y };

		Novice::DrawLine(xLine[0].x, xLine[0].y, xLine[1].x, xLine[1].y, 0xffffffaa);
	}

	Novice::ScreenPrintf(300, 300, "%d, %d, %d", mausePos_.x, mausePos_.y, mauseWheel);
}