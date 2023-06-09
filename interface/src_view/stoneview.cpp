#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>

//fichiers d'en-tête
#include "../head_view/stoneview.h"

VueBorne::VueBorne(/*const Stone& s,*/ QWidget *parent) : QPushButton(parent)/*, borne(&s)*/
{
    setText("Borne");
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(60,40);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(false);
}


