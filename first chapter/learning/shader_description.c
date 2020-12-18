//MY CONSPECT

//********STRUCTURE***********

#version version_number //always starts with shader version

//list of in variables
in type in_variable_name;
//{...}
//list of out variables
out type out_variable_name;
//{...}
// global variables 
uniform type uniform_name;

//start of shader
//we take in variables, do something and sent results to the out variables
void main()
{
	//something
	//{...}
	out_variable_name = weird_stuff_we_processed;
}

//********TYPE***********
int
float
double
uint
bool
vector 
matrix

//********VECTOR***********
vec3 //vector with 3 floats
bvec2// vector with two booleans
ivec1// vector with 1 integer
uvec2// vector with 2 unsigned integer
dvec4// vector with 4 double
vec.x vec.y vec.z vec.w 

//we can have not onle one value 
vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;

//creation of vector
vec2 vect = vec2(0.5f, 0.7f);
vec4 result = vec4(vect, 0.0f, 0.0f);
vec4 otherResult = vec4(result.xyz, 1.0f);

//********IN AND OUT VALUES***********
 layout (location = 0)// it means that we start from 0 in VAO
 //the fragment shader must return vec4. It means it must return RGBA color.
 // without that we will draw only black or only white color
 //if we want to send information from one shader to another (for example fro, first 
 // to second). We must have in first shader out value with the same name and type
 //as the in value in second shader
 //EXAMPLE
//Vertex shader
#version 330 core
layout (location = 0) in vec3 position; // Устанавливаем позицию атрибута в 0

out vec4 vertexColor; // Передаем цвет во фрагментный шейдер

void main()
{
    gl_Position = vec4(position, 1.0); // Напрямую передаем vec3 в vec4
    vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f); // Устанавливаем значение выходной переменной в темно-красный цвет.
}
//Fragment shader
#version 330 core
in vec4 vertexColor; // Входная переменная из вершинного шейдера (то же название и тот же тип)

out vec4 color;

void main()
{
    color = vertexColor;
} 
//We have made two conected shaders

//********UNIFORMS***********
//Global values are unique for every shader. Forms are saved until it will not be reset or updated
// If we want to update form, we must use value uniform.
//EXAMPLE
#version 330 core
out vec4 color;

uniform vec4 ourColor; // Мы устанавливаем значение этой переменной в коде OpenGL.

void main()
{
    color = ourColor;
}
//forms are global, so we can initialize them in any shader we want.
//if we initialize form, but we dont use it compoliter will delete it automatically.
//That can cause errors. Be carefull!
//EXAMPLE
GLfloat timeValue = glfwGetTime();//we get time in seconds
GLfloat greenValue = (sin(timeValue) / 2) + 0.5;//with sin we change value from 0.0 to 1.0
GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//we get index of "OurColor" form
// if glGetUniformLocation returmt -1 it means that there is no form with such name
glUseProgram(shaderProgram);//call this function before initialization of "ourColor"
glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//four arguments of float type

//********Peace of Program***********
while(!glfwWindowShouldClose(window))
{
    // Обрабатываем события
    glfwPollEvents();

    // Отрисовка
    // Очищаем буфер цвета
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Активируем шейдерную программу
    glUseProgram(shaderProgram);

    // Обновляем цвет формы
    GLfloat timeValue = glfwGetTime();
    GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // Рисуем треугольник
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}