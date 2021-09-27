#pragma once
#include <QWidget>
#include <QObject>

#include <QList>
#include <QPaintEvent>
#include <QEvent>
#include <QMouseEvent>

#include "video_sample.h"

class Timeline : public QWidget {
    Q_OBJECT
public:
    explicit Timeline(int _duration, int _length, QWidget *parent = nullptr);

    int duration;
    int length;
    QPoint pos;
    int pointerPos;
    int pointerTimePos;
    VideoSample *selectedSample;
    bool clicking;
    bool is_in;
    QList<VideoSample*> videoSamples;

    void addSample(VideoSample *smpl) {
        videoSamples.append(smpl);
    }

    float getScale() {
        int d = duration;
        int w = this->width();
        return d / w;
    }
    void checkSelect(int x);
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton)
                this->clicking = false;
    }
};
