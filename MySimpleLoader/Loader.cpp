/*
Created By: Sami Qureshi [CS141082]
*/

#include <windows.h>
#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include <string>
#include "Vec3.h"

#define KEY_ESCAPE 27

class MyGlutWindow
{
public:
	int width;
	int height;
	char* title;
	float fov_angle;
	float clip_near;
	float clip_far;
};

/*MODEL*/

class MyModel
{
public:
	//Constructor
	MyModel();
	// Load model
	int loadModel(char *filename);	
	// Draw model
	void drawModel();	
	// Delete model
	void deleteModel();	
	//Calculate normal given 3 vertices
	Vec3 calculateNormal(Vec3 vertA, Vec3 vertB, Vec3 vertC);

	float* normals;			// For storing normals
	float* faces;			// For storing triangles
	float* vertexBuffer;	// For storing vertices
	long totalVertices;		// For storing total number of connected vertices
	long totalTriangles;	// For storing total number of connected triangles

};

MyModel::MyModel() :totalTriangles(0), totalVertices(0){};

int MyModel::loadModel(char* filename)
{
	std::string line;
	std::ifstream myOBJFile(filename);
	// If model file is open
	if (myOBJFile.is_open())													
	{
		// Go to end of the file
		myOBJFile.seekg(0, std::ios::end);	
		// get file size
		long long fileSize = myOBJFile.tellg();									
		myOBJFile.seekg(0, std::ios::beg);										
		// Allocate memory for the vertices
		vertexBuffer = (float*)malloc(fileSize);	
		// Allocate memory for the triangles
		faces = (float*)malloc(fileSize * sizeof(float));	
		// Allocate memory for the normals
		normals = (float*)malloc(fileSize * sizeof(float));					
		// Set triangle index to zero
		int triangle_index = 0;		
		// Set normal index to zero
		int normal_index = 0;												
		// Start reading file data
		while (!myOBJFile.eof())											
		{
			// Get line from file
			getline(myOBJFile, line);											
			// If the first character is a v, this is a vertex
			if (line.c_str()[0] == 'v')										
			{
				// Set first character to 0 so we can use sscanf
				line[0] = ' ';												
				// Read floats from the line: v X Y Z
				sscanf(line.c_str(), "%f %f %f ",							
					&vertexBuffer[totalVertices],
					&vertexBuffer[totalVertices + 1],
					&vertexBuffer[totalVertices + 2]);
				// Add 3 to the total connected points
				totalVertices += 3;					
			}
			// If the first character is a v, this is a face
			if (line.c_str()[0] == 'f')										
			{
				line[0] = ' ';												

				int vertexNumber[4] = { 0, 0, 0 };
				// Read integers from the line:  f 1 2 3
				sscanf(line.c_str(), "%i%i%i",								
					&vertexNumber[0],										 
					&vertexNumber[1],										
					&vertexNumber[2]);										
				// OBJ file starts counting from 1
				vertexNumber[0] -= 1;										
				vertexNumber[1] -= 1;										
				vertexNumber[2] -= 1;										


				
				// Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z)
				int tCounter = 0;
				for (int i = 0; i < 3; i++)
				{
					faces[triangle_index + tCounter] = vertexBuffer[3 * vertexNumber[i]];
					faces[triangle_index + tCounter + 1] = vertexBuffer[3 * vertexNumber[i] + 1];
					faces[triangle_index + tCounter + 2] = vertexBuffer[3 * vertexNumber[i] + 2];
					tCounter += 3;
				}

				// Calculate all normals, used for lighting
				Vec3 vertA(faces[triangle_index], faces[triangle_index + 1], faces[triangle_index + 2]);
				Vec3 vertB(faces[triangle_index + 3], faces[triangle_index + 4], faces[triangle_index + 5]);
				Vec3 vertC(faces[triangle_index + 6], faces[triangle_index + 7], faces[triangle_index + 8]);
				Vec3 norm = calculateNormal(vertA, vertB, vertC);

				tCounter = 0;
				for (int i = 0; i < 3; i++)
				{
					normals[normal_index + tCounter] = norm.getX();
					normals[normal_index + tCounter + 1] = norm.getY();
					normals[normal_index + tCounter + 2] = norm.getZ();
					tCounter += 3;
				}
				//Jump by 9 for each triangle i.e. 3 points per vertex, 3 vertices per triangle
				triangle_index += 9;		
				normal_index += 9;
				totalTriangles += 9;
			}
		}
		// Close OBJ file
		myOBJFile.close();		
	}
	else
	{
		std::cout << "Unable to open file";
	}
	return 0;
}

void MyModel::drawModel()
{
	// Enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	// Enable normal arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	// Vertex Pointer to triangle array
	glVertexPointer(3, GL_FLOAT, 0, faces);
	// Normal pointer to normal array
	glNormalPointer(GL_FLOAT, 0, normals);
	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, totalTriangles);
	// Disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	// Disable normal arrays
	glDisableClientState(GL_NORMAL_ARRAY);
}

void MyModel::deleteModel()
{
	free(faces);
	free(normals);
	free(vertexBuffer);
}

Vec3 MyModel::calculateNormal(Vec3 vertA, Vec3 vertB, Vec3 vertC)
{
	//calculate Vector1 and Vector2 
	Vec3 v1(vertA.getX() - vertB.getX(),
		vertA.getY() - vertB.getY(),
		vertA.getZ() - vertB.getZ());
	Vec3 v2(vertA.getX() - vertC.getX(),
		vertA.getY() - vertC.getY(),
		vertA.getZ() - vertC.getZ());
	return v1.crossProduct(v2);
}

MyModel model;
float rotation;
MyGlutWindow win;

/*PROGRAM*/

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
	glPushMatrix();
	glRotatef(rotation, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	rotation++;
	model.drawModel();
	glPopMatrix();
	glutSwapBuffers();
}


void initialize()
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, win.width, win.height);
	GLfloat aspect = (GLfloat)win.width / win.height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(win.fov_angle, aspect, win.clip_near, win.clip_far);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.1f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat amb_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat specular[] = { 0.7f, 0.7f, 0.3f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_ESCAPE:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	// set window values
	win.width = 720;
	win.height = 560;
	win.title = "Sami's OBJ Loader";
	win.fov_angle = 45;
	win.clip_near = 1.0f;
	win.clip_far = 5000.0f;

	// initialize and run program
	glutInit(&argc, argv);                                    
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(win.width, win.height);					
	glutCreateWindow(win.title);								
	glutDisplayFunc(display);								
	glutIdleFunc(display);									
	glutKeyboardFunc(keyboard);								
	initialize();
	model.loadModel("Models/icosahedron.obj");
	glutMainLoop();												
	return 0;
}