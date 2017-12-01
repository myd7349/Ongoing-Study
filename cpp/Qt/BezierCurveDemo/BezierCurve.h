#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <QtCore/QPointF>
#include <QtCore/QVector>

#include "../../../algorithm/graphics/BezierCurve/DeCasteljau.hpp"



class QStylePainter;


struct BezierCurve
{
    enum Type
    {
        Invalid = 0,
        Linear = 2,
        Quadratic = 3,
        Cubic = 4,
    };

    enum RasterizationMethod
    {
        Incremental = 0,
        AdaptiveRecursiveSubdivision = 1, // De Casteljau's algorithm
    };

    BezierCurve()
    {
        controlPoints.reserve(4);
        method = AdaptiveRecursiveSubdivision;
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

    QPointF *hitTest(const QPointF &pt);

    bool isOnCurve(const QPointF &pt, double tolerance = 4.0);

    void offset(const QPointF &xy);

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

    RasterizationMethod rasterizationMethod() const
    {
        return method;
    }

    void rasterizationMethod(RasterizationMethod method_)
    {
        method = method_;
    }

    void switchRasterizationMethod()
    {
        method = static_cast<RasterizationMethod>(static_cast<int>(method) ^ 1);
    }

    void rasterize(QVector<QPointF> &points, QVector<Line<QPointF, qreal>> &tangents)
    {
        switch (method) {
        case Incremental:
            rasterizeInc(points, tangents);
            break;
        case AdaptiveRecursiveSubdivision:
            rasterizeSubDiv(points, tangents);
            break;
        default: Q_ASSERT(false); break;
        }
    }

    virtual void draw(QStylePainter &painter);

    static constexpr qreal R = 12.0f;

protected:
    QVector<QPointF> pointsOnCurve;
    QVector<Line<QPointF, qreal>> tangents;

private:
    void rasterizeInc(QVector<QPointF> &points, QVector<Line<QPointF, qreal>> &tangents);
    void rasterizeSubDiv(QVector<QPointF> &points, QVector<Line<QPointF, qreal>> &tangents);

    QVector<QPointF> controlPoints; // start, end, c1, c2
    RasterizationMethod method;
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
