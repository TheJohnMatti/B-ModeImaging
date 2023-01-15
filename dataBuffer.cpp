#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    // Initialize values if no parameter is entered
    numElement = 0;
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    // Initialize variables with inputs in override function
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;
    dataMatrix = createDataMatrix();
    loadRFData(dataMatrix, imagFile, realFile);
} 

dataBuffer::~dataBuffer()
{   
    // Call delete function
    deleteDataMatrix();
}

complex **dataBuffer::createDataMatrix()
{
    // Create 2D complex number array (each containing 2 floats)
    complex **dataMatrix;
    dataMatrix = new complex*[numElement];
    for (int i = 0; i < numElement; i++) {
        dataMatrix[i] = new complex[numSample];
    }
    return dataMatrix;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    // Define line to hold each line of files
    const int MAX_SIZE = 15;
    char line[MAX_SIZE];

    // Extract each line from response file into real and imag components of RFData matrix (numElement x numSample)
    for (int i = 0; i < numElement; i++) {
        for (int j = 0; j < numSample; j++) {
            imagFile->getline(line, MAX_SIZE);
            RFData[i][j].imag = atof(line);
            realFile->getline(line, MAX_SIZE);
            RFData[i][j].real = atof(line); 
        }    
    }
    return 0;

}

float dataBuffer::getRealRFData(int element,int sample)
{
    // Return real component
    return dataMatrix[element][sample].real;
}
float dataBuffer::getImagRFData(int element,int sample)
{
    // Return imag component
    return dataMatrix[element][sample].imag;
}
void dataBuffer::deleteDataMatrix()
{
    // Delete each sub-array in the data matrix
    for (int i = 0; i < numElement; i++) {
        delete dataMatrix[i];
    }
}




