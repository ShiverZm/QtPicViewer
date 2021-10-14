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
signals:
    void SendLoadImage();
public slots:
       void onSelectFile();
private:
    Ui::MainWindow *ui;
    QImage* m_pImageFrame;
};

#endif // MAINWINDOW_H
