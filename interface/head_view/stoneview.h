#ifndef STONEVIEW_H
#define STONEVIEW_H
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../../head/Board.h"

/*
class VueBorne : public QPushButton
{
    Q_OBJECT
public:
    //deux constructeurs (une vue vide, puis une vue affectée d'une stone)
    VueBorne(const Stone& s, QWidget *parent = nullptr);
    explicit VueBorne(QWidget *parent = nullptr);

    // affecter une nouvelle carte à la vue
    void setStone(const Stone& s) { setCheckable(true); setChecked(false); stone=&s; update(); }

    // vue vide, sans pointeur sur stone
    void setNoStone() { stone=nullptr; setCheckable(false); update(); }
    const Stone& getStone() const { return *stone; }
    bool StonePresente() const { return stone!=nullptr; }
protected:
           //void paintEvent(QPaintEvent *event) override;
private:
    const Stone* stone=nullptr;
    //un attribut pour savoir le numero de la borne ?? (en termes de placement)
    QPen pen;
    QBrush brush;

//SIGNAUX ET SLOTS
signals:
    // quand la vue de la borne est cliquée, elle émet un signal en transmettant son adresse
    void stoneClicked(VueBorne*);
public slots:
private slots:
    void clickedEvent() { emit stoneClicked(this); }
};
*/

#endif // STONEVIEW_H
