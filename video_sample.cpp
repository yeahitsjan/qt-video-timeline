#include "video_sample.h"

VideoSample::VideoSample(int _duration, QColor _color) 
            : duration(_duration), color(_color){
    defColor = color;
    startPos = 0;
    endPos = duration;
}