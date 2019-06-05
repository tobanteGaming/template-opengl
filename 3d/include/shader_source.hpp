#pragma once

namespace tobanteGaming
{
constexpr char* VERTEX_SHADER_SRC = R"(
    #version 430

    in vec3 position;

    out vec3 colour;

    void main(void){

        gl_Position = vec4(position,1.0);
        colour = vec3(position.x+0.5,0.0,position.y+0.5);
    }
)";

constexpr char* FRAGMENT_SHADER_SRC = R"(
    #version 430

    in vec3 colour;

    out vec4 out_Color;

    void main(void){

        out_Color = vec4(colour,1.0);

    }
)";

}