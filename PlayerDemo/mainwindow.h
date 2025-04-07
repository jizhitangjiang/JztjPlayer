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

private slots:
    void on_pushButton_clicked();

private:
    Ui::Mainwindow *ui;

    IJZTJPlayer *m_player{nullptr};
};
#endif // MAINWINDOW_H
