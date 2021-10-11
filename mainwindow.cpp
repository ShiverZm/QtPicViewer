#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pImageFrame = new QImage();
    QObject::connect(this,&MainWindow::SendLoadImage,
        this, &MainWindow::onLoadImage);

    m_CurrentAction = MainWindow::None;

    m_ZoomValue = 1.0f;
    m_RotateValue = 0;


    m_pScaleUpAction = new QAction(this);
    m_pScaleDownAction = new QAction(this);
    m_pRotateRightAction = new QAction(this);
    m_pRotateLeftAction = new QAction(this);

    m_pScaleUpAction->setText(tr("ScaleUp"));
    m_pScaleDownAction->setText(tr("ScaleDown"));
    m_pRotateRightAction->setText(tr("RotateRight"));
    m_pRotateLeftAction->setText(tr("RotateLeft"));

    connect(m_pScaleUpAction,&QAction::triggered,
        this, &MainWindow::onScaleUp);
    connect(m_pScaleDownAction,&QAction::triggered,
        this, &MainWindow::onScaleDown);
    connect(m_pRotateRightAction,&QAction::triggered,
        this, &MainWindow::onRotateRight);
    connect(m_pRotateLeftAction,&QAction::triggered,
        this, &MainWindow::onRotateLeft);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu pMenuContext;
    pMenuContext.addAction(m_pScaleUpAction);
    pMenuContext.addAction(m_pScaleDownAction);
    pMenuContext.addAction(m_pRotateRightAction);
    pMenuContext.addAction(m_pRotateLeftAction);
    pMenuContext.exec(QCursor::pos());


}

void MainWindow::paintEvent(QPaintEvent *event)
{

    if(ui->m_pLEditPicPath->text().isEmpty()){
      return;
    }

    if(m_CurrentAction == MainWindow::LoadImageAction){
        //onLoadImageAction();

    }else if(m_CurrentAction == MainWindow::ScaleUpAction){
        onScaleUpAction();
    }else if(m_CurrentAction == MainWindow::ScaleDownAction){
        onScaleDownAction();
    }else if(m_CurrentAction == MainWindow::RotateLeftAction){
        onRotateLeftAction();
    }else if(m_CurrentAction == MainWindow::RotateRightAction){
        onRotateRightAction();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    int value = event->delta();
    if (value > 0){
        onScaleUp();
    }
    else{
        onScaleDown();
    }

    ui->m_pLabelPicShow->update();
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


            //emit SendLoadImage();
            m_CurrentAction = MainWindow::LoadImageAction;
        }
    }
}

void MainWindow::onScaleUp()
{
   // QImage show_frame = m_pImageFrame->scaled(640,720);

    QMessageBox::information(NULL, "Tip", "onScaleUp",
                             QMessageBox::Ok);

    m_CurrentAction = MainWindow::ScaleUpAction;

    m_ZoomValue += 0.2;
}

void MainWindow::onScaleDown()
{
    QMessageBox::information(NULL, "Tip", "onScaleDown",
                             QMessageBox::Ok);

    m_CurrentAction = MainWindow::ScaleDownAction;

     m_ZoomValue -= 0.2;
     if (m_ZoomValue <= 0)
     {
         m_ZoomValue += 0.2;
         return;
     }
}

void MainWindow::onRotateRight()
{
    QMessageBox::information(NULL, "Tip", "onRotateRight",
                             QMessageBox::Ok);

    m_CurrentAction = MainWindow::RotateRightAction;

    m_RotateValue +=45;

}

void MainWindow::onRotateLeft()
{
    QMessageBox::information(NULL, "Tip", "onRotateLeft",
                             QMessageBox::Ok);

    m_CurrentAction = MainWindow::RotateLeftAction;

    m_RotateValue -=45;
}


