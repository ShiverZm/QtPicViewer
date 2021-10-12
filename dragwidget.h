#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPoint>

class DragWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);
    ~DragWidget(){};

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
signals:

public slots:

private:
    QPoint pressPoint;
};

#endif // DRAGWIDGET_H
