#pragma once
using namespace std;

class FourrierTransform
{
private:
	double* timeDomainX = nullptr;
	int timeDomainXLen = 0;
	double* xRealCosines = nullptr;
	int xRealCosinesLen = 0;
	double* xImSines = nullptr;
	int xImSinesLen = 0;
	void clearMembers();
public:
	~FourrierTransform();
	FourrierTransform();
	void inverseTransform(double* xReal, int xRealLen, double* xIm, int xImLen);
	void inverseTransformByTimeDomain();
	void inverseTransformByFrequencyDomain();
	double* getTimeDomainX();
	int getTimeDomainXLen();
};

