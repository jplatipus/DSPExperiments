#include "Convolution.h"

/******
 Convolution as a class, based on Digital Signal Processing, by 
 Steven W. Smith, chapter 7

*/
	/*
	* Allocates and copies arguments to members.
	* TODO: use memcpy to copy array arguments instead of for loops
	*/
	Convolution::Convolution(double* inputSignal, int inputSignalLen, double* impulse, int impulseLen)
	{
		this->inputSignal = new double[inputSignalLen];
		this->inputSignalLen = inputSignalLen;
		this->impulse = new double[impulseLen];
		this->impulseLen = impulseLen;
		this->outputSignalLen = inputSignalLen + impulseLen - 1;
		this->outputSignal = new double[inputSignalLen + impulseLen - 1];
		for (int index = 0; index < this->outputSignalLen; index++) {
			this->outputSignal[index] = 0.0;
		}
		for (int index = 0; index < this->inputSignalLen; index++) {
			this->inputSignal[index] = inputSignal[index];
		}
		for (int index = 0; index < this->impulseLen; index++) {
			this->impulse[index] = impulse[index];
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
		for (int index = 0; index < this->inputSignalLen; index++) {
			for (int hIndex = 0; hIndex < this->impulseLen; hIndex++) {
				this->outputSignal[index + hIndex] =
					this->outputSignal[index + hIndex]
					+ (this->inputSignal[index] * this->impulse[hIndex]);
			}
		}
	}

	/*
	* convulution based on the output side: builds up output one at a time, 
	* based on the input. It can be parallelised
	*/
	void Convolution::convoluteOutputSide() {
		for (int index = 0; index < this->outputSignalLen; index++) {
			this->outputSignal[index] = 0.0;
			for (int hIndex = 0; hIndex < this->impulseLen; hIndex++) {
				int inputIndex = index - hIndex;
				if (inputIndex < 0 || inputIndex > inputSignalLen) {
					continue;
				}
				this->outputSignal[index] =
					this->outputSignal[index]
					+ this->impulse[hIndex] * this->inputSignal[inputIndex];
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
