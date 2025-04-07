#include "mainwindow.h"
#include "ui_mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mainwindow)
{
    ui->setupUi(this);

    m_player = createIJZTJPlayer();
}

Mainwindow::~Mainwindow()
{
    delete ui;
}


void Mainwindow::on_pushButton_clicked()
{
    m_player->openMediaFile("d:/video/video3.mp4");
}

