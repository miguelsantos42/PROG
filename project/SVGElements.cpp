#include "SVGElements.hpp"
#include "Point.hpp"
#include <cmath>
#include <iostream>

// Helper function to create Point
svg::Point create_point(int x, int y) {
    svg::Point p;
    p.x = x;
    p.y = y;
    return p;
}

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse
    Ellipse::Ellipse(const Color &fill, const Point &center, const Point &radius)
        : fill(fill), center(center), radius(radius) {}

    void Ellipse::draw(PNGImage &img) const {
        img.draw_ellipse(center, radius, fill);
    }

    void Ellipse::translate(const Point &offset) {
        center = center.translate(offset);
    }

    void Ellipse::rotate(int angle, const Point &origin) {
        center = center.rotate(origin, angle);
    }

    void Ellipse::scale(int factor, const Point &origin) {
        center = center.scale(origin, factor);
        radius.x *= factor;
        radius.y *= factor;
    }

    // Circle
    Circle::Circle(const Color &fill, const Point &center, int radius)
        : fill(fill), center(center), radius(radius) {}

    void Circle::draw(PNGImage &img) const {
        img.draw_ellipse(center, create_point(radius, radius), fill);
    }

    void Circle::translate(const Point &offset) {
        center = center.translate(offset);
    }

    void Circle::rotate(int angle, const Point &origin) {
        center = center.rotate(origin, angle);
    }

    void Circle::scale(int factor, const Point &origin) {
        center = center.scale(origin, factor);
        radius *= factor;
    }

    // Rect
    Rect::Rect(const Color &fill, const Point &corner1, const Point &corner2, const Point &corner3, const Point &corner4) :
        fill(fill), corner1(corner1), corner2(corner2), corner3(corner3), corner4(corner4)  {}

    void Rect::draw(PNGImage &img) const {
        img.draw_polygon({
            corner1,
            corner2,
            corner3,
            corner4
        }, fill);
    }

    void Rect::translate(const Point &offset) {
        corner1 = corner1.translate(offset);
        corner2 = corner2.translate(offset);
        corner3 = corner3.translate(offset);
        corner4 = corner4.translate(offset);
    }

    void Rect::rotate(int angle, const Point &origin) {
        corner1 = corner1.rotate(origin, angle);
        corner2 = corner2.rotate(origin, angle);
        corner3 = corner3.rotate(origin, angle);
        corner4 = corner4.rotate(origin, angle);
    }

    void Rect::scale(int factor, const Point &origin) {
        corner1 = corner1.scale(origin, factor);
        corner2 = corner2.scale(origin, factor);
        corner3 = corner3.scale(origin, factor);
        corner4 = corner4.scale(origin, factor);
    }

    // Line
    Line::Line(const Color &stroke, const Point &start, const Point &end)
        : stroke(stroke), start(start), end(end) {}

    void Line::draw(PNGImage &img) const {
        img.draw_line(start, end, stroke);
    }

    void Line::translate(const Point &offset) {
        start = start.translate(offset);
        end = end.translate(offset);
    }

    void Line::rotate(int angle, const Point &origin) {
        start = start.rotate(origin, angle);
        end = end.rotate(origin, angle);
    }

    void Line::scale(int factor, const Point &origin) {
        start = start.scale(origin, factor);
        end = end.scale(origin, factor);
    }

    // Polyline
    Polyline::Polyline(const Color &stroke, const std::vector<Point> &points)
        : stroke(stroke), points(points) {}

    void Polyline::draw(PNGImage &img) const {
        for (size_t i = 0; i < points.size() - 1; i++) {
            img.draw_line(points[i], points[i + 1], stroke);
        }
    }

    void Polyline::translate(const Point &offset) {
        for (Point &point : points) {
            point = point.translate(offset);
        }
    }

    void Polyline::rotate(int angle, const Point &origin) {
        for (Point &point : points) {
            point = point.rotate(origin, angle);
        }
    }

    void Polyline::scale(int factor, const Point &origin) {
        for (Point &point : points) {
            point = point.scale(origin, factor);
        }
    }

    // Polygon
    Polygon::Polygon(const Color &fill, const std::vector<Point> &points)
        : fill(fill), points(points) {}

    void Polygon::draw(PNGImage &img) const {
        img.draw_polygon(points, fill);
    }

    void Polygon::translate(const Point &offset) {
        for (Point &point : points) {
            point = point.translate(offset);
        }
    }

    void Polygon::rotate(int angle, const Point &origin) {
        for (Point &point : points) {
            point = point.rotate(origin, angle);
        }
    }

    void Polygon::scale(int factor, const Point &origin) {
        for (Point &point : points) {
            point = point.scale(origin, factor);
        }
    }
}
