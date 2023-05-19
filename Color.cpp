#include "Color.h"
#include "Novice.h"

void Color::SetMausePos(InVector2 mausePos) {
	mausePos_.x = mausePos.x - colorList.x;
	mausePos_.y = mausePos.y - colorList.y;

}

void Color::Initialize() {
	redD = 100;
	greenD = 255;
	blueD = 255;
	alphaD = 255;
	redGauge[0] = {0, 0};
	redGauge[1] = { redGauge[0].x + gaugeHalfWidth * 2,  redGauge[0].y};
	redHandle = { redD, redGauge[0].y + gaugeHalfHeight};

	greenGauge[0] = { redGauge[0].x,  redGauge[0].y + 20 };
	greenGauge[1] = { greenGauge[0].x + gaugeHalfWidth * 2,  greenGauge[0].y };
	greenHandle = { greenD, greenGauge[0].y + gaugeHalfHeight };

	blueGauge[0] = { greenGauge[0].x,  greenGauge[0].y + 20 };
	blueGauge[1] = { blueGauge[0].x + gaugeHalfWidth * 2,  blueGauge[0].y };
	blueHandle = { blueD, blueGauge[0].y + gaugeHalfHeight };

	alphaGauge[0] = { blueGauge[0].x,  blueGauge[0].y + 20 };
	alphaGauge[1] = { alphaGauge[0].x + gaugeHalfWidth * 2,  alphaGauge[0].y };
	alphaHandle = { alphaD, alphaGauge[0].y + gaugeHalfHeight };

	colorBox = { alphaGauge[0].x, alphaGauge[0].y + 20 };
}

void Color::CheckHandle(bool &isClick, InVector2 &handle, int &colorD) {
	if (!isClick) {
		if (leftMause_ && MauseToHandle(handle)) {
			isClick = true;
		}
	}
	else if (isClick) {
		if (!leftMause_) {
			isClick = false;
		}
		if (handle.x < 0 && handle.x > 256) {
			isClick = false;
		}
		handle.x = mausePos_.x;
	}

	if (handle.x > 256) {
		handle.x = 255;
	}
	if (handle.x < 0) {
		handle.x = 0;
	}


	colorD = handle.x;

}

void Color::Update() {
	color_.r = unsigned char(redD);
	color_.g = unsigned char(greenD);
	color_.b = unsigned char(blueD);
	color_.a = unsigned char(alphaD);

		//ColorD(blueD, greenD, redD, alphaD);
	CheckHandle(isRedClick, redHandle, redD);
	CheckHandle(isGreenClick, greenHandle, greenD);
	CheckHandle(isBlueClick, blueHandle, blueD);
	CheckHandle(isAlphaClick, alphaHandle, alphaD);
}

bool Color::MauseToHandle(InVector2 Handle) {
	if (Handle.x - handleHalfWidth < mausePos_.x && Handle.x + handleHalfWidth > mausePos_.x) {
		if (Handle.y - handleHalfHeight < + mausePos_.y && Handle.y + handleHalfHeight > + mausePos_.y) {
			return true;
		}
	}
	return false;
}

void Color::GaugeDraw(InVector2 Gaugepos, InVector2 Handlepos, uint32_t color) {
	Novice::DrawBox(Gaugepos.x + colorList.x, Gaugepos.y + colorList.y, 255, 10, 0.0f, 0xAAAAAAFF, kFillModeSolid);
	Novice::DrawBox(Handlepos.x - handleHalfWidth + colorList.x, Handlepos.y - handleHalfHeight + colorList.y, handleHalfWidth * 2, handleHalfHeight * 2, 0.0f, color, kFillModeSolid);

}


void Color::Draw() {
	Novice::ScreenPrintf(0, 0, "RGBA %d, %d, %d, %d", redD, greenD, blueD, alphaD);
	GaugeDraw(redGauge[0], redHandle, RED);
	GaugeDraw(greenGauge[0], greenHandle, GREEN);
	GaugeDraw(blueGauge[0], blueHandle, BLUE);
	GaugeDraw(alphaGauge[0], alphaHandle, BLACK);

	Novice::DrawBox(colorBox.x + colorList.x, colorBox.y + colorList.y, 255, 10, 0.0f, ColorD(color_), kFillModeSolid);

	//Novice::DrawBox(redGauge[0].x, redGauge[0].y, 255, 10, 0.0f, RED, kFillModeSolid);

	//Novice::DrawBox(colorList.x + 40, colorList.y + 40, 255, 10, 0.0f, GREEN, kFillModeSolid);

	//Novice::DrawBox(colorList.x + 40, colorList.y + 60, 255, 10, 0.0f, BLUE, kFillModeSolid);

	//Novice::DrawBox(colorList.x + 40, colorList.y + 60, 255, 10, 0.0f, BLACK, kFillModeSolid);

	//Novice::DrawBox(redHandle.x - handleHalfWidth, redHandle.y - handleHalfHeight, handleHalfWidth * 2, handleHalfHeight * 2, 0.0f, RED, kFillModeSolid);

	Novice::ScreenPrintf(500, 500, "%d", MauseToHandle(redHandle));
}