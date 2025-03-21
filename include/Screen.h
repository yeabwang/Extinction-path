#ifndef SCREEN_H
#define SCREEN_H
#include "Point.h"
#include "Sprites.h"


class Screen
{
    public:
        virtual bool IsEnable()=0;/// checks if the screen is enabled or not
        virtual void setEnabled(bool e)=0;/// sets screens state
        virtual int getButtonPresed()=0;/// returns index of clicked button
        virtual void Render()=0;/// renders screen
        virtual Point getSize()=0;/// returns size of the screen
        virtual ~Screen()
        {
        }
};

#endif // SCREEN_H
