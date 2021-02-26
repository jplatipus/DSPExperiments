/* 
* DSPExperiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
* based on Digital Signal Processing, by
* Steven W.Smith
*/

#include <iostream>
#include "Convolution.h"
#include "FourrierTransform.h"

void testConvolution()
{
    std::cout << "Running Convolution Test\n";
    double input[] = { 0.0, -1.0, -1.25, 2.0, 1.5, 1.5, 0.75, 0, -0.75 };
    double impulse[] = { 1.0, -0.5, -0.25, -0.0 };
    double* output = nullptr;

    Convolution inc = Convolution(input, 9, impulse, 4);
    inc.convoluteInputSide();
    int outputLen = inc.getConvolutedOutLen();
    output = inc.getConvolutedOutput();
    printf("input side convolution =  {\n\t");
    for (int index = 0; index < outputLen; index++) {
        printf("%0.02f, ", *output);
        output++;
    }
    printf("\n}\n");

    Convolution outc = Convolution(input, 9, impulse, 4);
    outc.convoluteOutputSide();
    outputLen = outc.getConvolutedOutLen();
    output = outc.getConvolutedOutput();
    printf("output side convolution =  {\n\t");
    for (int index = 0; index < outputLen; index++) {
        printf("%0.02f, ", *output);
        output++;
    }
    printf("\n}\n");
}

void testLecture4Example()
{
    std::cout << "Running Lecture 4, slide 28 Convolution Test\n";
    double input[] = { 1.0, 0.0, 2.0, 3.0, 0.0, 1.0 };
    double impulse[] = { 2.0, 0.0, 1.0 };
    double* output = nullptr;

    Convolution inc = Convolution(input, 5, impulse, 3);
    inc.convoluteInputSide();
    int outputLen = inc.getConvolutedOutLen();
    output = inc.getConvolutedOutput();
    printf("input side convolution =  {\n\t");
    for (int index = 0; index < outputLen; index++) {
        printf("%0.02f, ", *output);
        output++;
    }
    printf("\n}\n");

    Convolution outc = Convolution(input, 5, impulse, 3);
    outc.convoluteOutputSide();
    outputLen = outc.getConvolutedOutLen();
    output = outc.getConvolutedOutput();
    printf("output side convolution =  {\n\t");
    for (int index = 0; index < outputLen; index++) {
        printf("%0.02f, ", *output);
        output++;
    }
    printf("\n}\n");
}

void testFourrierTransform()
{
    double reX[] = { 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0 };
    double imX[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double timeX[] = {32.0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0, 0,0, 0.0};

    FourrierTransform ft = FourrierTransform();
    ft.discreteTransform(timeX, 32);
    double* realCosines = ft.getRealConsinesX();
    double* imSines = ft.getImSinesX();
    int freqDomainLen = ft.getFreqDomainLen();
    printf("Fourrier transform =  Real{\n\t");
    for (int index = 0; index < freqDomainLen; index++) {
        printf("%0.02f, ", *realCosines);
        realCosines++;
    }
    printf("\n}\n");
    printf("                   =  Im{\n\t");
    for (int index = 0; index < freqDomainLen; index++) {
        printf("%0.02f, ", *imSines);
        imSines++;
    }
    printf("\n}\n");

    FourrierTransform ift = FourrierTransform();
    ift.inverseTransform(reX, 17, imX, 17);
    double *x = ift.getTimeDomainX();
    int xLen = ift.getTimeDomainXLen();
    printf("inverse transform =  {\n\t");
    for (int index = 0; index < xLen; index++) {
        printf("%0.02f, ", *x);
        x++;
    }
    printf("\n}\n");
}


int main()
{
    testConvolution();
    testFourrierTransform();
    testLecture4Example();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
