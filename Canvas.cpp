#include "Canvas.h"
#include "Novice.h"


void Canvas::Initialize(InVector2 pos, const int kWidth, const int kHeight, int canvasDotSize) {
	pos_ = pos;
	canvasWidth_ = kWidth;
	canvasHeight_ = kHeight;
	canvasDotSize_ = canvasDotSize;


	/*int Max{};
	int Min{};
	if (canvasHeight_ <= canvasWidth_) {
		Max = canvasWidth_;
		Min = canvasHeight_;
	}
	else if (canvasHeight_ > canvasWidth_) {
		Max = canvasHeight_;
		Min = canvasWidth_;
	}*/

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

	colorData_ = new Color();
	colorData_->SetPos({ 40, 20 });

	colorData_->Initialize();
	textureHandle_ = Novice::LoadTexture("./Resources/WhiteBase.png");
}

void Canvas::BModeIni() {
	mode_->SetCanvas(this);
	mode_->SetCanSize(canvasWidth_, canvasHeight_, canvasDotSize_);
	mode_->SetCanvasData(&canvasData_);
	//mode_->SetMap(&map_);
}

void Canvas::Update() {
	
	colorData_->SetKeys(keys_, preKeys_);
	colorData_->SetMausePos({mausePos_.x + pos_.x,mausePos_.y + pos_.y});
	colorData_->SetLeftMause(Novice::IsPressMouse(0));
	colorData_->SetLeftMauseTori(Novice::IsTriggerMouse(0));


	colorData_->Update();
	color_ = ColorD(colorData_->GetColor());

	if (mausePos_.y / canvasDotSize_ >= 0 && mausePos_.x / canvasDotSize_ >= 0 &&
		mausePos_.y / canvasDotSize_ < canvasHeight_ && mausePos_.x / canvasDotSize_ < canvasWidth_
		) {
		int xIndex = mausePos_.x / canvasDotSize_;
		int yIndex = mausePos_.y / canvasDotSize_;

		/*if (map_[mausePos_.y / canvasDotSize_][mausePos_.x / canvasDotSize_] == NONE
			&& keys_[DIK_R]) {
			map_[mausePos_.y / canvasDotSize_][mausePos_.x / canvasDotSize_] = WRITE;
			canvasData_[mausePos_.y / canvasDotSize_][mausePos_.x / canvasDotSize_] = color_;
		}*/
		mode_->SetIndex(xIndex, yIndex);
		mode_->SetKeys(keys_[DIK_R], preKeys_[DIK_R]);
		mode_->SetColor(color_);
		mode_->SetLeftMause(Novice::IsPressMouse(0));
		mode_->SetLeftMauseTori(Novice::IsTriggerMouse(0));

		mode_->Update();
		//canvasData_ = mode_->GetCanvasData();
		/*map_ = mode_->GetMap();*/
		color_ = mode_->GetColor();
	}
	if (keys_[DIK_1]) {
		delete mode_;
		mode_ = new WriteMode();
		BModeIni();
	}
	if (keys_[DIK_2]) {
		delete mode_;
		mode_ = new Erayser();
		BModeIni();
	}
	if (keys_[DIK_3]) {
		delete mode_;
		mode_ = new Bucket();
		BModeIni();
	}

}

void Canvas::SetMausePos(InVector2 mausePos) {
	mausePos_.x = mausePos.x - pos_.x;
	mausePos_.y = mausePos.y - pos_.y;

}

void Canvas::Draw() {
	/*for (int i = 0; i < canvasHeight_; i++) {
		for (int j = 0; j < canvasWidth_; j++) {
			Novice::DrawBox(i * canvasDotSize_, j * canvasDotSize_, canvasDotSize_, canvasDotSize_, 0.0f, WHITE, kFillModeWireFrame);
		}
	}*/
	
	CanvasDraw(pos_, canvasWidth_, canvasHeight_, canvasDotSize_);
	
	/*int Max{};
	int Min{};
	if (canvasHeight_ <= canvasWidth_) {
		Max = canvasWidth_;
		Min = canvasHeight_;
	}
	else if (canvasHeight_ > canvasWidth_) {
		Max = canvasHeight_;
		Min = canvasWidth_;
	}*/

	for (int i = 0; i < canvasHeight_; i++) {
		for (int j = 0; j < canvasWidth_; j++) {
			if (canvasData_[(canvasWidth_ * i) + j] != 0x00000000) {
				//Novice::DrawBox(j * canvasDotSize_, i * canvasDotSize_, canvasDotSize_, canvasDotSize_, 0.0f, canvasData_[i][j], kFillModeSolid);
			
				/*Novice::DrawQuad(
					pos_.x + j * canvasDotSize_, pos_.y + i * canvasDotSize_,
					pos_.x + j * canvasDotSize_ + canvasDotSize_, pos_.y + i * canvasDotSize_,
					pos_.x + j * canvasDotSize_, pos_.y + i * canvasDotSize_ + canvasDotSize_,
					pos_.x + j * canvasDotSize_ + canvasDotSize_, pos_.y + i * canvasDotSize_ + canvasDotSize_,
					0, 0, canvasDotSize_, canvasDotSize_, textureHandle_, canvasData_[(canvasWidth_ * i) + j]
				);*/
			}
		}
	}

	

	Novice::DrawBox(int(mausePos_.x) - 8 + pos_.x , int(mausePos_.y) - 8 + pos_.y, canvasDotSize_, canvasDotSize_, 0.0f, color_, kFillModeSolid);


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

		Novice::DrawLine(yLine[0].x, yLine[0].y, yLine[1].x, yLine[1].y, WHITE);
	}
	for (int x = 0; x < kWidthSubdivi; x++) {
		InVector2 xLine[2]{};
		xLine[0] = { kGridEvery * x + pos.x ,0 + pos.y };
		xLine[1] = { kGridEvery * x + pos.x,kGridEvery * canHeight + pos.y };

		Novice::DrawLine(xLine[0].x, xLine[0].y, xLine[1].x, xLine[1].y, WHITE);
	}

	Novice::ScreenPrintf(300, 300, "%d, %d", mausePos_.x, mausePos_.y);
}