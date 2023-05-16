#include "CSystem.h"
#include <Novice.h>


void CSys::Initialize() {
	
	if (canvas_ == nullptr) {
		canvas_ = new Canvas();
		canvas_->Initialize(canvasWidth_, canvasHeight_, 16);
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

		if (keys_[DIK_D] && !preKeys_[DIK_D]) {
			delete canvas_;
			canvas_ = nullptr;
		}
	}

	if (canvas_ == nullptr) {
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


		
		if (keys_[DIK_Q] && !preKeys_[DIK_Q]) {
			CreateCanvas(canvasWidth_, canvasHeight_);
		}
	}
}

void CSys::Draw() {
	if (canvas_ != nullptr) {
		canvas_->Draw();
	}
	if (canvas_ == nullptr) {
		Novice::ScreenPrintf(0, 0, "W : %d, H : %d", canvasWidth_, canvasHeight_);
	}
}

void CSys::CreateCanvas(const int width, const int height) {
	if (canvas_ == nullptr) {
		canvas_ = new Canvas();
		canvas_->Initialize(width, height, 16);
	}
}