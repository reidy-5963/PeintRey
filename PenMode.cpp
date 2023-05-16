#include "PenMode.h"



void WriteMode::Update() {
	if (map_[yIndex_][xIndex_] == 0
		&& keys_) {
		map_[yIndex_][xIndex_] = 1;
		canvasData_[yIndex_][xIndex_] = color_;
	}

}


void Erayser::Update() {
	if (map_[yIndex_][xIndex_] == 1
		&& keys_) {
		map_[yIndex_][xIndex_] = 0;
		canvasData_[yIndex_][xIndex_] = 0x00000000;
	}
}

void Bucket::Update() {
	if (map_[yIndex_][xIndex_] == 0
		&& keys_ && !preKeys_) {
		Solid(xIndex_, yIndex_);

	}

}

void Bucket::Solid(int xIndex, int yIndex) {
	if (map_[yIndex][xIndex] == 0) {
		map_[yIndex][xIndex] = 1;
		canvasData_[yIndex][xIndex] = color_;

		for (int i = 1; i <= xIndex; i++) {
			if (map_[yIndex][xIndex - i] == 1) {
				break;
			}
			Solid(xIndex - i, yIndex);
		}
		for (int i = 1; (xIndex + i) < canvasWidth_; i++) {
			if (map_[yIndex][xIndex + i] == 1) {
				break;
			}
			Solid(xIndex + i, yIndex);
		}

		for (int i = 1; i <= yIndex; i++) {
			if (map_[yIndex - i][xIndex] == 1) {
				break;
			}
			Solid(xIndex, yIndex - i);
		}
		for (int i = 1; (yIndex + i) < canvasHeight_; i++) {
			if (map_[yIndex + i][xIndex] == 1) {
				break;
			}
			Solid(xIndex, yIndex + i);
		}

		/*while (map_[yIndex][xIndex - i] == 0) {
			if (xIndex < 1) {
				break;
			}
			Solid(xIndex - i, yIndex);
			i++;
		}*/
		//i = 1;
		/*while (map_[yIndex - i][xIndex] == 0) {
			Solid(xIndex, yIndex - i);
			i++;
		}
		i = 1;
		while (map_[yIndex + i][xIndex] == 0) {
			Solid(xIndex, yIndex + i);
			i++;
		}
		i = 1;
		while (map_[yIndex][xIndex + i] == 0) {
			Solid(xIndex + i, yIndex);
			i++;
		}*/
	}
}
