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
        points.reserve(4);
    }

    virtual ~BezierCurve()
    {
    }

    Type getType() const
    {
        if (points.size() >= 2 && points.size() <= 4)
            return static_cast<Type>(points.size());

        return Invalid;
    }

    bool addPoint(const QPointF &pt)
    {
        if (points.size() == 4)
            return false;

        points.push_back(pt);
        return true;
    }

    bool removePoint()
    {
        if (points.empty())
            return false;

        points.pop_back();
        return true;
    }

    bool removePoint(const QPointF &pt)
    {
        QPointF *hitPt = hitTest(pt);
        if (hitPt == nullptr)
            return false;

        if (hitPt == start())
        {
            if (points.size() >= 2)
            {
                points[0] = points[1];
                points.resize(1);
            }
            else
            {
                points.clear();
            }
        }
        else if (hitPt == end())
        {
            points.resize(1);
        }
        else if (hitPt == c1())
        {
            points.removeAt(2);
        }
        else if (hitPt == c2())
        {
            points.removeAt(3);
        }

        return true;
    }

    QPointF *hitTest(const QPointF &pt)
    {
        if (points.empty())
            return nullptr;

        QPointF *p = &points[0];
        qreal d = distance(points[0], pt);

        for (int i = 1; i < points.size(); ++i)
        {
            qreal temp = distance(points[i], pt);

            if (d > temp)
            {
                d = temp;
                p = &points[i];
            }
        }

        return d <= R ? p : nullptr;
    }

    QPointF *start()
    {
        return points.empty() ? nullptr : &points[0];
    }

    QPointF *end()
    {
        return points.size() < 2 ? nullptr : &points[1];
    }

    QPointF *c1()
    {
        return points.size() < 3 ? nullptr : &points[2];
    }

    QPointF *c2()
    {
        return points.size() != 4 ? nullptr : &points[3];
    }

    virtual void draw(QStylePainter &painter);

    static constexpr qreal R = 12.0f;

private:
    QVector<QPointF> points; // start, end, c1, c2
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
