#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <QObject>
#include <QVector>
#include <QThreadPool>
#include <QMutex>
#include <QMutexLocker>
#include <functional>
//Qt Creator 需要在xxx.pro 内部增加静态库的链接声明
//LIBS += -L$$PWD -lgolib-impl

void EventCancel();
struct Name{
	std::string Space;
	std::string Local;
};
struct TranslationInfo{
	Name XMLName;
	std::string DictcnSpeach;
	std::string TransType;
	std::string Content;
};
struct QueryWords_Resp{
	bool Skipped;
	std::string ErrMsg;
	TranslationInfo Info;
};
QueryWords_Resp QueryWords(std::string in0);

// Qt
class RunOnUiThread : public QObject
{
    Q_OBJECT
public:
    explicit RunOnUiThread(QObject *parent = nullptr);
    virtual ~RunOnUiThread();

    void AddRunFnOn_OtherThread(std::function<void()> fn);
    // !!!注意,fn可能被调用,也可能由于RunOnUiThread被析构不被调用
    // 依赖于在fn里delete回收内存, 关闭文件等操作可能造成内存泄露
    void AddRunFnOn_UiThread(std::function<void ()> fn);
signals:
    void signal_newFn();
private slots:
    void slot_newFn();
private:
    bool m_done;
    QVector<std::function<void()>> m_funcList;
    QMutex m_Mutex;
    QThreadPool m_pool;
};
