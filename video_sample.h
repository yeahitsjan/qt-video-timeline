#pragma once
#include <QColor>

class VideoSample {
public:
    VideoSample(int _duration, QColor _color);

    int duration;
    QColor color;
    QColor defColor;
    int startPos;
    int endPos;
    // picture
};
