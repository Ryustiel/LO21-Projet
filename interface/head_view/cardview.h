
#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../../head/Card.h"

//classe mère abstraite VUE CARTE
class VueCarte : public QPushButton
{
    Q_OBJECT
public:
    VueCarte(const Card& c, QWidget *parent = nullptr);
    explicit VueCarte(QWidget *parent = nullptr);

    //permet la création d'une instance VueCarte en fonction du type de carte
    static VueCarte* createVueCarte(const Card& c, QWidget* parent = nullptr);

    void setCarte(const Card& c); //{ setCheckable(true); setChecked(false); carte = &c; update(); }
    void setNoCarte() { carte = nullptr; setCheckable(false); update(); }
    const Card& getCarte() const { return *carte; }
    bool cartePresente() const { return carte != nullptr; }

protected:
    virtual void dessiner(QPainter& painter) = 0;

    void paintEvent(QPaintEvent *event) override;

private:
    const Card* carte = nullptr;
    QPen pen;
    QBrush brush;

signals:
    void carteClicked(VueCarte*);

public slots:

private slots:
    void clickedEvent() { emit carteClicked(this); }
};

//classe fille CARTE CLAN
class VueCarteClan : public VueCarte
{
public:
    VueCarteClan(const Clan& c, QWidget* parent = nullptr) : VueCarte(c, parent) {}

protected:
    void dessiner(QPainter& painter) override;
};


//classe fille CARTE CLAN
class VueCarteTactical : public VueCarte
{
public:
    VueCarteTactical(const Tactical& t, QWidget* parent = nullptr) : VueCarte(t, parent) {}

protected:
    void dessiner(QPainter& painter) override;
};

#endif // CARDVIEW_H
