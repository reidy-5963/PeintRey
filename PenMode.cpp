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


	if (/*canvasData_->at((canvasHeight_ * yIndex_) + xIndex_) != color_
		&&*/ leftMauseTri_) {
		Solid(xIndex_, yIndex_/*, color_*/);

	}

}


void Bucket::Solid(int xIndex, int yIndex) {
	/*if (solid) {
		for (int i = 1; i <= xIndex; i++) {
			if (map_->at((canvasHeight_ * yIndex) + xIndex - i) == 1 || xIndex - i <= 0) {
				return;
			}
			SSSolid(xIndex - i, yIndex, SoloSolid(xIndex - i, yIndex, -i, 0));
		}

		for (int i = 1; (xIndex + i) < canvasWidth_; i++ || xIndex + i > canvasWidth_) {
			if (map_->at((canvasHeight_ * yIndex) + xIndex + i) == 1 || xIndex + i > canvasWidth_) {
				break;
			}
			SSSolid(xIndex + i, yIndex, SoloSolid(xIndex + i, yIndex, i, 0));
		}
		for (int i = 1; i <= yIndex; i++) {
			if (map_->at((canvasHeight_ * (yIndex - i)) + xIndex) == 1 || yIndex - i <= 0) {
				break;
			}
			SSSolid(xIndex , yIndex - i, SoloSolid(xIndex, yIndex - i, 0, -i));
		}

	}
	SoloSolid(xIndex, yIndex, 0, 0);*/
	//uint32_t color = canvasData_->at((canvasHeight_ * yIndex) + xIndex);

	if (xIndex > 0 || xIndex <= canvasWidth_ ||
		yIndex > 0 || yIndex <= canvasHeight_) {
		if (canvasData_->at((canvasWidth_ * yIndex) + xIndex) == color_) {
			return;
		}
	}



	if (canvasData_->at((canvasWidth_ * yIndex) + xIndex) != color_) {
		canvasData_->at((canvasWidth_ * yIndex) + xIndex) = color_;

	}


	Solid(xIndex, yIndex + 1);
	Solid(xIndex, yIndex - 1);
	Solid(xIndex + 1, yIndex);
	Solid(xIndex - 1, yIndex);


}

void Bucket::ScanLine(int leftX, int rightX, int y, uint32_t col) {
	while (leftX <= rightX) {
		for (; leftX <= rightX; leftX++) {
			if (canvasData_->at((canvasWidth_ * y) + leftX) == col) {
				break;
			}
		}
		if (canvasData_->at((canvasWidth_ * y) + leftX) != col) {
			break;
		}

		for (; leftX <= rightX; leftX++) {
			if (canvasData_->at((canvasWidth_ * y) + leftX) != col) {
				break;
			}
		}

		eIdx->sx = leftX - 1;
		eIdx->sy = y;

		if (++eIdx == &buff[MaxBuff]) {
			eIdx = buff;
		}
	}
}

void Bucket::Paint(int x, int y, uint32_t paintCol) {
	int leftX, rightX;
	int leftY, rightY;
	int i;
	uint32_t col = canvasData_->at((canvasWidth_ * y) + x);
	if (paintCol == col) {
		return;
	}

	sIdx = buff;
	eIdx = buff + 1;
	sIdx->sx = x;
	sIdx->sy = y;

	do {
		leftX = rightX = sIdx->sx;
		leftY = sIdx->sy;
		if (++sIdx == &buff[MaxBuff]) {
			sIdx = buff;
		}

		if (canvasData_->at((canvasWidth_ * leftY) + leftX) != col) {
			continue;
		}
		while (rightX < canvasWidth_ - 1) {
			if (canvasData_->at((canvasWidth_ * leftY) + rightX + 1) != col) {
				break;
			}
			rightX++;
		}
		while (leftX > 0) {
			if (canvasData_->at((canvasWidth_ * leftY) + leftX - 1) != col) {
				break;
			}
			leftX--;
		}
		for (i = leftX; i <= rightX; i++) {
			canvasData_->at((canvasWidth_ * leftY) + i) = paintCol;
		}

		if (leftY - 1 >= 0) {
			ScanLine(leftX, rightX, leftY - 1, col);
		}
		if (leftY + 1 <= canvasHeight_ - 1) {
			ScanLine(leftX, rightX, leftY + 1, col);
		}
	} while (sIdx != eIdx);

	sIdx = buff;
	eIdx = buff + 1;
	sIdx->sx = x;
	sIdx->sy = y;

	do {
		leftX = rightX = sIdx->sx;
		rightY = sIdx->sy;
		if (++sIdx == &buff[MaxBuff]) {
			sIdx = buff;
		}

		if (canvasData_->at((canvasWidth_ * rightY) + leftX) != col) {
			continue;
		}
		while (rightX < canvasWidth_ - 1) {
			if (canvasData_->at((canvasWidth_ * rightY) + rightX + 1) != col) {
				break;
			}
			rightX++;
		}
		while (leftX > 0) {
			if (canvasData_->at((canvasWidth_ * rightY) + leftX - 1) != col) {
				break;
			}
			leftX--;
		}
		for (i = leftX; i <= rightX; i++) {
			canvasData_->at((canvasWidth_ * rightY) + i) = paintCol;
		}

		if (leftY - 1 >= 0) {
			ScanLine(leftX, rightX, rightY - 1, paintCol);
		}
		if (leftY + 1 <= canvasHeight_ - 1) {
			ScanLine(leftX, rightX, rightY + 1, paintCol);
		}
	} while (sIdx != eIdx);
	//canvasData_->at((canvasHeight_ * y) + x) = paintCol;
}
