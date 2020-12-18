//*******Texture Coordinates*******
GLfloat texCoords[] = {
    0.0f, 0.0f,  // Нижний левый угол 
    1.0f, 0.0f,  // Нижний правый угол
    0.5f, 1.0f   // Верхняя центральная сторона
};

//*******Texture Wrapping*******
GL_REPEAT //repeats texture
GL_MIRRORED_REPEAT // mirrors the image with each repeat.
GL_CLAMP_TP_EDGE //higher coordinates become clamped to the edge, resulting in a stretched edge pattern
GL_CLAMP_TO_BORDER //Coordinates outside the range are now given a user-specified border color
//Each of the aforementioned options can be set per coordinates s and t (equal to x and y)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//if we want to set GL_CLAMP_TO_BORDER we use
float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

//*******Texture Filtering*******
GL_NEAREST //OpenGL selects the texel that center is closest to the texture coordinate
GL_LINEAR //(also known as (bi)linear filtering) takes an interpolated value from the texture coordinate's neighboring texels, 
//approximating a color between the texels. The smaller the distance from the texture coordinate to a texel's center, 
//the more that texel's color contributes to the sampled color

//*******Mipmaps*******
glGenerateMipmaps //generates mipmap

_GL_NEARESET_MIPMAPNEAREST //takes the nearest mipmap to match the pixel size 
//and uses nearest neighbor interpolation for texture sampling
_GL_LINEAR_MIPMAPNEAREST//takes the nearest mipmap level 
//and samples that level using linear interpolation. 
_GL_NEAREST_MIPMAPLINEAR // linearly interpolates between the two mipmaps that most closely match the size of a pixel 
//and samples the interpolated level via nearest neighbor interpolation
GL_LINEAR_MIPMAP_LINEAR //linearly interpolates between the two closest mipmaps 
//and samples the interpolated level via linear interpolation.

//setting filtering method
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

/////////////////SOIL/////////////////////
int width, height;
unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);

//*******Generating texture*******
GLuint texture;
glGenTextures(1, &texture); //first argument - the amount of textures

glBindTexture(GL_TEXTURE_2D, texture);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//second argument describes mipmap level
//third is the formate of final textutre
//sixth is always zero
//7th and 8th arguments are the formate of original image
//data of image
glGenerateMipmap(GL_TEXTURE_2D);
//free memory
SOIL_free_image_data(image);
glBindTexture(GL_TEXTURE_2D, 0);

//generating texture
GLuint texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
// Устанавливаем настройки фильтрации и преобразований (на текущей текстуре)
...
// Загружаем и генерируем текстуру
int width, height;
unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB); 
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
glGenerateMipmap(GL_TEXTURE_2D);
SOIL_free_image_data(image);
glBindTexture(GL_TEXTURE_2D, 0);

//*******Usage of texture*******

GLfloat vertices[] = {
    // Позиции          // Цвета             // Текстурные координаты
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Верхний правый
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Нижний правый
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Нижний левый
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Верхний левый
};

//we have new atributes
glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
glEnableVertexAttribArray(2);

//we must change vertex shader
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0f);
    ourColor = color;
    TexCoord = texCoord;
}

//we must change fragment shader
#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    color = texture(ourTexture, TexCoord);
}

//drawing
glBindTexture(GL_TEXTURE_2D, texture);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
glBindVertexArray(0);

//a couple of textures
glActiveTexture(GL_TEXTURE0);//activate texture unit before binding texture
glBindTexture(GL_TEXTURE_2D, texture);

//now we need to change fragment shader
#version 330 core
...

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}
//GLSL's built-in mix function takes two values as input and linearly interpolates between them based on its third argument. 
//If the third value is 0.0 it returns the first input; if it's 1.0 it returns the second input value. 
//A value of 0.2 will return 80% of the first input color and 20% of the second input color, resulting in a mixture of both our textures. 