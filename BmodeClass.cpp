#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    // Initialize pointers to NULL and line to 0 if no parameters
    imparams = NULL;
    RFData = NULL; 
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    // Override with inputs for imparams, RFData, and line; assign scanline; perform beamform
    imparams = params;
    RFData = data;
    line = numline;
    scanline = createScanline(imparams->getNumPixel());
    beamform();
}

BmodeClass::~BmodeClass()
{
    // Release memory from scanline
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
    // Create scanline array
    float *mem;
    mem = new float[numPixel];
    return mem; 
}

void BmodeClass::beamform()
{
   // Define variables
   float time = 0;
   int s = 0;
   float pReal = 0;
   float pImag = 0;

   for (int i = 0; i < imparams->getNumPixel(); ++i){ // Loop through numPixel times
    pReal = 0; // Initialize real component to zero
    pImag = 0; // Initialize imag component to zero

    for (int j = 0; j < imparams->getNumElement(); ++j){ // Loop through numElement times
        
        // Calculate time
        time = (imparams->getYPosition(line, i) + 
        sqrt(pow(imparams->getYPosition(line, i), 2) + pow(imparams->getXPosition(line, i) - imparams->getElementPosition(j), 2)))/imparams->SOS;
        
        // Calculate s
        s = floor(time*imparams->FS);
        
        if (s < imparams->getNumSample()){  // Ensure there is no seg fault
        pReal += RFData->getRealRFData(j, s); // Summation for realRFData
        pImag += RFData->getImagRFData(j, s); // Summation for imagRFDAta
        }
        // Calculate ith scanline
        scanline[i] = sqrt(pow(pReal, 2) + pow(pImag, 2));
    }
   }

}

void BmodeClass::getScanline(float *data)
{
    // Copy array entries of scanline 1 by 1 into data array
    for (int i = 0; i < imparams->getNumPixel(); i++) {
        data[i] = scanline[i];
    }
}

void BmodeClass::deleteScanline()
{
    // Delete 1D scanline array
    delete scanline;
}