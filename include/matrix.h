#ifndef MATRIX_H
#define MATRIX_H

#include "matrix.h"
// Interfaces with Everloop
#include "matrix_hal/everloop.h"
// Holds data for Everloop
#include "matrix_hal/everloop_image.h"
// Communicates with MATRIX device
#include "matrix_hal/matrixio_bus.h"

class matrix
{
    public:
        matrix();
        virtual ~matrix();
        void setLeds();

        auto bus;
        // Holds the number of LEDs on MATRIX device
        int ledCount;
        // Create EverloopImage object, with size of ledCount
        matrix_hal::EverloopImage everloop_image(ledCount);
        // Create Everloop object
        matrix_hal::Everloop everloop;

        // Set everloop to use MatrixIOBus bus
        everloop.Setup(&bus);
        // Keeps track of location of moving dots
        long counter;

    protected:

    private:

};

#endif // MATRIX_H
