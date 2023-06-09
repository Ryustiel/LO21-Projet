#ifndef CARDVIEW_OLD_H
#define CARDVIEW_OLD_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../../head/Card.h"


class VueCarte : public QPushButton
{
    Q_OBJECT
public:
    //deux constructeurs differents
    VueCarte(const Card& c, QWidget *parent = nullptr);
    explicit VueCarte(QWidget *parent = nullptr);

    // affecter une nouvelle carte à la vue
    void setCarte(const Card& c) { setCheckable(true); setChecked(false); carte=&c; update(); }

    // vue sans carte
    void setNoCarte() { carte=nullptr; setCheckable(false); update(); }
    const Card& getCarte() const { return *carte; }
    bool cartePresente() const { return carte!=nullptr; }
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    const Card* carte=nullptr;
    QPen pen;
    QBrush brush;
    void dessinerClan(QPainter &painter); //pour le cas des cartes Clan
    void dessinerTactical(QPainter &painter); //pour le cas des cartes Tactiques

    //SIGNAUX ET SLOTS
signals:
    // quand la vue de la carte est cliquée, elle émet un signal en transmettant son adresse
    void carteClicked(VueCarte*);
public slots:
private slots:
    //a adapter !
    void clickedEvent() { emit carteClicked(this); }
};



#endif // CARDVIEW_OLD_H


