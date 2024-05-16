#include <iostream>
#include <sstream>
#include <algorithm>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include "Color.hpp"

using namespace std;
using namespace tinyxml2;

namespace svg {
    // Helper function to create Point
    Point create_point(int x, int y) {
        Point p;
        p.x = x;
        p.y = y;
        return p;
    }

    void apply_transformations(SVGElement* element, const string& transform, const Point& origin) {
        istringstream ss(transform);
        string operation;

        while (ss >> operation) {
            if(operation.find("translate") != string::npos) {
                int x, y;
                sscanf(operation.c_str(), "translate(%d,%d)", &x, &y);
                element->translate(create_point(x, y));
            } else if (operation.find("rotate") != string::npos) {
                int angle;
                sscanf(operation.c_str(), "rotate(%d)", &angle);
                element->rotate(angle, origin);
            } else if (operation.find("scale") != string::npos) {
                int factor;
                sscanf(operation.c_str(), "scale(%d)", &factor);
                element->scale(factor, origin);
            }
        }
    }

    void parse_element(XMLElement* xml_elem, vector<SVGElement*>& svg_elements) {
        const char* value = xml_elem->Value();
        SVGElement* element = nullptr;
        if (strcmp(value, "ellipse") == 0) {
            int cx = xml_elem->IntAttribute("cx");
            int cy = xml_elem->IntAttribute("cy");
            int rx = xml_elem->IntAttribute("rx");
            int ry = xml_elem->IntAttribute("ry");
            const char* fillStr = xml_elem->Attribute("fill");
            Color fill = parse_color(fillStr ? fillStr : "");
            element = new Ellipse(fill, create_point(cx, cy), create_point(rx, ry));
        } else if (strcmp(value, "circle") == 0) {
            int cx = xml_elem->IntAttribute("cx");
            int cy = xml_elem->IntAttribute("cy");
            int r = xml_elem->IntAttribute("r");
            const char* fillStr = xml_elem->Attribute("fill");
            Color fill = parse_color(fillStr ? fillStr : "");
            element = new Circle(fill, create_point(cx, cy), r);
        } else if (strcmp(value, "polyline") == 0) {
            vector<Point> points;
            const char* pointsStr = xml_elem->Attribute("points");
            istringstream pointsStream(pointsStr);
            string point;
            while (getline(pointsStream, point, ' ')) {
                replace(point.begin(), point.end(), ',', ' ');
                istringstream pointStream(point);
                int x, y;
                pointStream >> x >> y;
                points.push_back(create_point(x, y));
            }
            const char* strokeStr = xml_elem->Attribute("stroke");
            Color stroke = parse_color(strokeStr ? strokeStr : "");
            element = new Polyline(stroke, points);
        } else if (strcmp(value, "line") == 0) {
            int x1 = xml_elem->IntAttribute("x1");
            int y1 = xml_elem->IntAttribute("y1");
            int x2 = xml_elem->IntAttribute("x2");
            int y2 = xml_elem->IntAttribute("y2");
            const char* strokeStr = xml_elem->Attribute("stroke");
            Color stroke = parse_color(strokeStr ? strokeStr : "");
            element = new Line(stroke, create_point(x1, y1), create_point(x2, y2));
        } else if (strcmp(value, "polygon") == 0) {
            vector<Point> points;
            const char* pointsStr = xml_elem->Attribute("points");
            istringstream pointsStream(pointsStr);
            string point;
            while (getline(pointsStream, point, ' ')) {
                replace(point.begin(), point.end(), ',', ' ');
                istringstream pointStream(point);
                int x, y;
                pointStream >> x >> y;
                points.push_back(create_point(x, y));
            }
            const char* fillStr = xml_elem->Attribute("fill");
            Color fill = parse_color(fillStr ? fillStr : "");
            element = new Polygon(fill, points);
        } else if (strcmp(value, "rect") == 0) {
            int x = xml_elem->IntAttribute("x");
            int y = xml_elem->IntAttribute("y");
            int width = xml_elem->IntAttribute("width");
            int height = xml_elem->IntAttribute("height");
            const char* fillStr = xml_elem->Attribute("fill");
            Color fill = parse_color(fillStr ? fillStr : "");
            element = new Rect(fill, create_point(x, y), width, height);
        } else if (strcmp(value, "g") == 0) {
            Group* group = new Group();
            for (XMLElement* child = xml_elem->FirstChildElement(); child; child = child->NextSiblingElement()) {
                parse_element(child, group->elements);
            }
            const char* transform = xml_elem->Attribute("transform");
            const char* transform_origin = xml_elem->Attribute("transform-origin");
            Point origin = transform_origin ? create_point(atoi(transform_origin), atoi(strchr(transform_origin, ' ') + 1)) : create_point(0, 0);
            if (transform) {
                apply_transformations(group, transform, origin);
            }
            element = group;
        }

        if (element) {
            const char* transform = xml_elem->Attribute("transform");
            const char* transform_origin = xml_elem->Attribute("transform-origin");
            Point origin = transform_origin ? create_point(atoi(transform_origin), atoi(strchr(transform_origin, ' ') + 1)) : create_point(0, 0);
            if (transform) {
                apply_transformations(element, transform, origin);
            }
            svg_elements.push_back(element);
        }
    }

    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement*>& svg_elements) {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS) {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement* xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");

        // Parse child elements
        for (XMLElement* child = xml_elem->FirstChildElement(); child; child = child->NextSiblingElement()) {
            parse_element(child, svg_elements);
        }
    }
}
