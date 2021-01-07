#include "FourrierTransform.h"
#define _USE_MATH_DEFINES
#include<cmath>

/**
* Fourrier Transorm class implementation 
* based on Digital Signal Processing, by 
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
	numberOfSamplesX = 0;
	timeDomainXLen = 0;
	xRealCosinesLen = 0;
	xImSinesLen = 0;
}

FourrierTransform::~FourrierTransform()
{
	this->clearMembers();
}

/*
* Section 8.8: Discrete Fourrier transform
*/
void FourrierTransform::discreteTransform(double* xTime, int xTimeLen)
{
	// allocate and initialise members
	clearMembers();
	numberOfSamplesX = xTimeLen;
	this->xRealCosinesLen = (numberOfSamplesX / 2) + 1;
	this->xRealCosines = new double[xRealCosinesLen];
	this->xImSinesLen = (numberOfSamplesX / 2) + 1;
	this->xImSines = new double[xImSinesLen];
	this->timeDomainXLen = xTimeLen;
	this->timeDomainX = new double[xTimeLen];

	for (int index = 0; index < xRealCosinesLen; index++) {
		xRealCosines[index] = 0.0;
		xImSines[index] = 0.0;
	}
	for (int index = 0; index < xTimeLen; index++) {
		timeDomainX[index] = *xTime;
		xTime++;
	}
	
	// CORRELATE xTimeDomain with xRealCosines and xImSines
	for (int kFreqIndex = 0; kFreqIndex < xRealCosinesLen; kFreqIndex++) {
		for (int iTimeIndex = 0; iTimeIndex < xTimeLen; iTimeIndex++) {
			xRealCosines[kFreqIndex] = xRealCosines[kFreqIndex] + timeDomainX[iTimeIndex]
				* cos((double)(2.0 * M_PI * kFreqIndex * iTimeIndex) / ((double)numberOfSamplesX));
			xImSines[kFreqIndex] = xImSines[kFreqIndex] + timeDomainX[iTimeIndex]
				* sin((double)(2.0 * M_PI * kFreqIndex * iTimeIndex) / ((double)numberOfSamplesX));
		}
	}
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
	this->xImSines = new double[xImLen];
	this->xImSinesLen = xImLen;
	this->timeDomainXLen = (xRealLen + xImLen) - 1;
	this->timeDomainX = new double[this->timeDomainXLen];
	for (int index = 0; index < xRealLen; index++) {
		xRealCosines[index] = xReal[index] / xRealLen;
		xImSines[index] = -1.0 * (xIm[index] / xImLen);
	}
	for (int index = 0; index < this->timeDomainXLen; index++) {
		timeDomainX[index] = 0;
	}
	numberOfSamplesX = timeDomainXLen;

	xRealCosines[0] = this->xRealCosines[0] / 2.0;
	xRealCosines[xRealCosinesLen - 1] = xRealCosines[xRealCosinesLen - 1] / 2.0;

	// two ways to calculate it:
	if (true) {
		inverseTransformByFrequencyDomain();
	}
	else {
		inverseTransformByTimeDomain();
	}
}

void FourrierTransform::inverseTransformByTimeDomain()
{
	// for each time domain amplitude, calculate the sum of all the associated frequency domain component values.
	for (int iTimeIndex = 0; iTimeIndex < timeDomainXLen; iTimeIndex++) {
		for (int kFreqIndex = 0; kFreqIndex < xRealCosinesLen; kFreqIndex++) {
			timeDomainX[iTimeIndex] = timeDomainX[iTimeIndex] +
				xRealCosines[kFreqIndex] * cos((2.0 * M_PI * kFreqIndex * iTimeIndex) / ((double)numberOfSamplesX));
			timeDomainX[iTimeIndex] = timeDomainX[iTimeIndex] +
				xImSines[kFreqIndex] * sin((2.0 * M_PI * kFreqIndex * iTimeIndex) / ((double)numberOfSamplesX));

		}
	}
}

void FourrierTransform::inverseTransformByFrequencyDomain()
{
	// for each frequency real and imaginary, add its component value to the time domains.
	for (int kFreqIndex = 0; kFreqIndex < xRealCosinesLen; kFreqIndex++) {
		for (int iTimeIndex = 0; iTimeIndex < timeDomainXLen; iTimeIndex++) {
			timeDomainX[iTimeIndex] = timeDomainX[iTimeIndex]
				+ xRealCosines[kFreqIndex] * cos((2.0 * M_PI * kFreqIndex * iTimeIndex) / ((double)numberOfSamplesX));
			timeDomainX[iTimeIndex] = timeDomainX[iTimeIndex]
				+ xImSines[kFreqIndex] * sin((2.0 * M_PI * kFreqIndex * iTimeIndex) / ((double)numberOfSamplesX));
		}
	}
}

double* FourrierTransform::getTimeDomainX()
{
	return timeDomainX;
}
int FourrierTransform::getTimeDomainXLen()
{
	return timeDomainXLen;
}

double* FourrierTransform::getRealConsinesX()
{
	return xRealCosines;
}

double* FourrierTransform::getImSinesX()
{
	return xImSines;
}

int FourrierTransform::getFreqDomainLen()
{
	return xImSinesLen;
}
