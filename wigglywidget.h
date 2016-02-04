#ifndef WIGGLYWIDGET_H
#define WIGGLYWIDGET_H

#include <QBasicTimer>
#include <QWidget>
#include <QDebug>

class WigglyWidget : public QWidget
{
    Q_OBJECT

public:
    WigglyWidget(QWidget *parent = 0);

public slots:
    void setText(const QString &newText) { text = newText; }
    void paintCurrentSymbol(int p);
    void changeMode(const qint8 &mode);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
//    void painter(QPainter *painter);

private:
    QBasicTimer timer;
    QString text;
    int step;
    int buf;
    int pc;
    int w_mode;
    int x;
    int y;
};

#endif
