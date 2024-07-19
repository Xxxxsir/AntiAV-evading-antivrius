#include"test.h"


/** 
* you can customize your own xor decoder and encoder here
* 
* 
* 
* */
void RC4_Init(unsigned char* S, unsigned char* K, unsigned int len)
{
	int i, j = 0;
	unsigned char ch_tmp, T[256] = { 0 };
	for (i = 0; i < 256; ++i) {
		S[i] = i;
		T[i] = K[i % len];
	}
	for (i = 0; i < 256; ++i) {
		j = (j + S[i] + T[i]) % 256;
		ch_tmp = S[i];
		S[i] = S[j];
		S[j] = ch_tmp;
	}
}

void RC4_Crypt(unsigned char* S, unsigned char* D, unsigned int len) {
	int i = 0, j = 0, int_tmp;
	unsigned int n;
	unsigned char ch_tmp;
	for (n = 0; n < len; ++n) {
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		ch_tmp = S[i];
		S[i] = S[j];
		S[j] = ch_tmp;
		int_tmp = (S[i] + S[j]) % 256;
		D[n] ^= S[n];
	}
}

void RC4_DeCrpty(unsigned char* S, unsigned char* Key, unsigned char* Data)
{
	RC4_Init(S, Key, strlen((char*)Key));
	RC4_Crypt(S, Data, strlen((char*)Data));
}