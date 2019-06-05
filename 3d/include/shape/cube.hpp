#pragma once

#include <GL/glew.h>

namespace tobanteGaming
{
// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive
// vertices give a triangle. A cube has 6 faces with 2 triangles each, so this
// makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f,  // triangle 1 : begin //
    -1.0f, -1.0f, 1.0f,   //
    -1.0f, 1.0f,  1.0f,   // triangle 1 : end //
    1.0f,  1.0f,  -1.0f,  // triangle 2 : begin //
    -1.0f, -1.0f, -1.0f,  //
    -1.0f, 1.0f,  -1.0f,  // triangle 2 : end //
    1.0f,  -1.0f, 1.0f,   //
    -1.0f, -1.0f, -1.0f,  //
    1.0f,  -1.0f, -1.0f,  //
    1.0f,  1.0f,  -1.0f,  //
    1.0f,  -1.0f, -1.0f,  //
    -1.0f, -1.0f, -1.0f,  //
    -1.0f, -1.0f, -1.0f,  //
    -1.0f, 1.0f,  1.0f,   //
    -1.0f, 1.0f,  -1.0f,  //
    1.0f,  -1.0f, 1.0f,   //
    -1.0f, -1.0f, 1.0f,   //
    -1.0f, -1.0f, -1.0f,  //
    -1.0f, 1.0f,  1.0f,   //
    -1.0f, -1.0f, 1.0f,   //
    1.0f,  -1.0f, 1.0f,   //
    1.0f,  1.0f,  1.0f,   //
    1.0f,  -1.0f, -1.0f,  //
    1.0f,  1.0f,  -1.0f,  //
    1.0f,  -1.0f, -1.0f,  //
    1.0f,  1.0f,  1.0f,   //
    1.0f,  -1.0f, 1.0f,   //
    1.0f,  1.0f,  1.0f,   //
    1.0f,  1.0f,  -1.0f,  //
    -1.0f, 1.0f,  -1.0f,  //
    1.0f,  1.0f,  1.0f,   //
    -1.0f, 1.0f,  -1.0f,  //
    -1.0f, 1.0f,  1.0f,   //
    1.0f,  1.0f,  1.0f,   //
    -1.0f, 1.0f,  1.0f,   //
    1.0f,  -1.0f, 1.0f    //
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.583f, 0.771f, 0.014f,  //
    0.609f, 0.115f, 0.436f,  //
    0.327f, 0.483f, 0.844f,  //
    0.822f, 0.569f, 0.201f,  //
    0.435f, 0.602f, 0.223f,  //
    0.310f, 0.747f, 0.185f,  //
    0.597f, 0.770f, 0.761f,  //
    0.559f, 0.436f, 0.730f,  //
    0.359f, 0.583f, 0.152f,  //
    0.483f, 0.596f, 0.789f,  //
    0.559f, 0.861f, 0.639f,  //
    0.195f, 0.548f, 0.859f,  //
    0.014f, 0.184f, 0.576f,  //
    0.771f, 0.328f, 0.970f,  //
    0.406f, 0.615f, 0.116f,  //
    0.676f, 0.977f, 0.133f,  //
    0.971f, 0.572f, 0.833f,  //
    0.140f, 0.616f, 0.489f,  //
    0.997f, 0.513f, 0.064f,  //
    0.945f, 0.719f, 0.592f,  //
    0.543f, 0.021f, 0.978f,  //
    0.279f, 0.317f, 0.505f,  //
    0.167f, 0.620f, 0.077f,  //
    0.347f, 0.857f, 0.137f,  //
    0.055f, 0.953f, 0.042f,  //
    0.714f, 0.505f, 0.345f,  //
    0.783f, 0.290f, 0.734f,  //
    0.722f, 0.645f, 0.174f,  //
    0.302f, 0.455f, 0.848f,  //
    0.225f, 0.587f, 0.040f,  //
    0.517f, 0.713f, 0.338f,  //
    0.053f, 0.959f, 0.120f,  //
    0.393f, 0.621f, 0.362f,  //
    0.673f, 0.211f, 0.457f,  //
    0.820f, 0.883f, 0.371f,  //
    0.982f, 0.099f, 0.879f   //
};

class Cube
{
public:
    Cube()
    {
        GLuint VBO;
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex
        // buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                     g_vertex_buffer_data, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer
        // registered VBO as the vertex attribute's bound vertex buffer object
        // so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // remember: do NOT unbind the EBO while a VAO is active as the bound
        // element buffer object IS stored in the VAO; keep the EBO bound.
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't
        // accidentally modify this VAO, but this rarely happens. Modifying
        // other VAOs requires a call to glBindVertexArray anyways so we
        // generally don't unbind VAOs (nor VBOs) when it's not directly
        // necessary.
        glBindVertexArray(0);
    }
    GLuint getVAO() { return m_vao; }

    void render()
    {
        glBindVertexArray(m_vao);
        // 12*3 indices starting at 0 ->12 triangles -> 6 squares
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
        // glDisableVertexAttribArray(0);
    }

private:
    GLuint m_vao;
};
}  // namespace tobanteGaming