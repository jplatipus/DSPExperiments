#include "Convolution.h"

/******
 Convolution as a class, based on Digital Signal Processing, by 
 Steven W. Smith, chapter 7

*/
	/*
	* Allocates and copies arguments to members.
	* TODO: use memcpy to copy array arguments instead of for loops
	*/
	Convolution::Convolution(double* inputSig, int inputSigLen, double* imp, int impLen)
	{
		this->inputSignal = new double[inputSigLen];
		this->inputSignalLen = inputSigLen;
		this->impulse = new double[impLen];
		this->impulseLen = impLen;
		this->outputSignalLen = inputSigLen + impLen - 1;
		this->outputSignal = new double[inputSigLen + impLen - 1];
		for (int index = 0; index < outputSignalLen; index++) {
			outputSignal[index] = 0.0;
		}
		for (int index = 0; index < inputSignalLen; index++) {
			inputSignal[index] = inputSig[index];
		}
		for (int index = 0; index < impulseLen; index++) {
			impulse[index] = imp[index];
		}
	}

	/*
	* clears allocated pointer members.
	*/
	Convolution::~Convolution() {
		delete this->inputSignal;
		delete this->impulse;
		delete this->outputSignal;
	}

	/*
	* convolution based in the input side: slowly builds up output, hence needs
	* reference to the output to read and update it
	*/
	void Convolution::convoluteInputSide() {
		for (int index = 0; index < inputSignalLen; index++) {
			for (int hIndex = 0; hIndex < impulseLen; hIndex++) {
				outputSignal[index + hIndex] =
					outputSignal[index + hIndex]
					+ (inputSignal[index] * impulse[hIndex]);
			}
		}
	}

	/*
	* convulution based on the output side: builds up output one at a time, 
	* based on the input. It can be parallelised
	*/
	void Convolution::convoluteOutputSide() {
		for (int index = 0; index < outputSignalLen; index++) {
			outputSignal[index] = 0.0;
			for (int hIndex = 0; hIndex < impulseLen; hIndex++) {
				int inputIndex = index - hIndex;
				if (inputIndex < 0 || inputIndex > inputSignalLen) {
					continue;
				}
				outputSignal[index] =
					outputSignal[index]
					+ impulse[hIndex] * inputSignal[inputIndex];
			}
		}
	}

	/*
	return output signal array: the pointer's lifetime is the same as the class instance's
	*/
	double* Convolution::getConvolutedOutput() {
		return outputSignal;
	}

	int Convolution::getConvolutedOutLen() {
		return outputSignalLen;
	}
