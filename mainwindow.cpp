#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "translation.h"
#include "dbconnection.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), isQuery(false)
{
    ui->setupUi(this);
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
    if ( words.isEmpty() || isQuery ) {
        return ;
    }
    isQuery = true;
    ui->pushButton->setText (trUtf8 ("查询中...") );
    QUrl url ( Translation::buildTranslateUrl ( words ) );
    QNetworkReply *reply= networkAccessManager->get (QNetworkRequest(url) );

    QTimer *timer = new QTimer(this);
    connect (timer, SIGNAL(timeout()),
             reply, SLOT(deleteLater()) );
    connect (timer, SIGNAL(timeout()),
             timer, SLOT(deleteLater()) );
    connect (timer, SIGNAL(timeout()),
             this, SLOT(slot_timeout()));
    timer->start (3000);
    connect (networkAccessManager, SIGNAL(finished(QNetworkReply*)),
             timer, SLOT(stop()) );
}


void MainWindow::slot_queryDone(QNetworkReply *networkReply)
{
    if ( ! networkReply->isFinished ()) {
        useLocalTranslation();
    } else {
        ui->pushButton->setText (trUtf8 ("查询"));
        ui->textBrowser->clear ();
        Translation translation ;
        translation.setOrigin (ui->lineEdit->text ());
        translation.parse ( networkReply->readAll () );
        if ( translation.isValueComplete () ) {
            DBConnection& dbconnection = DBConnection::getInstance ();
            dbconnection.store(translation);
            ui->textBrowser->setText ( translation.buildResultBlock() );
        } else {
            useLocalTranslation ();
        }
    }
    isQuery = false;
}

void MainWindow::slot_timeout ()
{
    useLocalTranslation();
    isQuery = false;
}

void MainWindow::useLocalTranslation ()
{
    ui->textBrowser->setText (trUtf8 ("联网查询失败，尝试使用本地数据！\n"));
    Translation translation;
    translation.setOrigin (ui->lineEdit->text ());
    if ( !DBConnection::getInstance ().retract (translation) ) {
        ui->textBrowser->append (trUtf8("糟糕, 本地数据也不存在 %0 !").arg (
                                     translation.getOrigin ()));
    }

    ui->textBrowser->append ( translation.buildResultBlock () );
    ui->pushButton->setText (trUtf8 ("查询"));
}
