#ifndef SCREEN_H  // Header guard to prevent multiple inclusions
#define SCREEN_H

#include "Point.h"  // Include Point class for size and position representation
#include "Sprites.h"  // Include Sprites class for handling sprite objects

// Screen class declaration (abstract base class)
class Screen
{
    public:
        // Pure virtual method to check if the screen is enabled
        virtual bool IsEnable() = 0;

        // Pure virtual method to set the enabled state of the screen
        virtual void setEnabled(bool e) = 0;

        // Pure virtual method to get the index of the clicked button
        virtual int getButtonPresed() = 0;

        // Pure virtual method to render the screen
        virtual void Render() = 0;

        // Pure virtual method to get the size of the screen
        virtual Point getSize() = 0;

        // Virtual destructor to ensure proper cleanup in derived classes
        virtual ~Screen() {}
};

#endif // SCREEN_H  // End of header guard
