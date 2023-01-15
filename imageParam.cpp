#include "imageParam.h"

imageParam::imageParam()
{
    // Initialize constants, as well as eleposition; generate scanlinePosition
    numElement = 128;
    numSample = 3338;
    numScanline = 127;
    elementPosition = genElementPosition();
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);
}

imageParam::~imageParam()
{
    // Call deletePositionArray to release data
    deletePositionArray();
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    // Define eleLocation float array
    float *eleLocation;
    eleLocation = new float[numElement];

    // Assign every element of eleLocation according to provided equation
    for (int i = 0; i < numElement; ++i){
        eleLocation[i] = (i-((float)numElement-1.0)/2.0)*PITCH;
    }

    // Return element position array
    return eleLocation;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    // Prompt and store depth and number of pixels
    std::cout << "Scanline depth: ";
    std::cin >> desiredDepth;
    std::cout << "Number of pixels: ";
    std::cin >> numPixel;

    // Create scanline position array
    float2 **scanlinePosition;
    scanlinePosition = new float2*[numScanline];
    
    // Populate numScanline x numPixel array
    for (int i = 0; i < numScanline; i++) {
        scanlinePosition[i] = new float2[numPixel];
        for (int j = 0; j < numPixel; j++) {
            
            // Set x-component according to scanline number
            scanlinePosition[i][j].x = (i - (((float)numScanline-1.0)/2.0))*PITCH;
            
            // Set y-component according to depth and pixels
            scanlinePosition[i][j].y = j*(desiredDepth/(numPixel-1));
        }
    }

    // Return populated position matrix
    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    // Return x position
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    // Return Y position
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
{
    // Return eleposition
    return elementPosition[element];
}

int imageParam::getNumElement()
{
    // Return constant
    return numElement;
}

int imageParam::getNumSample()
{
    // Return constant
    return numSample;
}

int imageParam::getNumScanline() 
{
    // Return constant
    return numScanline;
}

int imageParam::getNumPixel() 
{
    // Return user-defined variable
    return numPixel;
}

void imageParam::deletePositionArray()
{
    // Delete elementPosition array
    delete elementPosition;

    // Delete subarrays of 2D scanlinePosition array
    for (int i = 0; i < numScanline; i++)
        delete scanlinePosition[i];
}









