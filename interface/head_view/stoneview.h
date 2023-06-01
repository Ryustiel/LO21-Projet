#ifndef STONEVIEW_H
#define STONEVIEW_H
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../../head/Card.h"
#include "../../head/Board.h"


class VueBorne : public QPushButton
{
    Q_OBJECT
public:
    //deux constructeurs differents
    explicit VueBorne(/*const Stone& s,*/ QWidget *parent = nullptr);
    const Stone& getCarte() const { return *borne; }
protected:
           //void paintEvent(QPaintEvent *event) override;
private:
    const Stone* borne=nullptr;
    QPen pen;
    QBrush brush;
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void carteClicked(VueBorne*);
public slots:
private slots:
    void clickedEvent() { emit carteClicked(this); }
};






#endif // STONEVIEW_H
