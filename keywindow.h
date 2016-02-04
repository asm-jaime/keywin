#ifndef MYWINDOW
#define MYWINDOW

#include <QMainWindow>
#include "keywidget.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    qint8 mode;

private:
       keyw *key;

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void keyEvent(QKeyEvent *event);
    void keyRecord(QKeyEvent *event);
    void keyClear();
    void numClear();
    void keyStartStat();
    void changeMode(qint8 &mode);

private slots:
    void setMode(qint8 mode);
    void set_count_error(int num_error);
    void on_close_program_clicked();
    void on_record_button_clicked(bool checked);
    void on_start_button_clicked(bool checked);

};

#endif // MYWINDOW

