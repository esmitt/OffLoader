#include "OffObject.h"
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

COffObject::COffObject()
{
	m_nPoints = 0;
	m_nTriangles = 0;
	m_pVecTriangles = NULL;
	m_pVecPoints = NULL;
}

COffObject::~COffObject(void)
{
	if(m_pVecTriangles)
		delete [] m_pVecTriangles;
	if(m_pVecPoints)
		delete [] m_pVecPoints;
}

bool COffObject::loadFile(std::string strFilename)
{
	ifstream file(strFilename);
	if(!file.is_open()) return false;
	string input;
	int i, temp;
	glm::vec3 minVertex(INT_MAX), maxVertex(INT_MIN);
	file >> input;	//"OFF" word
	file >> m_nPoints >> m_nTriangles >> i;
	//create the points and triangles
	if(m_pVecPoints) delete [] m_pVecPoints;
	if(m_pVecTriangles) delete [] m_pVecTriangles;
	m_pVecPoints = new glm::vec3[m_nPoints];
	m_pVecTriangles = new glm::uvec3[m_nTriangles];
	
	//define max and min
	for(i = 0; i < m_nPoints; i++)
	{
		file >> m_pVecPoints[i].x >> m_pVecPoints[i].y >> m_pVecPoints[i].z;
		if(m_pVecPoints[i].x > maxVertex.x) maxVertex.x = m_pVecPoints[i].x;
		if(m_pVecPoints[i].y > maxVertex.y) maxVertex.y = m_pVecPoints[i].y;
		if(m_pVecPoints[i].z > maxVertex.z) maxVertex.z = m_pVecPoints[i].z;
		if(m_pVecPoints[i].x < minVertex.x) minVertex.x = m_pVecPoints[i].x;
		if(m_pVecPoints[i].y < minVertex.y) minVertex.y = m_pVecPoints[i].y;
		if(m_pVecPoints[i].z < minVertex.z) minVertex.z = m_pVecPoints[i].z;
	}
	
	m_vecCenter = (maxVertex + minVertex) / 2.f;
	m_fScale = 1.f / glm::max(maxVertex.x - minVertex.x, glm::max(maxVertex.y - minVertex.y, maxVertex.z - minVertex.z));
	
	for(i = 0; i < m_nTriangles; i++)
	{
		file >> temp;
		if(temp > 3)
		{
			std::cout << "a polygon with more than 3 vertexes" << std::endl;
			break;
		}
		else
			file >> m_pVecTriangles[i][VERTEX1] >> m_pVecTriangles[i][VERTEX2] >> m_pVecTriangles[i][VERTEX3];
	}
	file.close();
	if(i != m_nTriangles) return false;
	//m_pBitmap = FreeImage_Allocate(iWidth, iHeight, 24);
	//m_iWidth = iWidth;
	//m_iHeight = iHeight;
	std::cout << "\""<< strFilename<< "\""<< " succefully loaded" << endl;
	std::cout << "number of vertexes: " << m_nPoints << endl;
	std::cout << "number of triangles: " << m_nTriangles << endl;
	return true;
}
