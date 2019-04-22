//
// Created by reinaldo on 4/19/19.
//

#ifndef OFFDISPLAY_OFFOBJECT_H
#define OFFDISPLAY_OFFOBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "glm/glm.hpp"
#include "GL/glu.h"

bool get_next_uncommented_line(std::ifstream &infile, std::string &result) {
    while(getline(infile,result)) {
        if(result.length() > 1 && result[0] != '#') {
            return true;
        }
    }
    return false;
}


enum class DISPLAY_TYPE{POINTS=0, WIRE=1, POLYGONS=2};
class OffObject {
protected:
    bool loaded;
    unsigned long nvertices, nfaces, nedges;
    std::vector<glm::vec3> points;
    std::vector<std::vector<unsigned  long>> polygons;
    GLfloat xmax{}, xmin{}, ymax{}, ymin{}, zmax{}, zmin{};
    glm::vec3 centroid{};
    void normalize();
public:
    OffObject() : loaded(false), nvertices(0), nfaces(0), nedges(0) {}
    explicit OffObject(const std::string &);
    bool loadFile(const std::string &);
    void draw(DISPLAY_TYPE displayType=DISPLAY_TYPE::WIRE) const;
    void cleanUp() {
        loaded = false;
        nvertices = nfaces = nedges = 0;
        points.clear();
        polygons.clear();
    }

    ~OffObject(){
        cleanUp();
    }
};

#endif //OFFDISPLAY_OFFOBJECT_H
