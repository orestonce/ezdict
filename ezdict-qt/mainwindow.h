#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFuture>
#include <QThreadPool>
#include "golib.h"

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent=0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    RunOnUiThread m_syncUi;
};

#endif // MAINWINDOW_H
