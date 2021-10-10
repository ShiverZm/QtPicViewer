#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pImageFrame = new QImage();
//    QObject::connect(this,&MainWindow::SendLoadImage,
//        this, &MainWindow::onLoadImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu pMenuContext;
    QAction* pScaleUpAction = new QAction(this);
    QAction* pScaleDownAction = new QAction(this);
    QAction* pRotateRightAction = new QAction(this);
    QAction* pRotateLeftAction = new QAction(this);

    pScaleUpAction->setText(tr("ScaleUp"));
    pScaleDownAction->setText(tr("ScaleDown"));
    pRotateRightAction->setText(tr("RotateRight"));
    pRotateLeftAction->setText(tr("RotateLeft"));

    pMenuContext.addAction(pScaleUpAction);
    pMenuContext.addAction(pScaleDownAction);
    pMenuContext.addAction(pRotateRightAction);
    pMenuContext.addAction(pRotateLeftAction);
    pMenuContext.exec(QCursor::pos());
}

void MainWindow::paintEvent(QPaintEvent *event)
{
   onLoadImage();
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
//            int width = m_pImageFrame->width();
//            int height = m_pImageFrame->height();
//            QString str = "width";
//            str.append(":");
//            str.append(QString::number(width));
//            str.append(",");
//            str.append("height:");
//            str.append(QString::number(height));
//            QMessageBox::information(NULL, "Tip", str,
//                                     QMessageBox::Ok);
        }
    }
}

void MainWindow::onScaleUp()
{
   // QImage show_frame = m_pImageFrame->scaled(640,720);

    QMessageBox::information(NULL, "Tip", "onScaleUp",
                             QMessageBox::Ok);
}

void MainWindow::onScaleDown()
{
    QMessageBox::information(NULL, "Tip", "onScaleDown",
                             QMessageBox::Ok);
}

void MainWindow::onRotateRight()
{
    QMessageBox::information(NULL, "Tip", "onRotateRight",
                             QMessageBox::Ok);
}

void MainWindow::onRotateLeft()
{
    QMessageBox::information(NULL, "Tip", "onRotateLeft",
                             QMessageBox::Ok);
}

void MainWindow::onLoadImage()
{
    if(ui->m_pLEditPicPath->text().isEmpty()){
      return;
    }

/////////////////////////平移示例///////////////////

    QPainter painter(ui->m_pGLWPicShow);
    QImage show_frame = m_pImageFrame->scaled(100,100);

    painter.translate(100,100); //将（100，100）设为坐标原点

    QRect rect(0,0,100,100);

    painter.drawImage(rect,show_frame);

/////////////////////////image crop示例///////////////////
/*
      QPainter painter(ui->m_pGLWPicShow);
      QRect rect(0,100,200,200);
//      QRect cropRect(0,0,270,270);
//      painter.setClipRect(cropRect,Qt::ReplaceClip);

      QImage show_frame = m_pImageFrame->copy(0,0,300,250);
      painter.drawImage(rect,show_frame);
*/
/////////////////////////rotate示例///////////////////
  /*
    QPainter painter(ui->m_pGLWPicShow);
    QImage show_frame = m_pImageFrame->scaled(100,100);
    QRect rect(0,100,200,200);
    painter.rotate(-15);
    painter.drawImage(rect,show_frame);
    */
/////////////////////////scale示例///////////////////
    /*
     QPainter painter(ui->m_pGLWPicShow);
    QImage show_frame = m_pImageFrame->scaled(640,720);
    QPixmap pix = QPixmap::fromImage(show_frame);

    painter.drawPixmap(0,0,640,720,pix);
    */
/////////////////////////////////////////下面是自创的////////////////////////////

    /*
//    QMessageBox::information(NULL, "Tip", "onLoadImage",
//                             QMessageBox::Ok);

    //QPainter painter(ui->m_pGLWPicShow);
    QPainter painter(ui->m_pGLWPicShow);


    //QPainter painter = ui->verticalWidget->getPainter();

//    painter.setPen(Qt::red);
//    painter.drawLine(0,50,50,50);

    QPixmap pix;
    pix.load(ui->m_pLEditPicPath->text());

    int nWidgetWidth = ui->m_pGLWPicShow->width();
    int nWidgetHeight =ui->m_pGLWPicShow->height();

    int nShowHeight = 0;
    int nShowWidth = 0;

    float nWHRate = 1;
    if(pix.height() > 0){
       nWHRate = ((float)pix.width() / (float)pix.height());
    }

    if(pix.height() > nWidgetHeight || pix.width() > nWidgetWidth){
        nShowHeight = nWidgetHeight;
        nShowWidth =  nWHRate * nWidgetHeight;
    }


    int posX = nWidgetWidth / 2 - nShowWidth/2;
    int posY = 0;

    painter.drawPixmap(posX,posY,nShowWidth,nShowHeight,pix);
    //ui->m_pGLWPicShow->update();

    */
}


