#include "mainwindow.h"
#include "ui_mainwindow.h"

static void s_videoDataCallback(int w, int h, int yStride, int uStride, int vStride,
                              uint8_t *yData, uint8_t *uData, uint8_t *vData, void *obj)
{
    Mainwindow *window = static_cast<Mainwindow *>(obj);
    if (window) {
        window->videoDataCallback(w, h, yStride, uStride, vStride, yData, uData, vData);
    }
}

Mainwindow::Mainwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mainwindow)
{
    ui->setupUi(this);

    m_player = createIJZTJPlayer();
    connect(this, &Mainwindow::updateImage, this, &Mainwindow::onUpdateImage);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::videoDataCallback(int w, int h, int yStride, int uStride, int vStride, uint8_t *yData, uint8_t *uData, uint8_t *vData)
{
    QByteArray y((char*)yData, yStride*h);
    QByteArray u((char*)uData, uStride*h/2);
    QByteArray v((char*)vData, vStride*h/2);
    emit updateImage(w, h, yStride, uStride, vStride, y, u, v);
}

void Mainwindow::on_pushButton_clicked()
{
    m_player->setVideoYUVDataCallback(s_videoDataCallback, this);
    m_player->openMediaFile("d:/video/312095.mp4");
}

void Mainwindow::onUpdateImage(int w, int h, int yStride, int uStride, int vStride,
                               const QByteArray &yData, const QByteArray &uData, const QByteArray &vData)
{
    ui->widgetFrame->updateImage(w, h, yStride, uStride, vStride,
                                 (uchar*)yData.data(), (uchar*)uData.data(), (uchar*)vData.data());
}

