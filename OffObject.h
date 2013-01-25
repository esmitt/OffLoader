#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>

#define VERTEX1 0
#define VERTEX2 1
#define VERTEX3 2

class COffObject
{
public:
	unsigned int m_nPoints;
	unsigned int m_nTriangles;
	glm::uvec3* m_pVecTriangles;
	glm::vec3* m_pVecPoints;
	glm::vec3 m_vecCenter;
	float m_fScale;

	//member functions
	COffObject(void);
	~COffObject(void);
	bool loadFile(std::string strFilename);
};

