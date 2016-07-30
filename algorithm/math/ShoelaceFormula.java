// 2015-09-18T11:49+08:00

public final class ShoelaceFormula {
    private static double shoelace_formula(Point2D[] points) {
        double area = 0.0;

        int j;
        for (int i = 0; i < points.length; i++) {
            j = (i + 1) % points.length;
            area += points[i].x * points[j].y - points[j].x * points[i].y;
        }

        return area / 2.0;
    }

    public static double polyarea(Point2D[] points) {
        return Math.abs(shoelace_formula(points));
    }

    public static boolean isploycw(Point2D[] points) {
        return shoelace_formula(points) < 0;
    }

    public static void main(String[] args) {
        Point2D[] polygon1 = new Point2D[] {
            new Point2D(3, 4), 
            new Point2D(5, 6), 
            new Point2D(9, 5), 
            new Point2D(12, 8), 
            new Point2D(5, 11),
        };

        System.out.println("Polygon Area: " + polyarea(polygon1) + " Clockwise? " + isploycw(polygon1));

        Point2D[] polygon2 = new Point2D[] {
            new Point2D(2, 1), 
            new Point2D(4, 5), 
            new Point2D(7, 8), 
        };

        System.out.println("Polygon Area: " + polyarea(polygon2) + " Clockwise? " + isploycw(polygon2));
    }
}


class Point2D {
    public double x;
    public double y;

    public Point2D(double x, double y) {
        this.x = x;
        this.y = y;
    }
}

// When there are only 3 points(that is, a triangle), the formula is transformed to:
// (Suppose the 3 points are A, B, C)
// 0.5 * |A.x * B.y + B.x * C.y + C.x * A.y - B.x * A.y - C.x * B.y - A.x * C.y|
// 0.5 * |A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)|
// 0.5 * |A.x * ((B.y  - A.y) - (C.y - A.y)) + B.x * (C.y - A.y) + C.x * (A.y - B.y)|
// 0.5 * |(B.y - A.y) * (A.x - C.x) + (C.y - A.y) * (B.x - A.x)| (1)
// that's how Point2D/area2 in Algorithms exercise 1.2.1 works.
// A trangle's area can also be calculated by the cross product of vector AB and BC:
// area = 0.5 * |AB x AC| = 0.5 * |AB x BC| = 0.5 * |AC x BC|
// we can get formula (1) from this formula too.


// References:
// [Shoelace formula](https://en.wikipedia.org/wiki/Shoelace_formula)
// [How to determine if a list of polygon points are in clockwise order?](http://stackoverflow.com/questions/1165647/how-to-determine-if-a-list-of-polygon-points-are-in-clockwise-order)
// [Algorithms, 4th Edition, Exercise 1.2.1](https://github.com/kevin-wayne/algs4/blob/master/src/main/java/edu/princeton/cs/algs4/Point2D.java)
// [Curve orientation](https://en.wikipedia.org/wiki/Curve_orientation)
// [Ploygon Area](http://mathworld.wolfram.com/PolygonArea.html)
// GRAPHICS GEMS II/2D GEOMETRY AND ALGORITHMS/I.1 THE AREA OF A SIMPLE POLYGON
