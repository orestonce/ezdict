#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QSqlDatabase>

class Translation;
// 单例模式封装所有数据库操作
//  主要用于储存和检索翻译数据
class DBConnection
{
    static DBConnection static_dbconnection;
    DBConnection();
public:
    static DBConnection& getInstance();
    // 初始化数据库，主要是创建所需数据表和开启外键。 注意！ 根据
    //  https://forum.qt.io/topic/38486/solved-qt-sql-database-driver-not-loaded-in-android
    // qt安卓程序在构造QApplication之前不能加载数据库驱动，所以不能将 init 函数合并进
    // DBConnection 的构造函数
    void init();
    // 将翻译结果储存到本地数据库中，返回储存结果
    bool store(Translation const& translation);
    // 读取本地数据库，返回读取结果
    bool retract(Translation& translation);
private:
    QSqlDatabase m_db;
};

#endif // DBCONNECTION_H
