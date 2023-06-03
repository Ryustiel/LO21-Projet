#include "../head_view/cardview_old.h"
#include <QPainter>
#include <QString>
#include <QStaticText>
#include <QColor>
#include <string>
#include <typeinfo>
#include <iostream>

/*
VueCarte::VueCarte(const Card& c, QWidget *parent) : QPushButton(parent),carte(&c)
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


//methode privée pour dessiner nombre sur la carte dans la bonne couleur
void VueCarte::dessinerNombre(QPainter &painter)
{
    if (carte != nullptr && dynamic_cast<const Clan*>(carte) != nullptr) //si il y a bien une carte associée à la vue
    //&& (typeid(*carte).name()=="Clan")
    {
        const Clan* c=static_cast<const Clan *>(carte);
        //painter.setPen(Qt::black); // Couleur du texte
        QColor couleurCarte = QColor::fromString(toString(c->getColor()));
        painter.setPen(couleurCarte); // Couleur du texte
        painter.setFont(QFont("Arial", 20)); // Police et taille du texte

        // Définir la position du texte sur la carte (par exemple, au centre)
        int textPosX = width() / 2;
        int textPosY = height() / 2;

        painter.drawText(textPosX, textPosY, QString::number(toInt(c->getNumber()))); // Dessiner le nombre sur la carte
    }
}

void VueCarte::dessinerNom(QPainter &painter)
{
    if (carte != nullptr && dynamic_cast<const Tactical*>(carte) != nullptr) //si il y a bien une carte associée à la vue
    //&& (typeid(*carte).name()=="Clan")
    {
        const Tactical* c=static_cast<const Tactical *>(carte);
        painter.setPen(Qt::black); // Couleur du texte
        //QColor couleurCarte = QColor::fromString(toString(c->getColor()));
        //painter.setPen(couleurCarte); // Couleur du texte
        painter.setFont(QFont("Arial", 20)); // Police et taille du texte

        // Définir la position du texte sur la carte (par exemple, au centre)
        int textPosX = width() / 2;
        int textPosY = height() / 2;

        painter.drawText(textPosX, textPosY, QString::fromStdString(c->getName())); // Dessiner le nombre sur la carte
    }


}


void VueCarte::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event); // Appel à la méthode paintEvent de la classe de base (QPushButton)

    QPainter painter(this);
    if(dynamic_cast<const Tactical*>(carte) != nullptr){
        dessinerNom(painter); //appel à la méthode pour rendu visuel carte (tactique)
    }
    else{
        dessinerNombre(painter); //appel à la méthode pour rendu visuel carte (clan)
    }

}


*/



