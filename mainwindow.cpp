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
                                       tr("Image files (*.jpg)"));
    if (!fileName.isEmpty()){
        ui->m_pLEditPicPath->setText(fileName);

        //emit SendLoadImage();
    }
}

void MainWindow::onScaleUp()
{
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

//    QMessageBox::information(NULL, "Tip", "onLoadImage",
//                             QMessageBox::Ok);

    //QPainter painter(ui->m_pGLWPicShow);
    QPainter painter(ui->m_pGLWPicShow);


    //QPainter painter = ui->verticalWidget->getPainter();

//    painter.setPen(Qt::red);
//    painter.drawLine(0,50,50,50);

    QPixmap pix;
    pix.load(ui->m_pLEditPicPath->text());
    pix.size()

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
}


