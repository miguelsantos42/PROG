#include "SVGElements.hpp"
#include "Point.hpp"
#include <cmath>

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
    Rect::Rect(const Color &fill, const Point &corner, int width, int height)
        : fill(fill), corner(corner), width(width), height(height) {}

    void Rect::draw(PNGImage &img) const {
        for (int i = corner.x; i < corner.x + width; i++) {
            for (int j = corner.y; j < corner.y + height; j++) {
                img.at(i, j) = fill;
            }
        }
    }

    void Rect::translate(const Point &offset) {
        corner = corner.translate(offset);
    }

    void Rect::rotate(int angle, const Point &origin) {
        corner = corner.rotate(origin, angle);
    }

    void Rect::scale(int factor, const Point &origin) {
        corner = corner.scale(origin, factor);
        width *= factor;
        height *= factor;
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
        for (size_t i = 0; i < points.size() - 1; i++) {
            img.draw_line(points[i], points[i + 1], fill);
        }
        img.draw_line(points[points.size() - 1], points[0], fill);
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

    // Group
    Group::Group() {}
    Group::~Group() {
        for (SVGElement* element : elements) {
            delete element;
        }
    }

    void Group::addElement(SVGElement* element) {
        elements.push_back(element);
    }

    void Group::draw(PNGImage &img) const {
        for (SVGElement* element : elements) {
            element->draw(img);
        }
    }

    void Group::translate(const Point &offset) {
        for (SVGElement* element : elements) {
            element->translate(offset);
        }
    }

    void Group::rotate(int angle, const Point &origin) {
        for (SVGElement* element : elements) {
            element->rotate(angle, origin);
        }
    }

    void Group::scale(int factor, const Point &origin) {
        for (SVGElement* element : elements) {
            element->scale(factor, origin);
        }

    }
}
