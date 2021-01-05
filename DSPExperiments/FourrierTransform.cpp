#include "FourrierTransform.h"
#define _USE_MATH_DEFINES
#include<cmath>

/**
* Fourrier Transorm class implementation 
* Convolution as a class, based on Digital Signal Processing, by 
 Steven W. Smith, chapter 8
*/

FourrierTransform::FourrierTransform()
{

}

/*
* Deallocate members
*/
void FourrierTransform::clearMembers()
{
	if (this->timeDomainX != nullptr) {
		delete this->timeDomainX;
	}
	if (this->xImSines != nullptr) {
		delete this->xImSines;
	}
	if (this->xRealCosines != nullptr) {
		delete this->xRealCosines;
	}
}

FourrierTransform::~FourrierTransform()
{
	this->clearMembers();
}

/*
* Section 8/3
*/
void FourrierTransform::inverseTransform(double* xReal, int xRealLen, double* xIm, int xImLen)
{
	// allocate & initilise members
	// find sine and cosine amplitudes
	this->clearMembers();
	this->xRealCosines = new double[xRealLen];
	this->xRealCosinesLen = xRealLen;
	for (int index = 0; index < xRealLen; index++) {
		this->xRealCosines[index] = xReal[index]/ xRealLen;
	}
	this->xImSines = new double[xImLen];
	this->xImSinesLen = xImLen;
	for (int index = 0; index < xImLen; index ++) {
		this->xImSines[index] = -1*(xIm[index]/ xImLen);
	}
	this->timeDomainXLen = (xRealLen * 2) - 1;
	this->timeDomainX = new double[this->timeDomainXLen];
	for (int index = 0; index < this->timeDomainXLen; index++) {
		this->timeDomainX[index] = 0;
	}
	this->xRealCosines[0] = this->xRealCosines[0] / 2;
	this->xRealCosines[xRealLen - 1] = xRealCosines[xRealLen - 1] / 2;

	// two ways to calculate it:
	
	//inverseTransformByFrequencyDomain();
	inverseTransformByTimeDomain();
}

void FourrierTransform::inverseTransformByTimeDomain()
{
	// for each time domain amplitude, calculate the sum of all the associated frequency domain component values.
	for (int iTimeIndex = 0; iTimeIndex < this->timeDomainXLen; iTimeIndex++) {
		for (int kFreqIndex = 0; kFreqIndex < this->xRealCosinesLen; kFreqIndex++) {
			this->timeDomainX[iTimeIndex] = this->timeDomainX[iTimeIndex] +
				this->xRealCosines[kFreqIndex] * cos(2 * M_PI * kFreqIndex * iTimeIndex / ((double)(this->timeDomainXLen+1)));
			this->timeDomainX[iTimeIndex] = this->timeDomainX[iTimeIndex] +
				this->xImSines[kFreqIndex] * sin(2 * M_PI * kFreqIndex * iTimeIndex / ((double)this->timeDomainXLen+1));

		}
	}
}

void FourrierTransform::inverseTransformByFrequencyDomain()
{
	// for each frequency real and imaginary, add its component value to the time domains.
	for (int kFreqIndex = 0; kFreqIndex < this->xRealCosinesLen; kFreqIndex++) {
		for (int iTimeIndex = 0; iTimeIndex < this->timeDomainXLen; iTimeIndex++) {
			this->timeDomainX[iTimeIndex] = this->timeDomainX[iTimeIndex]
				+ this->xRealCosines[kFreqIndex] * cos(2 * M_PI * kFreqIndex * iTimeIndex / ((double)(this->timeDomainXLen+1)));
			this->timeDomainX[iTimeIndex] = this->timeDomainX[iTimeIndex]
				+ this->xImSines[kFreqIndex] * sin(2 * M_PI * kFreqIndex * iTimeIndex / ((double)(this->timeDomainXLen+1)));
		}
	}
}

double* FourrierTransform::getTimeDomainX()
{
	return this->timeDomainX;
}
int FourrierTransform::getTimeDomainXLen()
{
	return this->timeDomainXLen;
}