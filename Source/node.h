#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

#undef small

class Edge;
class QGraphicsSceneMouseEvent;

class Node : public QGraphicsItem
{
public:
    Node(bool color, bool small = false);

  //  void addEdge(Edge *edge);
  //  QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const Q_DECL_OVERRIDE { return Type; }

  //  void calculateForces();
	void advance(int phase)  Q_DECL_OVERRIDE;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
 //   QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

 //   void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
 //   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
  //  QList<Edge *> edgeList;
  //  QPointF newPos;
    bool color;
    bool small;
};

#endif // NODE_H
