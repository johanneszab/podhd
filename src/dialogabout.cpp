#include "dialogabout.h"
#include "ui_dialogabout.h"

dialogAbout::dialogAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialogAbout)
{
    ui->setupUi(this);

    connect( ui->pb_okay, SIGNAL( clicked() ), this, SLOT( close() ) );

}

dialogAbout::~dialogAbout()
{
    delete ui;
}
