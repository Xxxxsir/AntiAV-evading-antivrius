#include"test.h"

unsigned char* inputFile(const char* filename, int& len) {
	FILE* fp = NULL;
	int err = fopen_s(&fp, filename, "rb");
	if (err != 0 || !fp) {
		exit(-1);
	}

	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	rewind(fp);

	unsigned char* lpAddress = (unsigned char*)malloc(len);
	fread(lpAddress, 1, len, fp);
	fclose(fp);
	return lpAddress;
}

void outputFile(const char* filename, unsigned char* buf, int len) {
	FILE* fp = NULL;
	fopen_s(&fp, filename, "wb");
	if (!fp) {
		printf("Error: unable to open file for writing\n");
		exit(-1);
	}

	fwrite(buf, 1, len, fp);
	printf("write done");
	fclose(fp);
}