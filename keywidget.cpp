#include "keywidget.h"
#include <QDebug>


keyw::keyw(QLineEdit  *parent) : QLineEdit(parent)
{
    str = "";
    pl = 0;
    num_err = 0;
}

void keyw::keyEvent(QKeyEvent *event)
{

    switch(event->key())
    {
        case Qt::Key_Shift: return; break;
    }

    if(event->text()[0] == str[pl])
    {
        pl++;
        emit paintCurrentSymbol(pl);
    }
    else
    {
        num_err++;
        stack_err.push(event->text()[0]);
        emit set_count_error(num_err);
        qDebug()<<stack_err;
    }

    if(pl > str.size()-1)
    {
        pl = 0;
        emit setMode(0);
    }

}

void keyw::keyRecord(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Backspace)
    {
       str.remove(str.size()-1, 1);
       setText(str);
    }
    else
    {
        str.append(QString(event->text()));
        setText(str);
        qDebug()<<str;
    }
}

void keyw::keyClear()
{
    str.clear();
    setText(str);
    pl = 0;
}

void keyw::numClear()
{
    num_err = 0;
    pl = 0;
    stack_err.clear();
//    emit paintCurrentSymbol(pl);
}

void keyw::keyStartStat()
{
    pl = 0;
    stack_err.clear();
//    emit paintCurrentSymbol(pl);
}

void keyw::loadFromFile()
{

}

void keyw::loadFromError()
{

}
