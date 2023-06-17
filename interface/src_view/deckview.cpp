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
#include "../head_view/deckview.h"

VuePioche::VuePioche(Deck& d, QWidget *parent) : QPushButton(parent), pioche(&d)
{
    setText("Pioche");
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(50,80);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(true);
}


