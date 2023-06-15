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
    explicit VuePioche(const Deck& d, QWidget *parent = nullptr);
protected:
           //void paintEvent(QPaintEvent *event) override;
private:
    const Deck* pioche=nullptr;
    QPen pen;
    QBrush brush;
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void carteClicked(VuePioche*);
public slots:
private slots:
    void clickedEvent() { emit carteClicked(this); }
};



#endif // DECKVIEW_H
