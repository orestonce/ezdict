#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class QNetworkAccessManager;
class QNetworkReply;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void slot_queryDone(QNetworkReply *networkReply);
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkAccessManager;
};

#endif // MAINWINDOW_H
