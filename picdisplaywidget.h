#ifndef PICDISPLAYWIDGET_H
#define PICDISPLAYWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QImage>


class PicDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PicDisplayWidget(QWidget *parent = nullptr);
    ~PicDisplayWidget();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void wheelEvent(QWheelEvent *event)override;
    void contextMenuEvent(QContextMenuEvent *event) override;

public slots:
       void onScaleUp();
       void onScaleDown();
       void onRotateRight();
       void onRotateLeft();
       void onLoadImage();
public:
       void onScaleUpAction();
       void onScaleDownAction();
       void onRotateRightAction();
       void onRotateLeftAction();
       void onLoadImageAction();

public:
    QMenu *m_pRClickMenu;
    QImage* m_pImageFrame;

    enum Action{
        None,
        LoadImageAction,
        ScaleUpAction,
        ScaleDownAction,
        RotateRightAction,
        RotateLeftAction,
    };

    Action m_CurrentAction;

    float m_ZoomValue;
    float m_RotateValue;

    QAction* m_pScaleUpAction;
    QAction* m_pScaleDownAction;
    QAction* m_pRotateRightAction;
    QAction* m_pRotateLeftAction;

    int m_XPtInterval;
    int m_YPtInterval;
    QPoint m_OldPos;
    bool m_Pressed = false;
};

#endif // PICDISPLAYWIDGET_H
