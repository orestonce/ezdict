#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <json/json.h>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    networkAccessManager = new QNetworkAccessManager(this);
    connect (networkAccessManager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(slot_queryDone(QNetworkReply*)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString words = ui->lineEdit->text ();
    if ( words.isEmpty() ) {
        std::clog << "empty" << std::endl;
        return ;
    }
    ui->pushButton->setText (trUtf8 ("查询中...") );
    QUrl url ("http://openapi.baidu.com/public/2.0/bmt/translate"
                            "?client_id=dAMINjtqHu18pomUYb5qPUMY"
                            "&from=en&to=zh&q="  + words );
    std::clog << qPrintable(url.toString ()) << std::endl;
    networkAccessManager->get (QNetworkRequest(url) );
}


void MainWindow::slot_queryDone(QNetworkReply *networkReply)
{
    if ( ! networkReply->isFinished ()) {
        ui->pushButton->setText (trUtf8 ("查询失败 !"));
        ui->textBrowser->setText (networkReply->errorString ());
    } else {
        ui->pushButton->setText (trUtf8 ("查询"));
        ui->textBrowser->clear ();

        try {
            std::string content = QString(networkReply->readAll ()).toStdString ();
            std::clog << content << std::endl;
            std::istringstream is( content );
            Json::Value root;

            is >> root;

            Json::Value trans_result(Json::arrayValue) ;
            trans_result = root["trans_result"];

            for ( Json::Value::iterator it =  trans_result.begin ();
                  it != trans_result.end () ; ++it ) {
                  ui->textBrowser->append (
                            trUtf8 ((*it)["dst"].asCString ()) + "\n");

            }
        } catch ( std::exception const& e) {
            ui->textBrowser->setText (e.what ());
        }
    }
}

/*
GET /search?q=think&keyfrom=dict.typo&le=eng&spc=go HTTP/1.1
Connection: Keep-Alive
Host: dict.youdao.com
*/
