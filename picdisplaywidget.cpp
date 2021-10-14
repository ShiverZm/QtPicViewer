#include "picdisplaywidget.h"

#include "dragwidget.h"

#include <QAction>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QWheelEvent>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QPushButton>

PicDisplayWidget::PicDisplayWidget(QWidget *parent) :
    QWidget(parent)
{
    m_pImageFrame = new QImage();

    m_CurrentAction = PicDisplayWidget::None;

    m_ZoomValue = 1.0f;
    m_RotateValue = 0;
    m_XPtInterval = 0;
    m_YPtInterval = 0;

    m_pScaleUpAction = new QAction();
    m_pScaleDownAction = new QAction();
    m_pRotateRightAction = new QAction();
    m_pRotateLeftAction = new QAction();

    m_pScaleUpAction->setText(tr("ScaleUp"));
    m_pScaleDownAction->setText(tr("ScaleDown"));
    m_pRotateRightAction->setText(tr("RotateRight"));
    m_pRotateLeftAction->setText(tr("RotateLeft"));

    connect(m_pScaleUpAction,&QAction::triggered,
        this, &PicDisplayWidget::onScaleUp);
    connect(m_pScaleDownAction,&QAction::triggered,
        this, &PicDisplayWidget::onScaleDown);
    connect(m_pRotateRightAction,&QAction::triggered,
        this, &PicDisplayWidget::onRotateRight);
    connect(m_pRotateLeftAction,&QAction::triggered,
        this, &PicDisplayWidget::onRotateLeft);


    m_pImageFrame = NULL;

//    QVBoxLayout *m_pVlayout = new QVBoxLayout();
//    QVBoxLayout *m_pVlayoutDragWidget = new QVBoxLayout();
//    DragWidget* m_dragWidget = new DragWidget();

//    QPushButton* m_pBtnScaleUp = new QPushButton();
//    QPushButton* m_pBtnScaleUp->setObjectName(QString::fromUtf8("m_pBtnScaleUp"));
//    QPushButton* m_pBtnScaleUp->setGeometry(QRect(11, 11, 90, 40));
//    QPushButton* m_pBtnScaleUp->setMinimumSize(QSize(0, 40));
//    QPushButton* m_pBtnScaleUp->setMaximumSize(QSize(16777215, 40));
//    QPushButton* m_pBtnScaleDown = new QPushButton();
//    QPushButton* m_pBtnScaleDown->setObjectName(QString::fromUtf8("m_pBtnScaleDown"));
//    m_pBtnScaleDown->setGeometry(QRect(108, 11, 89, 40));
//    m_pBtnScaleDown->setMinimumSize(QSize(0, 40));
//    m_pBtnScaleDown->setMaximumSize(QSize(16777215, 40));
//    m_pBtnRoateRight = new QPushButton(horizontalWidget);
//    m_pBtnRoateRight->setObjectName(QString::fromUtf8("m_pBtnRoateRight"));
//    m_pBtnRoateRight->setGeometry(QRect(204, 11, 89, 40));
//    m_pBtnRoateRight->setMinimumSize(QSize(0, 40));
//    m_pBtnRoateRight->setMaximumSize(QSize(16777215, 40));
//    m_pRotateLeft = new QPushButton(horizontalWidget);
//    m_pRotateLeft->setObjectName(QString::fromUtf8("m_pRotateLeft"));
//    m_pRotateLeft->setGeometry(QRect(300, 11, 89, 40));
//    m_pRotateLeft->setMinimumSize(QSize(0, 40));
//    m_pRotateLeft->setMaximumSize(QSize(16777215, 40));

//    m_dragWidget->setLayout(m_pVlayoutDragWidget);

//    m_pVlayout->addWidget(m_dragWidget);

//    this->setLayout(m_pVlayout);

}

PicDisplayWidget::~PicDisplayWidget()
{

}


void PicDisplayWidget::paintEvent(QPaintEvent *event)
{
    if(m_pImageFrame == NULL){
          return;
    }

    QPainter painter(this);

    if (m_pImageFrame->isNull()){
        return;
    }




    if(m_CurrentAction == PicDisplayWidget::LoadImageAction){
        onLoadImageAction();
    }else if(m_CurrentAction == PicDisplayWidget::ScaleUpAction){
        onScaleUpAction();
    }else if(m_CurrentAction == PicDisplayWidget::ScaleDownAction){
        onScaleDownAction();
    }else if(m_CurrentAction == PicDisplayWidget::RotateLeftAction){
        onRotateLeftAction();
    }else if(m_CurrentAction == PicDisplayWidget::RotateRightAction){
        onRotateRightAction();
    }

}

void PicDisplayWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu pMenuContext;
    pMenuContext.addAction(m_pScaleUpAction);
    pMenuContext.addAction(m_pScaleDownAction);
    pMenuContext.addAction(m_pRotateRightAction);
    pMenuContext.addAction(m_pRotateLeftAction);
    pMenuContext.exec(QCursor::pos());

}


void PicDisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_Pressed){
        return ;//QWidget::mouseMoveEvent(event);
    }

    this->setCursor(Qt::SizeAllCursor);
    QPoint pos = event->pos();
    int xPtInterval = pos.x() - m_OldPos.x();
    int yPtInterval = pos.y() - m_OldPos.y();

    m_XPtInterval += xPtInterval;
    m_YPtInterval += yPtInterval;

    m_OldPos = pos;
    this->update();
}

void PicDisplayWidget::mousePressEvent(QMouseEvent *event)
{
    m_OldPos = event->pos();
    m_Pressed = true;
}

void PicDisplayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_Pressed = false;
    this->setCursor(Qt::ArrowCursor);
}

void PicDisplayWidget::wheelEvent(QWheelEvent *event)
{
    int value = event->delta();
    if (value > 0){
        onScaleUp();
    }
    else{
        onScaleDown();
    }


}
void PicDisplayWidget::onScaleUp()
{
   // QImage show_frame = m_pImageFrame->scaled(640,720);

    //QMessageBox::information(NULL, "Tip", "onScaleUp",QMessageBox::Ok);

    m_CurrentAction = PicDisplayWidget::ScaleUpAction;

    m_ZoomValue += 0.2;

    this->update();
}

void PicDisplayWidget::onScaleDown()
{
//    QMessageBox::information(NULL, "Tip", "onScaleDown",QMessageBox::Ok);


    m_CurrentAction = PicDisplayWidget::ScaleDownAction;

     m_ZoomValue -= 0.2;
     if (m_ZoomValue <= 0)
     {
         m_ZoomValue += 0.2;
     }

     this->update();
}

void PicDisplayWidget::onRotateRight()
{
//    QMessageBox::information(NULL, "Tip", "onRotateRight",QMessageBox::Ok);

    m_CurrentAction = PicDisplayWidget::RotateRightAction;

    m_RotateValue +=45;

}

void PicDisplayWidget::onRotateLeft()
{
//    QMessageBox::information(NULL, "Tip", "onRotateLeft",QMessageBox::Ok);

    m_CurrentAction = PicDisplayWidget::RotateLeftAction;

    m_RotateValue -=45;

    update();
}


void PicDisplayWidget::onLoadImage()
{

    // 绘制样式

    QPainter painter( this);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), this->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, this->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());


    // 平移
    painter.translate(this->width() / 2 + m_XPtInterval, this->height() / 2 + m_YPtInterval);

    // 缩放
    painter.scale(m_ZoomValue, m_ZoomValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);
    this->update();

}

void PicDisplayWidget::onScaleUpAction()
{



    // 绘制样式

    QPainter painter( this);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), this->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, this->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());


    // 平移
    painter.translate(this->width() / 2 + m_XPtInterval, this->height() / 2 + m_YPtInterval);

    // 缩放
    painter.scale(m_ZoomValue, m_ZoomValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);
    this->update();
}

void PicDisplayWidget::onScaleDownAction()
{
    // 绘制样式
    QStyleOption opt;
    opt.init( this);
    QPainter painter( this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), this->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, this->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());

    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    // 平移
    painter.translate(this->width() / 2 + m_XPtInterval, this->height() / 2 + m_YPtInterval);

    // 缩放
    painter.scale(m_ZoomValue, m_ZoomValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);
    this->update();
}

void PicDisplayWidget::onRotateRightAction()
{
    // 绘制样式
    QStyleOption opt;
    opt.init( this);
    QPainter painter( this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), this->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, this->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());

    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    // 平移
    painter.translate(this->width() / 2 + m_XPtInterval, this->height() / 2 + m_YPtInterval);

    // 缩放
    //painter.scale(m_ZoomValue, m_ZoomValue);
    painter.rotate(m_RotateValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);
    this->update();
}

void PicDisplayWidget::onRotateLeftAction()
{
    // 绘制样式
    QStyleOption opt;
    opt.init( this);
    QPainter painter( this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), this->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, this->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());

    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    // 平移
    painter.translate(this->width() / 2 + m_XPtInterval, this->height() / 2 + m_YPtInterval);

    // 缩放
    //painter.scale(m_ZoomValue, m_ZoomValue);
    painter.rotate(m_RotateValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);

    this->update();
}

void PicDisplayWidget::onLoadImageAction()
{
    // 绘制样式

    QPainter painter(this);

    if (m_pImageFrame->isNull()){
        return;
    }

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(m_pImageFrame->width(), this->width());
    int height = width * 1.0 / (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());
    height = qMin(height, this->height());
    width = height * 1.0 * (m_pImageFrame->width() * 1.0 / m_pImageFrame->height());

    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    // 平移
    painter.translate(this->width() / 2 + m_XPtInterval, this->height() / 2 + m_YPtInterval);

    // 缩放
    //painter.scale(m_ZoomValue, m_ZoomValue);
    painter.rotate(m_RotateValue);

    // 绘制图像
    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, *m_pImageFrame);

    this->update();
}
