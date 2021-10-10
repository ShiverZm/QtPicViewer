#include "mypicviewwidget.h"
#include <QPainter>
#include <QLine>

MyPicViewWidget::MyPicViewWidget()
{
    QPainter painter(this);

    painter.setPen(Qt::red);
    painter.drawLine(0,50,50,50);
}
