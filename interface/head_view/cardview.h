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
    void setCarte(const Card* c) {
        carte=c;
        update();
    }



    // vue sans carte
    void setNoCarte() { carte=nullptr; setCheckable(false); update();}
    void setUnclickable() { carte=nullptr; setCheckable(false); setEnabled(false); update(); }
    const Card& getCarte() const { return *carte; }
    bool cartePresente() const { return carte!=nullptr; }
    void setNb(int i){nb = i;}
    void setStoneNb(int i){stoneNb = i;}
    void setSide(int i){side = i;}
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    int nb;
    int stoneNb;
    int side;
    const Card* carte=nullptr;
    QPen pen;
    QBrush brush;
    void dessinerClan(QPainter &painter); //pour le cas des cartes Clan
    void dessinerTactical(QPainter &painter); //pour le cas des cartes Tactiques

    //SIGNAUX ET SLOTS
signals:
    // quand la vue de la carte est cliquée, elle émet un signal en transmettant son adresse
    void carteClicked(int i);
    void carteSurBorneClicked(int i, int i2, int i3);
public slots:
private slots:
    //a adapter !
    void clickedEvent() { emit carteClicked(nb); emit carteSurBorneClicked(nb, stoneNb,side); cout << "card clicked"<<endl; }
};



#endif // CARDVIEW_OLD_H


