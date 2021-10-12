#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMenu>
#include <QImage>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void contextMenuEvent(QContextMenuEvent *event) override;

//自定义信号
signals:
       void SendLoadImage();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void wheelEvent(QWheelEvent *event)override;
public slots:
       void onSelectFile();
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
private:
    Ui::MainWindow *ui;
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

#endif // MAINWINDOW_H
