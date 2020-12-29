#pragma once
#include <iostream>

using namespace std;
/**
Convolution as a class, based on Digital Signal Processing, by
Steven W.Smith, chapter 7
**/
class Convolution
{
private:
	double* inputSignal = nullptr;
	int inputSignalLen = 0;
	double* impulse = nullptr;
	int impulseLen = 0;
	double* outputSignal = nullptr;
	int outputSignalLen = 0;

public:
	Convolution(double* inX, int inXlen, double* imH, int imHlen);
	~Convolution();
	void convoluteInputSide();
	void convoluteOutputSide();
	double *getConvolutedOutput();
	int getConvolutedOutLen();
};

