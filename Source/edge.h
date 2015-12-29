#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode, bool color);
	~Edge()
	{
		source = nullptr;
		dest = nullptr;
	}
    Node *sourceNode() const;
    Node *destNode() const;

    void adjust();
	void advance(int phase)  Q_DECL_OVERRIDE;

    enum { Type = UserType + 2 };
    int type() const Q_DECL_OVERRIDE { return Type; }



protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    bool color;
};

#endif // EDGE_H
