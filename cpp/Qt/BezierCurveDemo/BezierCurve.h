#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <cmath>

#include <QtCore/QPointF>
#include <QtCore/QVector>


class QStylePainter;


inline qreal distance(const QPointF &p1, const QPointF &p2)
{
    qreal xd = p2.x() - p1.x();
    qreal yd = p2.y() - p1.y();

    return std::sqrt(xd*xd + yd*yd);
}

struct BezierCurve
{
    enum Type
    {
        Invalid = 0,
        Linear = 2,
        Quadratic = 3,
        Cubic = 4,
    };

    BezierCurve()
    {
        controlPoints.reserve(4);
    }

    virtual ~BezierCurve()
    {
    }

    Type getType() const
    {
        if (controlPoints.size() >= 2 && controlPoints.size() <= 4)
            return static_cast<Type>(controlPoints.size());

        return Invalid;
    }

    bool addPoint(const QPointF &pt)
    {
        if (controlPoints.size() == 4)
            return false;

        controlPoints.push_back(pt);
        return true;
    }

    bool removePoint()
    {
        if (controlPoints.empty())
            return false;

        controlPoints.pop_back();
        return true;
    }

    bool removePoint(const QPointF &pt)
    {
        QPointF *hitPt = hitTest(pt);
        if (hitPt == nullptr)
            return false;

        if (hitPt == start())
        {
            if (controlPoints.size() >= 2)
            {
                controlPoints[0] = controlPoints[1];
                controlPoints.resize(1);
            }
            else
            {
                controlPoints.clear();
            }
        }
        else if (hitPt == end())
        {
            controlPoints.resize(1);
        }
        else if (hitPt == c1())
        {
            controlPoints.removeAt(2);
        }
        else if (hitPt == c2())
        {
            controlPoints.removeAt(3);
        }

        return true;
    }

    QPointF *hitTest(const QPointF &pt)
    {
        if (controlPoints.empty())
            return nullptr;

        QPointF *p = &controlPoints[0];
        qreal d = distance(controlPoints[0], pt);

        for (int i = 1; i < controlPoints.size(); ++i)
        {
            qreal temp = distance(controlPoints[i], pt);

            if (d > temp)
            {
                d = temp;
                p = &controlPoints[i];
            }
        }

        return d <= R ? p : nullptr;
    }

    QPointF *start()
    {
        return controlPoints.empty() ? nullptr : &controlPoints[0];
    }

    QPointF *end()
    {
        return controlPoints.size() < 2 ? nullptr : &controlPoints[1];
    }

    QPointF *c1()
    {
        return controlPoints.size() < 3 ? nullptr : &controlPoints[2];
    }

    QPointF *c2()
    {
        return controlPoints.size() != 4 ? nullptr : &controlPoints[3];
    }

    const QVector<QPointF> &points(int maxPoints = -1);

    virtual void draw(QStylePainter &painter);

    static constexpr qreal R = 12.0f;

private:
    QVector<QPointF> controlPoints; // start, end, c1, c2
    QVector<QPointF> pointsOnCurve;
};

struct DecoratedBezierCurve : public BezierCurve
{
    virtual void draw(QStylePainter &painter);

private:
    void drawPointMarker(QStylePainter &painter, const QPointF &pt);
};

#endif

// References:
// [Bézier curve](https://en.wikipedia.org/wiki/B%C3%A9zier_curve)
