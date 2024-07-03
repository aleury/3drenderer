#ifndef MESH_H
#define MESH_H

#include "triangle.h"
#include "vector.h"

// Vertices of a cube
#define N_MESH_VERTICES 8
extern vec3_t mesh_vertices[N_MESH_VERTICES];

// Triangles of a cube
#define N_MESH_FACES (6 * 2) /* 6 faces, 2 triangles per face */
extern face_t mesh_faces[N_MESH_FACES];

#endif
