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
    topcorner = glm::vec3(std::numeric_limits<float>::min());
    bottomcorner = glm::vec3(std::numeric_limits<float>::max());

    points.reserve(nvertices);
    for(auto i=0; i < nvertices; ++i) {
        if (!get_next_uncommented_line(infile,info)) {
            return false;
        }
        std::istringstream info_stream(info);
        glm::vec3 point;
        info_stream >> point.x >> point.y >> point.z;
        points.emplace_back(point);
        // Calculating bounding-box
        topcorner.x = std::max(topcorner.x, point.x);
        topcorner.y = std::max(topcorner.y, point.y);
        topcorner.z = std::max(topcorner.z, point.z);
        bottomcorner.x = std::min(bottomcorner.x, point.x);
        bottomcorner.y = std::min(bottomcorner.y, point.y);
        bottomcorner.z = std::min(bottomcorner.z, point.z);
    }

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
    return (loaded = true);
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
            for (const auto & i : indexes) {
                glVertex3f(points[i].x, points[i].y, points[i].z);
            }
            glEnd();
        }
    }
}