void MainWindow::onLoadImage()
{

////////////////////////////////////适应显示原图片1////////////////////////////////////////////
//        QImage showFrame = m_pImageFrame->scaled(ui->m_pLabelPicShow->size(), Qt::KeepAspectRatio);
//        //ui->m_pLabelPicShow->setScaledContents(true);
//        QPixmap pix = QPixmap::fromImage(showFrame);
//        ui->m_pLabelPicShow->setPixmap(pix);
//        ui->m_pLabelPicShow->update();
///////////////////////////////控件显示原图片2//////////////////////////
//    int nWidgetWidth  = ui->m_pLabelPicShow->width();
//    int nWidgetHeight = ui->m_pLabelPicShow->height();

//    int nShowHeight = 0;
//    int nShowWidth = 0;

//    float nWHRate = 1;
//    if(m_pImageFrame->height() > 0){
//       nWHRate = ((float)m_pImageFrame->width() / (float)m_pImageFrame->height());
//    }

//    if(m_pImageFrame->height() > nWidgetHeight || m_pImageFrame->width() > nWidgetWidth){
//        nShowHeight = nWidgetHeight;
//        nShowWidth =  nWHRate * nWidgetHeight;
//    }
//    QImage showFrame = m_pImageFrame->scaled(nShowWidth,nShowHeight);

//    QPixmap pix = QPixmap::fromImage(showFrame);


//    ui->m_pLabelPicShow->setPixmap(pix);

//    ui->m_pLabelPicShow->update();





/////////////////////////平移示例///////////////////

//    QPainter painter(ui->m_pLabelPicShow);
//    QImage show_frame = m_pImageFrame->scaled(100,100);

//    painter.translate(100,100); //将（100，100）设为坐标原点

//    QRect rect(0,0,100,100);

//    painter.drawImage(rect,show_frame);

/////////////////////////image crop示例///////////////////

//      QPainter painter(ui->m_pLabelPicShow);
//      QRect rect(0,100,200,200);
////      QRect cropRect(0,0,270,270);
////      painter.setClipRect(cropRect,Qt::ReplaceClip);

//      QImage show_frame = m_pImageFrame->copy(0,0,300,250);
//      painter.drawImage(rect,show_frame);
//      ui->m_pLabelPicShow->update();

/////////////////////////rotate示例///////////////////
  /*
    QPainter painter(ui->m_pLabelPicShow);
    QImage show_frame = m_pImageFrame->scaled(100,100);
    QRect rect(0,100,200,200);
    painter.rotate(-15);
    painter.drawImage(rect,show_frame);
    */
/////////////////////////scale示例///////////////////
    /*
     QPainter painter(ui->m_pLabelPicShow);
    QImage show_frame = m_pImageFrame->scaled(640,720);
    QPixmap pix = QPixmap::fromImage(show_frame);

    painter.drawPixmap(0,0,640,720,pix);
    */
/////////////////////////////////////////下面是自创的////////////////////////////


//    QMessageBox::information(NULL, "Tip", "onLoadImage",
//                             QMessageBox::Ok);

    //QPainter painter(ui->m_pGLWPicShow);
    QPainter painter(ui->m_pLabelPicShow);


    //QPainter painter = ui->verticalWidget->getPainter();

//    painter.setPen(Qt::red);
//    painter.drawLine(0,50,50,50);

    QPixmap pix;
    pix.load(ui->m_pLEditPicPath->text());

    int nWidgetWidth = ui->m_pLabelPicShow->width();
    int nWidgetHeight =ui->m_pLabelPicShow->height();

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

void MainWindow::onScaleUpAction()
{

//    QPainter painter(ui->m_pLabelPicShow);
//    QRect rect(0,100,200,200);
//    QImage showFrame = m_pImageFrame->copy(0,0,300,250);

//    painter.drawImage(rect,showFrame);
//    ui->m_pLabelPicShow->setPixmap(QPixmap::fromImage(showFrame));
//    ui->m_pLabelPicShow->update();


    // 绘制样式
    QStyleOption opt;
    opt.init( ui->m_pLabelPicShow);
    QPainter painter( ui->m_pLabelPicShow);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, ui->m_pLabelPicShow);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), ui->m_pLabelPicShow->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, ui->m_pLabelPicShow->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());

    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    // 平移
    painter.translate(ui->m_pLabelPicShow->width() / 2 + m_XPtInterval, ui->m_pLabelPicShow->height() / 2 + m_YPtInterval);

    // 缩放
    painter.scale(m_ZoomValue, m_ZoomValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);
}

void MainWindow::onScaleDownAction()
{
    // 绘制样式
    QStyleOption opt;
    opt.init( ui->m_pLabelPicShow);
    QPainter painter( ui->m_pLabelPicShow);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, ui->m_pLabelPicShow);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), ui->m_pLabelPicShow->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, ui->m_pLabelPicShow->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());

    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    // 平移
    painter.translate(ui->m_pLabelPicShow->width() / 2 + m_XPtInterval, ui->m_pLabelPicShow->height() / 2 + m_YPtInterval);

    // 缩放
    painter.scale(m_ZoomValue, m_ZoomValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);
}

void MainWindow::onRotateRightAction()
{
    // 绘制样式
    QStyleOption opt;
    opt.init( ui->m_pLabelPicShow);
    QPainter painter( ui->m_pLabelPicShow);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, ui->m_pLabelPicShow);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), ui->m_pLabelPicShow->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, ui->m_pLabelPicShow->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());

    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    // 平移
    painter.translate(ui->m_pLabelPicShow->width() / 2 + m_XPtInterval, ui->m_pLabelPicShow->height() / 2 + m_YPtInterval);

    // 缩放
    //painter.scale(m_ZoomValue, m_ZoomValue);
    painter.rotate(m_RotateValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);
}

void MainWindow::onRotateLeftAction()
{
    // 绘制样式
    QStyleOption opt;
    opt.init( ui->m_pLabelPicShow);
    QPainter painter( ui->m_pLabelPicShow);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, ui->m_pLabelPicShow);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), ui->m_pLabelPicShow->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, ui->m_pLabelPicShow->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());

    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    // 平移
    painter.translate(ui->m_pLabelPicShow->width() / 2 + m_XPtInterval, ui->m_pLabelPicShow->height() / 2 + m_YPtInterval);

    // 缩放
    //painter.scale(m_ZoomValue, m_ZoomValue);
    painter.rotate(m_RotateValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);
}

void MainWindow::onLoadImageAction()
{
    QPainter painter(ui->m_pLabelPicShow);
    QPixmap pix = QPixmap::fromImage(*m_pImageFrame);

    int nWidgetWidth = ui->m_pLabelPicShow->width();
    int nWidgetHeight =ui->m_pLabelPicShow->height();

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


