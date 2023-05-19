#ifndef CARDVIEW_H
#define CARDVIEW_H

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
    VueCarte(const Clan& c, QWidget *parent = nullptr);
    explicit VueCarte(QWidget *parent = nullptr);

    // affecter une nouvelle carte à la vue
    void setCarte(const Clan& c) { setCheckable(true); setChecked(false); carte=&c; update(); }

    // vue sans carte
    void setNoCarte() { carte=nullptr; setCheckable(false); update(); }
    const Clan& getCarte() const { return *carte; }
    bool cartePresente() const { return carte!=nullptr; }
protected:
    //void paintEvent(QPaintEvent *event) override;
private:
    const Clan* carte=nullptr;
    QPen pen;
    QBrush brush;
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void carteClicked(VueCarte*);
public slots:
private slots:
    void clickedEvent() { emit carteClicked(this); }
};

#endif // CARDVIEW_H


