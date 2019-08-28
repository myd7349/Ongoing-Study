#ifndef KNOTSEQUENCE_H
#define KNOTSEQUENCE_H

#include <QtCore/QPointF>
#include <QtCore/QStack>


class QStylePainter;

class KnotSequence : public QStack<QPointF>
{
public:
    void draw(QStylePainter &painter);
};

#endif // KNOTSEQUENCE_H
