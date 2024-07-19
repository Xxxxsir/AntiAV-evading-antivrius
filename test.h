#pragma once
#include<iostream>
#include<bits/stdc++.h>
#include<Windows.h>

using namespace std;
typedef NTSTATUS(WINAPI* PayloadFunction)(int, LPWSTR, ULONG);

void RC4_Init(unsigned char* S, unsigned char* K, unsigned int len);
void RC4_Crypt(unsigned char* S, unsigned char* D, unsigned int len);
void RC4_DeCrpty(unsigned char* S, unsigned char* Key, unsigned char* Data);

unsigned char* inputFile(const char* filename, int& len);
void outputFile(const char* filename, unsigned char* buf, int len);

