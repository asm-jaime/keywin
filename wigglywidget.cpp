#include <QtWidgets>
#include "wigglywidget.h"

WigglyWidget::WigglyWidget(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);

    QFont newFont = font();
//    QFontMetrics metrics(font());

    newFont.setPointSize(newFont.pointSize() + 40);
    newFont.setBold(true);
    setFont(newFont);

    step = 0;
    timer.start(60, this);
    pc = 0;
    buf = 0;
}

void WigglyWidget::paintEvent(QPaintEvent * /* event */)
{
    static const int sineTable[16] = {
      0, 0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 0, 0
    };

    QFontMetrics metrics(font());
//    if(pc)
//    x = (width() - metrics.width(text)) / 2 - buf;
    x = 30 - buf;
    y = (height() + metrics.ascent() - metrics.descent()) / 2;

//    x = x - buf;
    QColor color;
    QPainter painter(this);

    for (int i = 0; i < text.size(); i++) {

        QFont newFont = font();
        int index = (step + i) % 16;
        if(i < pc)
        {
            color.setNamedColor("Gray");
        }
        else if(i > pc)
        {
            color.setNamedColor("Black");
        }
        else
        {
            if(w_mode == 1)
            {
                color.setHsv((15 - index) * 2, 255, 255);
                newFont.setPointSize(newFont.pointSize() - sineTable[index]);
            }
        }

        painter.setPen(color);
        painter.setFont(newFont);
        painter.drawText(x, y, QString(text[i]));
        x = x + metrics.width(text[i]);
    }

}

void WigglyWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        ++step;
        update();
    } else {
        QWidget::timerEvent(event);
    }
}

void WigglyWidget::paintCurrentSymbol(int p)
{
//
    pc = p;
    if(pc > 0)
    {
        QFontMetrics metrics(font());
        buf = buf + metrics.width(text[p-1]);
    }
//    qDebug()<<step;
//    QStringRef str_offset(&text, 0, pc);
//    qDebug()<<str_offset;
//    qDebug()<<width();
//
}

void WigglyWidget::changeMode(const qint8 &mode)
{
    w_mode = mode;
    switch(w_mode)
    {
    case 0 :
        pc = 0;
        buf = 0;
        update();
        timer.stop();
        break;
    case 1 :
        timer.start(60, this);
        break;
    case 2 :
        timer.start(60, this);
        break;
    default :
        break;
    }
}
