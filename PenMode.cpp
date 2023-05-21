#include "PenMode.h"
#include "Novice.h"


void WriteMode::Update() {
	if (canvasData_->at((canvasWidth_ * yIndex_) + xIndex_) != color_
		&& leftMause_) {
		canvasData_->at((canvasWidth_ * yIndex_) + xIndex_) = color_;
	}
	//mausePos.x = xIndex_ * canvasDot_;
	//mausePos.y = yIndex_ * canvasDot_;
	const int max = 200;
	Vector2 line{ float(mausePos.x - preMausePos.x), float(mausePos.y - preMausePos.y) };


	Vector2 lineerInter[max];
	int linerXIndex;
	int linerYIndex;

	for (int i = 0; i < max; i++) {
		lineerInter[i] = { float(preMausePos.x) + ((line.x / float(max)) * i), float(preMausePos.y) + ((line.y / float(max)) * i) };
		linerXIndex = int(lineerInter[i].x) / canvasDot_;
		linerYIndex = int(lineerInter[i].y) / canvasDot_;

		if (linerXIndex >= 0 && linerXIndex < canvasWidth_ &&
			linerYIndex >= 0 && linerYIndex < canvasHeight_)
		{
			if (canvasData_->at((canvasWidth_ * (linerYIndex)) + (linerXIndex)) != color_
				&& leftMause_) {
				canvasData_->at((canvasWidth_ * (linerYIndex)) + (linerXIndex)) = color_;
			}
		}

	}
	//Novice::ScreenPrintf(100, 400, "%d, %d, %d, %d", mausePos.x, mausePos.y, preMausePos.x, preMausePos.y);


	//preMausePos = mausePos;

}

void Erayser::Update() {
	if (canvasData_->at((canvasWidth_ * yIndex_) + xIndex_) != 0x00000000
		&& leftMause_) {
		canvasData_->at((canvasWidth_ * yIndex_) + xIndex_) = 0x00000000;
	}

	const int max = 200;
	Vector2 line{ float(mausePos.x - preMausePos.x), float(mausePos.y - preMausePos.y) };


	Vector2 lineerInter[max];
	int linerXIndex;
	int linerYIndex;

	for (int i = 0; i < max; i++) {
		lineerInter[i] = { float(preMausePos.x) + ((line.x / float(max)) * i), float(preMausePos.y) + ((line.y / float(max)) * i) };
		linerXIndex = int(lineerInter[i].x) / canvasDot_;
		linerYIndex = int(lineerInter[i].y) / canvasDot_;

		if (linerXIndex >= 0 && linerXIndex < canvasWidth_ &&
			linerYIndex >= 0 && linerYIndex < canvasHeight_)
		{
			if (canvasData_->at((canvasWidth_ * (linerYIndex)) + (linerXIndex)) != 0x00000000
				&& leftMause_) {
				canvasData_->at((canvasWidth_ * (linerYIndex)) + (linerXIndex)) = 0x00000000;
			}
		}

	}

	//preMausePos = mausePos;


}



void Bucket::Update() {


	if (canvasData_->at((canvasWidth_ * yIndex_) + xIndex_) != color_
		&& leftMauseTri_) {
		Paint(xIndex_, yIndex_, color_);

	}

}

//
void Bucket::Solid(int xIndex, int yIndex) {

	//
	if (xIndex < 0 || xIndex >= canvasWidth_ ||
		yIndex < 0 || yIndex >= canvasHeight_ ||
		canvasData_->at((canvasWidth_ * yIndex) + xIndex) == color_) {
		//
		return;
	}

	//
	canvasData_->at((canvasWidth_ * yIndex) + xIndex) = color_;


	//
	Solid(xIndex + 1, yIndex);
	Solid(xIndex - 1, yIndex);
	Solid(xIndex, yIndex - 1);
	Solid(xIndex, yIndex + 1);
}


void Bucket::ScanLine(int leftX, int rightX, int y, uint32_t beforeColor) {
	while (leftX <= rightX) {
		for (; leftX <= rightX; leftX++) {
			if (canvasData_->at((canvasWidth_ * y) + leftX) == beforeColor) {
				break;
			}
		}
		if (canvasData_->at((canvasWidth_ * y) + leftX) != beforeColor) {
			break;
		}
		for (; leftX <= rightX; leftX++) {
			if (canvasData_->at((canvasWidth_ * y) + leftX) != beforeColor) {
				break;
			}
		}

		EndIdx->sx = leftX - 1;
		EndIdx->sy = y;

		if (++EndIdx == &buff[MaxBuff]) {
			EndIdx = buff;
		}
	}
}
void Bucket::Paint(int x, int y, uint32_t paintColor) {
	int leftX, rightX;
	int leftY, rightY;
	int i;
	uint32_t beforeColor = canvasData_->at((canvasWidth_ * y) + x);
	if (paintColor == beforeColor) {
		return;
	}
	StartIdx = buff;
	EndIdx = buff + 1;
	StartIdx->sx = x;
	StartIdx->sy = y;

	do {
		leftX = rightX = StartIdx->sx;
		leftY = StartIdx->sy;
		if (++StartIdx == &buff[MaxBuff]) {
			StartIdx = buff;
		}

		if (canvasData_->at((canvasWidth_ * leftY) + leftX) != beforeColor) {
			continue;
		}
		while (rightX < canvasWidth_ - 1) {
			if (canvasData_->at((canvasWidth_ * leftY) + rightX + 1) != beforeColor) {
				break;
			}
			rightX++;
		}
		while (leftX > 0) {
			if (canvasData_->at((canvasWidth_ * leftY) + leftX - 1) != beforeColor) {
				break;
			}
			leftX--;
		}
		for (i = leftX; i <= rightX; i++) {
			canvasData_->at((canvasWidth_ * leftY) + i) = paintColor;
		}

		if (leftY - 1 >= 0) {
			ScanLine(leftX, rightX, leftY - 1, beforeColor);
		}
		if (leftY + 1 <= canvasHeight_ - 1) {
			ScanLine(leftX, rightX, leftY + 1, beforeColor);
		}
	} while (StartIdx != EndIdx);

	StartIdx = buff;
	EndIdx = buff + 1;
	StartIdx->sx = x;
	StartIdx->sy = y;

	do {
		leftX = rightX = StartIdx->sx;
		rightY = StartIdx->sy;
		if (++StartIdx == &buff[MaxBuff]) {
			StartIdx = buff;
		}

		if (canvasData_->at((canvasWidth_ * rightY) + leftX) != beforeColor) {
			continue;
		}
		while (rightX < canvasWidth_ - 1) {
			if (canvasData_->at((canvasWidth_ * rightY) + rightX + 1) != beforeColor) {
				break;
			}
			rightX++;
		}
		while (leftX > 0) {
			if (canvasData_->at((canvasWidth_ * rightY) + leftX - 1) != beforeColor) {
				break;
			}
			leftX--;
		}
		for (i = leftX; i <= rightX; i++) {
			canvasData_->at((canvasWidth_ * rightY) + i) = paintColor;
		}

		if (leftY - 1 >= 0) {
			ScanLine(leftX, rightX, rightY - 1, paintColor);
		}
		if (leftY + 1 <= canvasHeight_ - 1) {
			ScanLine(leftX, rightX, rightY + 1, paintColor);
		}
	} while (StartIdx != EndIdx);
}
