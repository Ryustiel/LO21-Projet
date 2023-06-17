#ifndef DECKVIEW_H
#define DECKVIEW_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../../head/Deck.h"


class VuePioche : public QPushButton
{
    Q_OBJECT
public:
    //deux constructeurs differents
    explicit VuePioche(Deck& d, QWidget *parent = nullptr) ;
protected:
           //void paintEvent(QPaintEvent *event) override;
private:
    Deck * pioche=nullptr;
    QPen pen;
    QBrush brush;
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void piocheClicked(Deck*);
public slots:
    void clickedEvent() { emit piocheClicked(pioche); cout<<"clicked" <<endl; }
};



#endif // DECKVIEW_H
