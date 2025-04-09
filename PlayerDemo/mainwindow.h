#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "IJZTJPlayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QWidget
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

public:
    void videoDataCallback(int w, int h, int yStride, int uStride, int vStride,
                           uint8_t *yData, uint8_t *uData, uint8_t *vData);

signals:
    void updateImage(int w, int h, int yStride, int uStride, int vStride,
                     const QByteArray &yData, const QByteArray &uData, const QByteArray &vData);

private slots:
    void on_pushButton_clicked();
    void onUpdateImage(int w, int h, int yStride, int uStride, int vStride,
                       const QByteArray &yData, const QByteArray &uData, const QByteArray &vData);


private:
    Ui::Mainwindow *ui;

    IJZTJPlayer *m_player{nullptr};
};
#endif // MAINWINDOW_H
