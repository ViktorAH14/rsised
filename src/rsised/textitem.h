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
    bool sceneEvent(QEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void focusOutEvent(QFocusEvent *focusEvent) override;

private:
    QMenu *m_contextMenu;
};

#endif // TEXTITEM_H
