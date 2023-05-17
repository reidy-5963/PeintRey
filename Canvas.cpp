#include "Canvas.h"
#include "Novice.h"


void Canvas::Initialize(const int kWidth, const int kHeight, int canvasDotSize) {
	canvasWidth_ = kWidth;
	canvasHeight_ = kHeight;
	canvasDotSize_ = canvasDotSize;

	for (int i = 0; i < canvasWidth_ ; i++) {
		mapX_.emplace_back(i) = NONE;
		canvasDataX_.emplace_back(i) = 0x00000000;
		/*mapX_[i] = NONE;
		canvasDataX_[i] = 0x00000000;*/
	}
	for (int i = 0; i < canvasHeight_ ; i++) {
		map_.emplace_back(i) = mapX_;
		canvasData_.emplace_back(i) = canvasDataX_;
		/*map_[i] = mapX_;
		canvasData_[i] = canvasDataX_;*/
	}
	

	mode_ = new WriteMode();
	BModeIni();

	colorData_ = new Color();
	colorData_->SetPos({ 40, 20 });

	colorData_->Initialize();
	textureHandle_ = Novice::LoadTexture("./Resources/WhiteBase.png");
}

void Canvas::BModeIni() {
	mode_->SetCanvas(this);
	mode_->SetCanSize(canvasWidth_, canvasHeight_);
	mode_->SetCanvasData(&canvasData_);
	mode_->SetMap(&map_);
}

void Canvas::Update() {
	
	colorData_->SetKeys(keys_, preKeys_);
	colorData_->SetMausePos(mausePos_);

	colorData_->Update();
	color_ = colorData_->GetColor();

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

		mode_->Update();
		/*canvasData_ = mode_->GetCanvasData();
		map_ = mode_->GetMap();
		color_ = mode_->GetColor();*/
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
	mausePos_ = mausePos;
}

void Canvas::Draw() {
	/*for (int i = 0; i < canvasHeight_; i++) {
		for (int j = 0; j < canvasWidth_; j++) {
			Novice::DrawBox(i * canvasDotSize_, j * canvasDotSize_, canvasDotSize_, canvasDotSize_, 0.0f, WHITE, kFillModeWireFrame);
		}
	}*/
	CanvasDraw(canvasWidth_, canvasHeight_, canvasDotSize_);
	for (int i = 0; i < canvasHeight_; i++) {
		for (int j = 0; j < canvasWidth_; j++) {
			if (canvasData_[i][j] != 0x00000000) {
				//Novice::DrawBox(j * canvasDotSize_, i * canvasDotSize_, canvasDotSize_, canvasDotSize_, 0.0f, canvasData_[i][j], kFillModeSolid);
			
				Novice::DrawQuad(
					j * canvasDotSize_, i * canvasDotSize_,
					j * canvasDotSize_ + canvasDotSize_, i * canvasDotSize_,
					j * canvasDotSize_, i * canvasDotSize_ + canvasDotSize_,
					j * canvasDotSize_ + canvasDotSize_, i * canvasDotSize_ + canvasDotSize_,
					0, 0, canvasDotSize_, canvasDotSize_, textureHandle_, canvasData_[i][j]
				);
			}
		}
	}

	

	Novice::DrawBox(int(mausePos_.x) - 8, int(mausePos_.y) - 8, canvasDotSize_, canvasDotSize_, 0.0f, color_, kFillModeSolid);


	colorData_->Draw();
}

void Canvas::CanvasDraw(const int canWidth, const int canHeight, const int dotSize) {
	const int kWidthSubdivi = canWidth + 1;
	const int kHeightSubdivi = canHeight + 1;
	const int kGridEvery = dotSize;
	

	for (int y = 0; y < kHeightSubdivi; y++) {
		InVector2 yLine[2]{};
		yLine[0] = { 0, kGridEvery * y };
		yLine[1] = { kGridEvery * canWidth, kGridEvery * y };

		Novice::DrawLine(yLine[0].x, yLine[0].y, yLine[1].x, yLine[1].y, WHITE);
	}
	for (int x = 0; x < kWidthSubdivi; x++) {
		InVector2 xLine[2]{};
		xLine[0] = { kGridEvery * x ,0 };
		xLine[1] = { kGridEvery * x ,kGridEvery * canHeight };

		Novice::DrawLine(xLine[0].x, xLine[0].y, xLine[1].x, xLine[1].y, WHITE);
	}

	Novice::ScreenPrintf(300, 300, "%d, %d", mausePos_.x, mausePos_.y);
}