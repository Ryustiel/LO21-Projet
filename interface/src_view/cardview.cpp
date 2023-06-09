#include "../head_view/cardview.h"
#include <QPainter>
#include <QString>
#include <QStaticText>
#include <QColor>
#include <string>
#include <iostream>


VueCarte::VueCarte(const Card& c, QWidget* parent) : QPushButton(parent), carte(&c)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(120, 200);
    connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
    setCheckable(true);
    setProperty("class", "open");
    //setStyleSheet("QPushButton:open{ border: 2px solid red;  }");
}

VueCarte::VueCarte(QWidget* parent) : QPushButton(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(120, 200);
    connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
    setCheckable(false);
    setProperty("class", "open");
    //setStyleSheet("QPushButton:open{ border: 2px solid red;  }");
}

/*
VueCarte* VueCarte::createVueCarte(const Card& c, QWidget* parent)
{
    if (const Clan* clanCard = dynamic_cast<const Clan*>(&c))
    {
        return new VueCarteClan(*clanCard, parent);
    }
    else if (const Tactical* tacticalCard = dynamic_cast<const Tactical*>(&c))
    {
        return new VueCarteTactical(*tacticalCard, parent);
    }
    else
    {
        //A REVOIR
        // Gérer le cas où le type de carte n'est pas reconnu ou n'a pas de vue correspondante
        // Par exemple, retourner une instance de la classe de base VueCarte ou nullptr.
        //return new VueCarte(c, parent); // A REGARDER
        return nullptr;
    }
}



void VueCarte::setCarte(const Card& c){
    VueCarte* newVueCarte = createVueCarte(c, parentWidget());

    // Désassocier l'ancienne carte (si présente)
    if (carte != nullptr)
    {
        setNoCarte();
    }




    setCheckable(true);
    setChecked(false);

    // Associer la nouvelle carte et mettre à jour la vue
    carte = &c;
    update();
}
*/


void VueCarte::paintEvent(QPaintEvent* event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);
    dessiner(painter);
}

void VueCarteClan::dessiner(QPainter& painter)
{
    const Clan* c = dynamic_cast<const Clan*>(&getCarte());
    if (c != nullptr)
    {
        qDebug() << "dessiner Clan OK";
        QColor couleurCarte = QColor::fromString(toString(c->getColor()));
        painter.setPen(couleurCarte);
        painter.setFont(QFont("Arial", 20));

        int textPosX = width() / 2;
        int textPosY = height() / 2;

        painter.drawText(textPosX, textPosY, QString::number(toInt(c->getNumber())));
    }
}

void VueCarteTactical::dessiner(QPainter& painter)
{
    const Tactical* t = dynamic_cast<const Tactical*>(&getCarte());
    if (t != nullptr)
    {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 20));

        int textPosX = width() / 2;
        int textPosY = height() / 2;

        painter.drawText(textPosX, textPosY, QString::fromStdString(t->getName()));
    }
}
