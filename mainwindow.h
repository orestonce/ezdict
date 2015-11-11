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
    // 网络查询结束，可能查询失败
    void slot_queryDone(QNetworkReply *networkReply);
    // 网络查询超时
    void slot_timeout();
private:
    // 尝试使用本地数据库的内容对目标进行翻译
    void useLocalTranslation();
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkAccessManager;
    // 标记现在是否正在查询，若正在查询就不响应用户发送的查询请求
    //  （避免手抖）
    bool isQuery ;
};

#endif // MAINWINDOW_H
