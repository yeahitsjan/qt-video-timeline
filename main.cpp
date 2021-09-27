#include <QApplication>

#include <QMainWindow>
#include "timeline.h"
#include "video_sample.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    VideoSample *smpl1 = new VideoSample(100, Qt::darkYellow);
    Timeline *timeline = new Timeline(360, 6, nullptr);
    timeline->addSample(smpl1);
    QMainWindow win;
    win.setCentralWidget(timeline);
    win.show();

    return app.exec();
}
