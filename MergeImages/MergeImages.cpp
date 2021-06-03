#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 100

struct Pixel
{
	char red;
	char green;
	char blue;
};

bool isBitOn(char letter, int index)
{
	return (letter >> index & 1) ? true : false;
}

//  BLACK = 0, else -> other color

void cutForms() {  // create the first picture - the black form the input pacman

	FILE* pacman_input = fopen("pacman_input.bmp", "rb");
	FILE* white_image = fopen("white_image.bmp", "rb");
	FILE* black_forms = fopen("black_forms.bmp", "wb");

	fseek(pacman_input, 0, SEEK_SET);
	fseek(white_image, 0, SEEK_SET);

	char pacBuffer[BUFFER_SIZE];
	char whiteBuffer[BUFFER_SIZE];

	fread(pacBuffer, 54, 1, pacman_input);
	fread(whiteBuffer, 54, 1, white_image);
	fwrite(whiteBuffer, 54, 1, black_forms);

	char inputByte;
	char whiteByte;
	char result;
	bool isFinished = false;

	while (fread(&inputByte, 1, 1, pacman_input) != 0) {
		fread(&whiteByte, 1, 1, white_image);

		// we have 1 byte from pacman - 1 byte from white image
		if (!isFinished) {
			result = inputByte ^ whiteByte;
			fwrite(&result, 1, 1, black_forms);
				
			if (feof(pacman_input)) {
				isFinished = true;
			}

		}
	}

	fclose(pacman_input);
	fclose(white_image);
	fclose(black_forms);
}

void mergeMapWithBlackForms() {

	FILE* map_input = fopen("map_input.bmp", "rb");
	FILE* black_forms = fopen("black_forms.bmp", "rb");
	FILE* firstMerge = fopen("firstMerge.bmp", "wb");

	fseek(map_input, 0, SEEK_SET);
	fseek(black_forms, 0, SEEK_SET);

	char mapBuffer[BUFFER_SIZE];
	char blackFormsBuffer[BUFFER_SIZE];

	fread(mapBuffer, 54, 1, map_input);
	fread(blackFormsBuffer, 54, 1, black_forms);
	fwrite(mapBuffer, 54, 1, firstMerge);

	char mapByte;
	char formByte;
	char result;
	bool isFinished = false;

	while (fread(&formByte, 1, 1, black_forms) != 0) {
		fread(&mapByte, 1, 1, map_input);

		// we have 1 byte from pacman - 1 byte from white image
		if (!isFinished) {
			result = mapByte & formByte;
			fwrite(&result, 1, 1, firstMerge);

			if (feof(black_forms)) {
				isFinished = true;
			}
		}
	}

	fclose(map_input);
	fclose(black_forms);
	fclose(firstMerge);
}

void finalMerge() {  // create the first picture - the black form the input pacman

	FILE* firstMerge = fopen("firstMerge.bmp", "rb");
	FILE* pacman_input = fopen("pacman_input.bmp", "rb");
	FILE* finalMerge = fopen("finalMerge.bmp", "wb");

	fseek(firstMerge, 0, SEEK_SET);
	fseek(pacman_input, 0, SEEK_SET);

	char firstMergeBuffer[BUFFER_SIZE];
	char pacBuffer[BUFFER_SIZE];

	fread(firstMergeBuffer, 54, 1, firstMerge);
	fread(pacBuffer, 54, 1, pacman_input);
	fwrite(firstMergeBuffer, 54, 1, finalMerge);

	char firstMergeByte;
	char pacmanByte;
	char result;
	bool isFinished = false;

	while (fread(&firstMergeByte, 1, 1, firstMerge) != 0) {
		fread(&pacmanByte, 1, 1, pacman_input);

		// we have 1 byte from pacman - 1 byte from white image
		if (!isFinished) {
			result = firstMergeByte | pacmanByte;
			fwrite(&result, 1, 1, finalMerge);

			if (feof(firstMerge)) {
				isFinished = true;
			}

		}
	}

	fclose(firstMerge);
	fclose(pacman_input);
	fclose(finalMerge);
}


int main() {

	cutForms();
	mergeMapWithBlackForms(); 
	finalMerge();

	return 0;
}