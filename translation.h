#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>
#include <QSet>
#include <QXmlStreamReader>

/*
 *  翻译类 ， 主要作用：（其实最好这里来个多态，以后方便创建
 *  GoogleTranslate、BaiduTranslate、YoudaoTranslate、... ）
 *    构造翻译网址
 *    解析返回数据
 *    将翻译结果构造成文本
**/

class Translation
{
public:
    Translation();
    // data是从网页返回的数据，parse负责从中解析出自身
    void parse(QByteArray const& data);
    // 从外部设置&读取请求源、请求类型，添加翻译结果
    void setOrigin(QString const& origin);
    void setType(QString const& type);
    void addResult(QString const& result);
    QString const& getType() const;
    QString const& getOrigin() const;
    QSet<QString> const& getResult() const;
    // 构造结果文本
    QString buildResultBlock() const;
    // 自检
    bool isValueComplete() const;
    // 构造翻译请求网址
    static QString buildTranslateUrl(QString const& origin);
private:
    void readOrigin();
    void readType();
    void readResult();
private:
    QString m_type;
    QString m_origin;
    QSet<QString> m_result;
    QXmlStreamReader m_reader;
};

#endif // TRANSLATION_H
