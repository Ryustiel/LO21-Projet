#include "../head_view/cardview.h"
#include <QPainter>
#include <QString>
#include <QStaticText>

VueCarte::VueCarte(const Clan& c, QWidget *parent) : QPushButton(parent),carte(&c)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(120,200);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(true);
}

VueCarte::VueCarte(QWidget *parent): QPushButton(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(120,200);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(false);
}




