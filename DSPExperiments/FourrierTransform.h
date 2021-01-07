#pragma once
using namespace std;

class FourrierTransform
{
private:
	int numberOfSamplesX = 0;
	double* timeDomainX = nullptr;
	int timeDomainXLen = 0;
	double* xRealCosines = nullptr;
	int xRealCosinesLen = 0;
	double* xImSines = nullptr;
	int xImSinesLen = 0;
	void clearMembers();
	void inverseTransformByTimeDomain();
	void inverseTransformByFrequencyDomain();
public:
	~FourrierTransform();
	void discreteTransform(double* xTime, int xTimeLen);
	FourrierTransform();
	void inverseTransform(double* xReal, int xRealLen, double* xIm, int xImLen);
	double* getTimeDomainX();
	int getTimeDomainXLen();
	double *getRealConsinesX();
	double *getImSinesX();
	int getFreqDomainLen();

};

