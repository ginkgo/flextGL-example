#include "mesh.hpp"

GLint grid_index_count(int w, int h)
{
    return w*h + w*(h-2) + 2*(h-2);
}

#define GRIDPOS(x,y) ((y)*w+(x)+offset)

void create_grid_indices(GLuint* dst, int w, int h, GLuint offset=0)
{
    int i = 0;

    for (int y = 0; y < h-1; ++y) {
        if (y > 0) {
            dst[i] = GRIDPOS(w-1,y-1); ++i;
            dst[i] = GRIDPOS(0,y+1);   ++i;
        }

        for (int x = 0; x < w; ++x) {
            dst[i] = GRIDPOS(x,y+1); ++i;
            dst[i] = GRIDPOS(x,y);   ++i;
        }
    }

    assert(i == grid_index_count(w,h));
}


void create_donut(Mesh& mesh, float r1, float r2, int s1, int s2)
{
    mesh.primitive_type = GL_TRIANGLE_STRIP;
    mesh.vertex_count = (s1+1)*(s2+1);
    mesh.index_count =  grid_index_count(s2+1, s1+1);

    mesh.vertices = new vec4[mesh.vertex_count];
    mesh.colors   = new vec4[mesh.vertex_count];
    mesh.normals  = new vec3[mesh.vertex_count];

    mesh.indices  = new GLuint[mesh.index_count];

    for (int i = 0; i <= s1; ++i) {
        double outer = (double)i/s1 * 2*M_PI;

        vec3 dir1 = vec3(sin(outer),cos(outer),0);
        vec3 dir2 = vec3(0,0,1);

        // vec3 tangent = cross(dir1,dir2);

        vec3 pos = r1 * dir1;

        for (int j = 0; j <= s2; ++j) {
            double inner = ((double)j/s2)*2*M_PI;

            vec3 normal = (float)cos(inner)*dir1 + (float)sin(inner)*dir2;

            mesh.vertices[i*(s2+1)+j] = vec4(r2 * normal + pos,1);
            mesh.normals[i*(s2+1)+j] = normal;
            // mesh.tangents[i*(s2+1)+j] = tangent;


            mesh.colors[i*(s2+1)+j] = vec4(glm::rgbColor(vec3(outer/(2*M_PI)*360, 1, 1)),1);
        }
    }

    create_grid_indices(mesh.indices, s2+1, s1+1);
}
