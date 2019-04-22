//
// Created by reinaldo on 4/19/19.
//

#include "OffObject.h"
#include <fstream>
#include <sstream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <limits>
#include <algorithm>

OffObject::OffObject(const std::string & filename) {
    loadFile(filename);
}

bool OffObject::loadFile(const std::string & filename) {
    // 0 - open input file
    std::ifstream infile(filename);
    if(!infile.is_open()) {
        // failed to open the file
        return false;
    }
    // 1 - header
    std::string header;
    if (!get_next_uncommented_line(infile, header)) {
        return false;
    }
    // todo : check for header == "off"

    // 2 - number of vertices, number of faces, number of edges (can be ignored)
    std::string info;
    if (!get_next_uncommented_line(infile, info)) {
        return false;
    }
    std::istringstream info_stream;
    info_stream.str(info);

    info_stream >> nvertices >> nfaces >> nedges;

    // 3 - the actual vertices
    xmax = ymax = zmax = std::numeric_limits<float>::min();
    xmin = ymin = zmin = std::numeric_limits<float>::max();
    points.reserve(nvertices);
    for(auto i=0; i < nvertices; ++i) {
        if (!get_next_uncommented_line(infile,info)) {
            return false;
        }
        std::istringstream info_stream(info);
        glm::vec3 point;
        info_stream >> point.x >> point.y >> point.z;
        points.emplace_back(point);
        xmax = std::max(xmax,point.x); ymax = std::max(ymax,point.y); zmax = std::max(zmax,point.z);
        xmin = std::min(xmin,point.x); ymin = std::min(ymin,point.y); zmin = std::min(zmin,point.z);
    }
    centroid.x = 0.5 * (xmax + xmin);
    centroid.y = 0.5 * (ymax + ymin);
    centroid.z = 0.5 * (zmax + zmin);

    // 4 - the actual faces
    polygons.reserve(nfaces);
    for(auto i=0; i < nfaces; ++i) {
        if (!get_next_uncommented_line(infile,info)) {
            return false;
        }
        std::istringstream info_stream(info);
        unsigned long n;
        unsigned long index;
        info_stream >> n;
        polygons.emplace_back(n);
        for (auto j = 0; j < n; ++j) {
            info_stream >> index;
            polygons[i][j] = index;
        }
    }

    infile.close();
    normalize();
    loaded = true;
    return true;
}

void OffObject::draw(DISPLAY_TYPE displayType) const {
    if (displayType == DISPLAY_TYPE::POINTS) {
        glBegin(GL_POINTS);
        std::for_each(points.begin(), points.end(),
                      [](const auto & point) { glVertex3f(point.x, point.y, point.z); });
        glEnd();
    } else {
        // either WIRE or POLYGONS
        GLenum mode = (displayType == DISPLAY_TYPE::POLYGONS)? GL_POLYGON : GL_LINE_LOOP;
        for(const auto & indexes : polygons) {
            glBegin(mode);
            for (const auto &i : indexes) {
                glVertex3f(points[i].x, points[i].y, points[i].z);
            }
            glEnd();
        }
    }
}

void OffObject::normalize() {
    // centroid of the object at origin
    xmax = ymax = zmax = std::numeric_limits<double>::min();
    xmin = ymin = zmin = std::numeric_limits<double>::max();
    for (auto & point : points) {
        point -= centroid;
        xmax = std::max(xmax,point.x); ymax = std::max(ymax,point.y); zmax = std::max(zmax,point.z);
        xmin = std::min(xmin,point.x); ymin = std::min(ymin,point.y); zmin = std::min(zmin,point.z);
    }

    // rescaling max 1.0
    GLfloat mag = std::max(std::abs(xmax), std::abs(xmin));
            mag = std::max(mag,std::max(std::abs(ymax), std::abs(ymin)));
            mag = std::max(mag,std::max(std::abs(zmax), std::abs(zmin)));
    for (auto & point : points) {
        point /= mag;
    }
}
