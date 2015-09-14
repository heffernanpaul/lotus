#include "sphere.h"

#include <math.h>
#include <vector>
#include <glm/gtc/constants.hpp>
#include <iomanip>

Sphere::Sphere(GLfloat radius, glm::vec3 positionIn, int rings, int sectors, GLuint texture,
	const GLuint shader) : 
		Node(positionIn, texture, shader), radius(radius){

    std::vector<GLfloat> sphere_vertices;
    std::vector<GLfloat> sphere_normals;
    std::vector<GLfloat> sphere_texcoords;
    std::vector<GLushort> sphere_indices;

    GLfloat const R = 1./(float)(rings);
        GLfloat const S = 1./(float)(sectors);
        int r, s;

        sphere_vertices.resize(rings * sectors * 3);
        sphere_normals.resize(rings * sectors * 3);
        sphere_texcoords.resize(rings * sectors * 2);
        std::vector<GLfloat>::iterator v = sphere_vertices.begin();
        std::vector<GLfloat>::iterator n = sphere_normals.begin();
        std::vector<GLfloat>::iterator t = sphere_texcoords.begin();

    // std::vector<GLfloat> points;
    // points.resize(rings * sectors * 6 * 5);
    // std::vector<GLfloat>::iterator p = points.begin();
    GLfloat points[rings * sectors * 6 * 5];
    GLfloat* p = points;
        for(r = 0; r < rings; r++) {
            for(s = 0; s < sectors; s++) {
            
                GLfloat const y1 = cos(M_PI * r * R );
                GLfloat const y2 = cos(M_PI * (r+1) * R );
                GLfloat const x1 = -cos(2*M_PI * s * S) * sin( M_PI * r * R );
                GLfloat const z1 = sin(2*M_PI * s * S) * sin( M_PI * r * R );

                GLfloat const x2 = -cos(2*M_PI * (s+1) * S) * sin( M_PI * r * R );
                GLfloat const z2 = sin(2*M_PI * (s+1) * S) * sin( M_PI * r * R );

                GLfloat const x3 = -cos(2*M_PI * (s+1) * S) * sin( M_PI * (r+1) * R );
                GLfloat const z3 = sin(2*M_PI * (s+1) * S) * sin( M_PI * (r+1) * R );

                GLfloat const x4 = -cos(2*M_PI * s * S) * sin( M_PI * (r+1) * R );
                GLfloat const z4 = sin(2*M_PI * s * S) * sin( M_PI * (r+1) * R );


//        std::cout << std::setprecision(1) <<"Vertex:["<< r <<", " << s << "] " << x << ", " << y << ", " << z << std::endl;

                GLfloat s1 = s*S;
                GLfloat t1 = r*R;

                GLfloat s2 = (s+1)*S;
                GLfloat t2 = r*R;

                GLfloat s3 = (s+1)*S;
                GLfloat t3 = (r+1)*R;

                GLfloat s4 = s*S;
                GLfloat t4 = (r+1)*R;

        // std::cout << std::setprecision(1) <<"Vertex:["<< r <<", " << s << "] " << x1 << ", " << y1 << ", " << z1  << " [" << s1 << "," << t1 << "]" << std::endl;
        // std::cout << std::setprecision(1) <<"Vertex:["<< r <<", " << s << "] " << x2 << ", " << y1 << ", " << z2  << " [" << s2 << "," << t2 << "]" << std::endl;
        // std::cout << std::setprecision(1) <<"Vertex:["<< r <<", " << s << "] " << x3 << ", " << y2 << ", " << z3  << " [" << s3 << "," << t3 << "]" << std::endl;
        // std::cout << std::endl;
        // std::cout << std::setprecision(1) <<"Vertex:["<< r <<", " << s << "] " << x1 << ", " << y1 << ", " << z1  << " [" << s1 << "," << t1 << "]" << std::endl;
        // std::cout << std::setprecision(1) <<"Vertex:["<< r <<", " << s << "] " << x3 << ", " << y2 << ", " << z3  << " [" << s3 << "," << t3 << "]" << std::endl;
        // std::cout << std::setprecision(1) <<"Vertex:["<< r <<", " << s << "] " << x4 << ", " << y2 << ", " << z4  << " [" << s4 << "," << t4 << "]" << std::endl;
        // std::cout << std::endl;

                *p++ = x1 * radius;
                *p++ = y1 * radius;
                *p++ = z1 * radius;
                *p++ = s1;
                *p++ = t1;

                *p++ = x2 * radius;
                *p++ = y1 * radius;
                *p++ = z2 * radius;
                *p++ = s2;
                *p++ = t2;

                *p++ = x3 * radius;
                *p++ = y2 * radius;
                *p++ = z3 * radius;
                *p++ = s3;
                *p++ = t3;

                *p++ = x1 * radius;
                *p++ = y1 * radius;
                *p++ = z1 * radius;
                *p++ = s1;
                *p++ = t1;

                *p++ = x3 * radius;
                *p++ = y2 * radius;
                *p++ = z3 * radius;
                *p++ = s3;
                *p++ = t3;

                *p++ = x4 * radius;
                *p++ = y2 * radius;
                *p++ = z4 * radius;
                *p++ = s4;
                *p++ = t4;


                // *v++ = x * radius;
                // *v++ = y * radius;
                // *v++ = z * radius;

                // *n++ = x;
                // *n++ = y;
                // *n++ = z;
            }
        }

        // sphere_indices.resize(rings * sectors * 4);
        // std::vector<GLushort>::iterator i = sphere_indices.begin();
        // for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
        //         *i++ = r * sectors + s;
        //         *i++ = r * sectors + (s+1);
        //         *i++ = (r+1) * sectors + (s+1);
        //         *i++ = (r+1) * sectors + s;
        // }

    // std::vector<GLfloat> points;
    // points.resize((rings+1) * (sectors+1) * 6 * 5);
    // std::vector<GLfloat>::iterator p = points.begin();

    // for (GLushort index : sphere_indices) {

    //     std::cout << "Vertex:["<< index <<"] " << sphere_vertices[(index*3)+0] << ", " << sphere_vertices[(index*3)+0] << ", " << sphere_vertices[(index*3)+0] << std::endl;
    //     *p++ = sphere_vertices[(index*3)+0];
    //     *p++ = sphere_vertices[(index*3)+1];
    //     *p++ = sphere_vertices[(index*3)+2];

    //     *p++ = sphere_texcoords[(index*2)+0];
    //     *p++ = sphere_texcoords[(index*2)+1];

    // }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    std::cout << "Size of points = " << sizeof(points) << std::endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArray(0);
    numVertices = rings * sectors * 6;

}

void Sphere::draw() {

    Node::draw();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);  

}