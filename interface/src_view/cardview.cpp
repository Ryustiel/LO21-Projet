#include "../head_view/cardview.h"
#include <QPainter>
#include <QString>
#include <QStaticText>
#include <QColor>

VueCarte::VueCarte(const Clan* c, QWidget *parent) : QPushButton(parent),carte(c)
{
    if (c==nullptr) setText("Vide");
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(50,80);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(true);
}

VueCarte::VueCarte(QWidget *parent): QPushButton(parent)
{
    setText("Vide");
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(50,80);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(false);
}


//methode privée pour dessiner nombre sur la carte dans la bonne couleur
void VueCarte::dessinerNombre(QPainter &painter)
{
    if (carte != nullptr) //si il y a bien une carte associée à la vue
    {
        //painter.setPen(Qt::black); // Couleur du texte
        QColor couleurCarte = QColor::fromString(toString(carte->getColor()));
        painter.setPen(couleurCarte); // Couleur du texte
        painter.setFont(QFont("Arial", 20)); // Police et taille du texte

        // Définir la position du texte sur la carte (par exemple, au centre)
        int textPosX = width() / 2;
        int textPosY = height() / 2;
        this->setContentsMargins(0,0,0,0);
        painter.drawText(textPosX, textPosY, QString::number(toInt(carte->getNumber()))); // Dessiner le nombre sur la carte
    }
}


void VueCarte::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event); // Appel à la méthode paintEvent de la classe de base (QPushButton)

    QPainter painter(this);
    dessinerNombre(painter); //appel à la méthode pour rendu visuel carte
}



