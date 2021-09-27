#include "timeline.h"

#include <QPalette>
#include <QColor>

#include <QPainter>
#include <QPoint>
#include <QLine>
#include <QPolygon>
#include <QPen>
#include <QFont>

Timeline::Timeline(int _duration, int _length, QWidget *parent) : duration(_duration), length(_length), QWidget(parent) {
    QPalette pal;
    pal.setColor(QPalette::Background, QColor(60, 63, 65));
    pal.setColor(QPalette::Text, QColor(180, 180, 180));
    this->setPalette(pal);

    clicking = false;
    is_in = false;
    this->setGeometry(300, 300, this->length, 200);
    this->setMouseTracking(true);
    this->setAutoFillBackground(true);
}

void Timeline::paintEvent(QPaintEvent *event) {
    QPainter p;
    p.begin(this);
    p.setPen(QPen(QColor(180, 180, 180)));
    p.setFont(QFont("Arial", 10));
    p.setRenderHint(QPainter::Antialiasing);
    auto w = 0;
    auto scale = this->getScale();
    while (w <= this->width()) {
        p.drawText(w - 50, 0, 100, 100, Qt::AlignHCenter, "test time stamp");
        w += 100;
    }
    p.setPen(QPen(Qt::darkCyan, 5, Qt::SolidLine));
    p.drawLine(0, 40, this->width(), 40);

    auto point = 0;
    p.setPen(QPen(QColor(180, 180, 180)));
    p.drawLine(0, 40, this->width(), 40);
    while (point <= this->width()) {
        if (point % 30 != 0) {
            p.drawLine(3 * point, 40, 3 * point, 30);
        } else {
            p.drawLine(3 * point, 40, 3 * point, 20);
        }
        point += 10;
    }

    if (!pos.isNull() && is_in) {
        p.drawLine(this->pos.x(), 0, this->pos.x(), 40);
    }

    QLine line;
    QPolygon poly;
    if (!pointerPos == 0) {
        line = QLine(QPoint(this->pointerTimePos/this->getScale(), 40), QPoint(this->pointerTimePos/this->getScale(), this->height()));

        auto p1 = QPoint(this->pointerTimePos/this->getScale() - 10, 20);
        auto p2 = QPoint(this->pointerTimePos/this->getScale() + 10, 20);
        auto p3 = QPoint(this->pointerTimePos/this->getScale(), 40);
        poly.append(p1);
        poly.append(p2);
        poly.append(p3);
    } else {
        line = QLine(QPoint(0, 0), QPoint(0, this->height()));
        auto p1 = QPoint(-10, 20);
        auto p2 = QPoint(10, 20);
        auto p3 = QPoint(0, 40);
        poly.append(p1);
        poly.append(p2);
        poly.append(p3);
    }

    auto t = 0;
    foreach(VideoSample *_s, videoSamples) {
        QPainterPath path;
        path.addRoundedRect(QRectF(t / scale, 50, _s->duration / scale, 200), 10, 10);
        p.setClipPath(path);

        QPainterPath path2;
        p.setPen(QPen(_s->color));
        path2.addRoundedRect(QRectF(t / scale, 50, _s->duration / scale, 50), 10, 10);
        _s->startPos = t/scale;
        _s->endPos = t/scale + _s->duration/scale;
        p.fillPath(path2, _s->color);
        p.drawPath(path2);
    }

    QPainterPath clipPath;
    clipPath.addRect(this->rect().x(), this->rect().y(), this->rect().width(), this->rect().height());
    p.setClipPath(clipPath);

    p.setPen(Qt::darkCyan);
    p.setBrush(QBrush(Qt::darkCyan));

    p.drawPolygon(poly);
    p.drawLine(line);
    p.end();
}

void Timeline::checkSelect(int x) {
    foreach(VideoSample *_s, videoSamples) {
        if (_s->startPos < x < _s->endPos) {
            _s->color = Qt::darkCyan;
        } else {
            _s->color = _s->defColor;
        }
    }
}

void Timeline::enterEvent(QEvent *event) {
    is_in = true;
}

void Timeline::leaveEvent(QEvent *event) {
    is_in = false;
    this->update();
}

void Timeline::mouseMoveEvent(QMouseEvent *event) {
    this->pos = event->pos();

    if (this->clicking) {
        auto x = this->pos.x();
        this->pointerPos = x;
        this->pointerTimePos = this->pointerPos * this->getScale();
    }

    this->update();
}

void Timeline::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        auto x = event->pos().x();
        this->pointerPos = x;
        this->pointerTimePos = this->pointerPos * this->getScale();

        this->update();
        this->clicking = true;
    }
}
