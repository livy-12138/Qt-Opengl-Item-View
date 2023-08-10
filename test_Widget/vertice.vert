#version 330 core
layout(location = 0) in vec3 aPos;
out vec4 vertexColor;
uniform mat4 theMatrix;
void main(){
    gl_Position =  theMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);

}