#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>

class TextItem : public QGraphicsTextItem
{
public:
    enum { Type = UserType + 5};

    explicit TextItem(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void focusOutEvent(QFocusEvent *focusEvent) override;

private:
    QMenu *contextMenu;
};

#endif // TEXTITEM_H
