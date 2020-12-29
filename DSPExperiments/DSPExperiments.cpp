// DSPExperiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Convolution.h"

int main()
{
    std::cout << "Hello World!\n";
    double input[] = { 0.0, -1.0, -1.25, 2.0, 1.5, 1.5, 0.75, 0, -0.75};
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
