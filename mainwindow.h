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
public slots:
       void onSelectFile();
       void onScaleUp();
       void onScaleDown();
       void onRotateRight();
       void onRotateLeft();
       void onLoadImage();
private:
    Ui::MainWindow *ui;
    QMenu *m_pRClickMenu;
    QImage* m_pImageFrame;
};

#endif // MAINWINDOW_H
