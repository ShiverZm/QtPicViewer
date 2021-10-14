#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QWheelEvent>
#include <QStyleOption>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    m_pImageFrame = new QImage();

    connect(this,&MainWindow::SendLoadImage,
        ui->m_pLabelPicShow, &PicDisplayWidget::onLoadImage);
    connect(ui->m_pBtnScaleUp,&QPushButton::clicked,
        ui->m_pLabelPicShow, &PicDisplayWidget::onScaleUp);
    connect(ui->m_pBtnScaleUp,&QPushButton::clicked,
        ui->m_pLabelPicShow, &PicDisplayWidget::onScaleUp);
    connect(ui->m_pBtnScaleDown,&QPushButton::clicked,
        ui->m_pLabelPicShow, &PicDisplayWidget::onScaleDown);
    connect(ui->m_pBtnRoateRight,&QPushButton::clicked,
        ui->m_pLabelPicShow, &PicDisplayWidget::onRotateRight);
    connect(ui->m_pRotateLeft,&QPushButton::clicked,
        ui->m_pLabelPicShow, &PicDisplayWidget::onRotateLeft);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onSelectFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                       tr("Open Image"), ".",
                                       tr("Image files (*.jpg | *.png)"));
    if (!fileName.isEmpty()){
        ui->m_pLEditPicPath->setText(fileName);


        if( m_pImageFrame->load(fileName))
        {
            ui->m_pLabelPicShow->m_pImageFrame = m_pImageFrame;
            ui->m_pLabelPicShow->m_CurrentAction = PicDisplayWidget::LoadImageAction;
            emit SendLoadImage();
        }
    }
}




