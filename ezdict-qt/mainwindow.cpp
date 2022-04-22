#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "golib.h"
#include <QMessageBox>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget *parent) :
    ui(new Ui::MainWindow), m_syncUi(parent)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    EventCancel();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setText("查询中...");

    std::string words = ui->lineEdit->text().toStdString();
    this->m_syncUi.AddRunFnOn_OtherThread([words, this](){
        QueryWords_Resp resp = QueryWords(words);
        this->m_syncUi.AddRunFnOn_UiThread([words, this, resp](){
            ui->pushButton->setText("查询");
            if (this->ui->lineEdit->text().toStdString() != words || resp.Skipped ) {
                return;
            }
            if (!resp.ErrMsg.empty()) {
                QMessageBox::warning(this, "查询错误", QString::fromStdString(resp.ErrMsg));
                return;
            }
            ui->textBrowser->setText (QString::fromStdString(resp.Info.Content));
        });
    });
}

