OffLoader
-------------

It is a simple loader of files OFF (Object File Format). The code read the file which is totally basic and contains only triangles, i.e. 3 vertexes by triangle; and no color per vertex/triangle. In order to support quads or more, it is necessary the subdivision of the primitives.

The data structure used is very simple. It is based on stores the number of vertexes, triangles and two dynamic arrays (you can change them by vectors). Also, the base data type such as point3f and others were performed using the OpenGL Mathematics (http://glm.g-truc.net/).

The code includes the GLM, FreeGLUT (including dll/lib) and a simple .OFF file to test. There are several pages which have .OFF file to download.

I REMEMBER AGAIN: this code is only to be used as a template. There is no efficiency inside the code, Actually, it includes the slower and deprecated way to render in OpenGL: glBegin/glEnd.
