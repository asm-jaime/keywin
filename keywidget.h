#ifndef KEYWIDGET_H
#define KEYWIDGET_H

//#include <QWidget>
#include <QKeyEvent>
#include <QLineEdit>
#include <QStack>

class keyw : public QLineEdit
{
    Q_OBJECT

public:
    explicit keyw(QLineEdit *parent = 0);
    QStack<QChar> stack_err;
//    ~keyw();
    QString str;
    int num_err;
    int pl;

signals:
    void paintCurrentSymbol(int p);
    void set_count_error(int num_error);
    void setMode(qint8 mode);

private slots:
    void keyEvent(QKeyEvent *event);
    void keyRecord(QKeyEvent *event);
    void keyClear();
    void numClear();
    void keyStartStat();
    void loadFromFile();
    void loadFromError();
};

#endif // KEYWIDGET_H
