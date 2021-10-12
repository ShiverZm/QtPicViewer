#ifndef MYPICVIEWWIDGET_H
#define MYPICVIEWWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>

class MyPicViewWidget : public QOpenGLWidget
{
public:
    explicit MyPicViewWidget(QWidget *parent = nullptr);
};

#endif // MYPICVIEWWIDGET_H
