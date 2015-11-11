#include "translation.h"
#include <QIODevice>
#include <QSharedPointer>

Translation::Translation()
{

}

void Translation::parse (const QByteArray &data)
{
    m_reader.clear ();
    m_reader.addData (data);
    m_reader.readNext ();

    while ( !m_reader.atEnd () && !m_reader.hasError () )
    {
        if ( m_reader.isStartElement () ) {
            QString name = m_reader.name ().toString ();

            if ( name == "dictcn-speach" ) {
                readOrigin();
            } else if ( name == "type" ) {
                readType();
            } else if ( name == "content" ) {
                readResult();
            }
        }
        m_reader.readNext ();
    }
}

void Translation::readOrigin ()
{
    m_reader.readNext ();
    if ( m_reader.isCharacters () ) {
        m_origin = m_reader.text ().toString ();
    }
}

void Translation::readType ()
{
    m_reader.readNext ();
    if ( m_reader.isCharacters () ) {
        m_type = m_reader.text ().toString ();
    }
}

void Translation::readResult ()
{
    m_reader.readNext ();
    if ( m_reader.isCharacters () ) {
        m_result.insert ( m_reader.text ().toString () );
    }
}

bool Translation::isValueComplete () const
{
    return !m_type.isEmpty () && !m_origin.isEmpty () && !m_result.isEmpty ();
}

QString Translation::buildTranslateUrl (const QString &origin)
{
    return QString("http://fanyi.youdao.com/fsearch?q=" + origin );
}

QString const& Translation::getType () const
{
    return m_type;
}

QString const& Translation::getOrigin() const
{
    return m_origin;
}

QSet<QString> const& Translation::getResult() const
{
    return m_result;
}

QString Translation::buildResultBlock () const
{
    QString results ;
    QString result ;

    foreach (result, m_result) {
        if ( !results.isEmpty () ) {
            results += "\n";
            results += result ;
        } else {
            results = result;
        }
    }
    return results;
}

void Translation::setOrigin (const QString &origin)
{
    m_origin = origin;
}

void Translation::setType (const QString &type)
{
    m_type = type;
}

void Translation::addResult(const QString& result)
{
    m_result.insert (result);
}
