//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include <vector>
#include <string>

namespace svg
{
    class SVGElement
    {
    public:
        SVGElement();
        virtual ~SVGElement();

        virtual void draw(PNGImage &img) const = 0;

        // other transformations
        virtual void translate(const Point &offset) = 0;
        virtual void rotate(int angle, const Point &origin) = 0;
        virtual void scale(int factor, const Point &origin) = 0;
    };

    // Declaration of namespace functions
    void readSVG(const std::string &svg_file, Point &dimensions, std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file, const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;
        void translate(const Point &offset) override;
        void rotate(int angle, const Point &origin) override;
        void scale(int factor, const Point &origin) override;

    private:
        Color fill;
        Point center;
        Point radius;
    };

    class Circle : public SVGElement
    {
    public:
        Circle(const Color &fill, const Point &center, int radius);
        void draw(PNGImage &img) const override;
        void translate(const Point &offset) override;
        void rotate(int angle, const Point &origin) override;
        void scale(int factor, const Point &origin) override;

    private:
        Color fill;
        Point center;
        int radius;
    };

    class Rect : public SVGElement
    {
    public:
        Rect(const Color &fill, const Point &corner1, const Point &corner2, const Point &corner3, const Point &corner4);
        void draw(PNGImage &img) const override;
        void translate(const Point &offset) override;
        void rotate(int angle, const Point &origin) override;
        void scale(int factor, const Point &origin) override;

    private:
        Color fill;
        Point corner1;
        Point corner2;
        Point corner3;
        Point corner4;
    };

    class Line : public SVGElement
    {
    public:
        Line(const Color &stroke, const Point &start, const Point &end);
        void draw(PNGImage &img) const override;
        void translate(const Point &offset) override;
        void rotate(int angle, const Point &origin) override;
        void scale(int factor, const Point &origin) override;

    private:
        Color stroke;
        Point start;
        Point end;
    };

    class Polyline : public SVGElement
    {
    public:
        Polyline(const Color &stroke, const std::vector<Point> &points);
        void draw(PNGImage &img) const override;
        void translate(const Point &offset) override;
        void rotate(int angle, const Point &origin) override;
        void scale(int factor, const Point &origin) override;

    private:
        Color stroke;
        std::vector<Point> points;
    };

    class Polygon : public SVGElement
    {
    public:
        Polygon(const Color &fill, const std::vector<Point> &points);
        void draw(PNGImage &img) const override;
        void translate(const Point &offset) override;
        void rotate(int angle, const Point &origin) override;
        void scale(int factor, const Point &origin) override;

    private:
        Color fill;
        std::vector<Point> points;
    };
}
#endif
