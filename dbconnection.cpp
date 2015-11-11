#include "dbconnection.h"
#include "translation.h"
#include <QFile>
#include <QSqlQuery>
#include <QVariant>

DBConnection DBConnection::static_dbconnection;

DBConnection::DBConnection()
{

}

void DBConnection::init()
{
    m_db = QSqlDatabase::addDatabase ("QSQLITE");
    m_db.setDatabaseName ("ezdict.db3");
    m_db.open () ;
    if ( !m_db.isOpen () ) {
        return;
    }
    // 翻译类型，目前支持中译英、英译中
    m_db.exec ("CREATE TABLE trans_type ("
               "t_type CHAR(32) NOT NULL PRIMARY KEY"
               ");");
    m_db.exec ("INSERT INTO trans_type VALUES('ec'),('ce');");
    // 翻译请求，每个请求有唯一 的id，
    //   当然请求类型和请求源数据组合起来也是不可重复的
    m_db.exec ("CREATE TABLE trans_request ("
               "r_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
               "r_type CHAR(32) NOT NULL REFERENCES trans_type( t_type ),"
               "r_origin TEXT NOT NULL COLLATE NOCASE,"
               "UNIQUE(r_type, r_origin)"
               ");");
    // 翻译结果，sqlite默认为utf8编码，所以就不用纠结编码的问题了
    m_db.exec ("CREATE TABLE trans_result ("
               "r_id REFERENCES trans_request(r_id) ,"
               "r_result TEXT,"
               "UNIQUE(r_id, r_result)"
               ") ;");
    // sqlite3 默认不启用外键，但是我们的业务需要是要启用外键滴
    m_db.exec ("PRAGMA foreign_keys=ON;");
}

DBConnection& DBConnection::getInstance ()
{
    return static_dbconnection;
}

bool DBConnection::store (const Translation &translation)
{
    // 需要确保翻译数据完整才往数据库里面放
    if ( !translation.isValueComplete() ) {
        return false;
    }
    QSqlQuery query(m_db);
    query.prepare ("INSERT INTO trans_request(r_type, r_origin) VALUES"
                   "( :r_type, :r_origin)"
                   );
    query.bindValue (":r_type", translation.getType() );
    query.bindValue (":r_origin", translation.getOrigin () );
    // 增加翻译请求失败，那说明已经有了该请求的记录
    //  所以就不用再写啦
    if ( !query.exec () ) {
        return false;
    }
    // 获取到刚才增加的请求的id
    quint64 id = query.lastInsertId ().toULongLong ();
    query.prepare ("INSERT INTO trans_result(r_id, r_result) "
                   "VALUES(:r_id, :r_result)");
    query.bindValue (":r_id", id);

    QString result ;
    // 逐条增加翻译结果
    foreach (result, translation.getResult () ) {
        query.bindValue (":r_result",result);
        query.exec ();
    }
    return true;
}

bool DBConnection::retract (Translation &translation)
{
    QSqlQuery query(m_db);
    // 只需取得一条数据，所以用LIMIT 1
    query.prepare ("SELECT r_id,r_type FROM trans_request WHERE "
                   "r_origin = :r_origin COLLATE NOCASE LIMIT 1");
    query.bindValue (":r_origin", translation.getOrigin () );
    query.exec ();
    // 可惜了了，以前并没有相同的请求
    if ( !query.next () ) {
        return false;
    }

    quint64 id = query.value (0).toULongLong ();
    translation.setType (query.value (1).toString ());
    query.prepare ("SELECT r_result FROM trans_result WHERE "
                   "r_id = :r_id ");
    query.bindValue (":r_id", id);
    query.exec ();
    // 逐条取得翻译结果
    while ( query.next () )
    {
        translation.addResult (query.value (0).toString ());
    }

    return !translation.getResult ().isEmpty ();
}
