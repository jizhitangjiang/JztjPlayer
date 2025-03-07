#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QWidget
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

private:
    Ui::Mainwindow *ui;
};
#endif // MAINWINDOW_H
