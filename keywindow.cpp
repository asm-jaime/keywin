#include "keywindow.h"
#include "wigglywidget.h"
#include "ui_keywindow.h"
#include <QDebug>
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
//#include <QGraphicsEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /** *add icon */
    ui->record_button->setIcon(QIcon(":/images/images/media_record.png"));
    ui->start_button->setIcon(QIcon(":/images/images/play-normal-red.png"));

    /** * keystring! */
    key = new keyw;

    /** * wiggly widget */
    WigglyWidget *wigglyWidget = new WigglyWidget(this);
    ui->gridForWiggly->addWidget(wigglyWidget);
    QGraphicsDropShadowEffect* effect	= new QGraphicsDropShadowEffect(this);
    //    QGEffect->
    wigglyWidget->setGraphicsEffect(effect);
    wigglyWidget->setFocus();

    /** * Menu */
    QMenu *file = menuBar()->addMenu("File");
    QMenu *load_str = menuBar()->addMenu("Load");
    QAction *load_str_file = new QAction(tr("Load file"), this);
    QAction *load_str_err = new QAction(tr("Load err"), this);

    /** * Connect */
    connect(key, &keyw::textChanged, wigglyWidget, &WigglyWidget::setText);
    connect(this,&MainWindow::changeMode, wigglyWidget,&WigglyWidget::changeMode);
    connect(key,SIGNAL(paintCurrentSymbol(int)), wigglyWidget, SLOT(paintCurrentSymbol(int)));

    connect(this,SIGNAL(keyEvent(QKeyEvent*)),key,SLOT(keyEvent(QKeyEvent*)));
    connect(this,SIGNAL(keyRecord(QKeyEvent*)),key,SLOT(keyRecord(QKeyEvent*)));
//    connect(newFile,SIGNAL(triggered()),this, SLOT(action()));
//    connect(Open,SIGNAL(triggered()),this, SLOT(action()));
    connect(this,SIGNAL(keyClear()),key,SLOT(keyClear()));
    connect(key,SIGNAL(set_count_error(int)),this,SLOT(set_count_error(int)));
    connect(this, SIGNAL(numClear()), key, SLOT(numClear()));
    connect(this, SIGNAL(keyStartStat()), key, SLOT(keyStartStat()));
//    connect(key,SIGNAL(),ui->number_error, SLOT(display(int));

    connect(key, SIGNAL(setMode(qint8)), this, SLOT(setMode(qint8)));
    connect(load_str_file, SIGNAL(triggered()), key, SLOT(loadFromFile()));
    connect(load_str_err, SIGNAL(triggered()), key, SLOT(loadFromError()));
//    newFile->setShortcut(tr("Ctrl+F"));
//    Open->setShortcut(tr("Ctrl+N"));

    load_str->addAction(load_str_file);
    load_str->addAction(load_str_err);

    key->setText("mamku ebal");
    key->str = "mamku ebal";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(this->mode)
    {
    case 0 : break;
    case 1 : emit keyEvent(event); break;
    case 2 : emit keyRecord(event); break;
    }
}

void MainWindow::on_close_program_clicked()
{
   close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_button_clicked(bool checked)
{
    if(checked)
    {
        this->setMode(1);
    }
    else
    {
        this->setMode(0);
    }
}

void MainWindow::on_record_button_clicked(bool checked)
{
    if(checked)
    {
        this->setMode(2);
    }
    else
    {
        this->setMode(0);
    }
}

void MainWindow::set_count_error(int num_error)
{
    ui->number_error->display(num_error);
}

void MainWindow::setMode(qint8 mode)
{
    switch (mode) {
    case 0 :

        switch(this->mode)
        {
        case 1 :
            ui->start_button->setChecked(false);
            ui->start_button->setIcon(QIcon(":/images/images/play-normal-red.png"));
            break;
        case 2 :
            ui->record_button->setChecked(false);
            ui->record_button->setIcon(QIcon(":/images/images/media_record.png"));
            break;
        case 3 :

            break;
        default:
            break;
        }
        this->mode = 0;
        emit changeMode(this->mode);
        emit keyStartStat();

        break;
    case 1 :

        if(!this->key->str.size())
        {
            ui->start_button->setChecked(false);
            ui->start_button->setIcon(QIcon(":/images/images/play-normal-red.png"));
            break;
        }

        if(this->mode == 2)
        {
            this->ui->record_button->setChecked(false);
            ui->record_button->setIcon(QIcon(":/images/images/media_record.png"));
        }

        this->mode = 1;
        emit changeMode(this->mode);
        emit numClear();
        ui->number_error->display(0);
        ui->start_button->setIcon(QIcon(":/images/images/red_stop.png"));
        break;
    case 2 :

        if(this->mode == 1)
        {
            this->ui->start_button->setChecked(false);
            ui->start_button->setIcon(QIcon(":/images/images/play-normal-red.png"));
        }
        this->mode = 2;
        emit changeMode(this->mode);
        emit keyClear();
        ui->record_button->setIcon(QIcon(":/images/images/red_stop_rec.png"));
        break;
    case 3 :

        break;
    default : break;
    }
}
