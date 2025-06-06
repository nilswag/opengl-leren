#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float positions[6] = 
{
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
};

static std::string read_file(const std::string& path)
{
    std::ifstream file("src/resources/" + path);
    if (!file.is_open())
    {
        std::cerr << "failed to open file: " << path << std::endl;
        return "";
    }
    std::string content;
    std::string line;
    while (std::getline(file, line)) content += line + '\n';
    return content;
}

static unsigned int compile_shader(const std::string& shader_src, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = shader_src.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char log[512];
        glGetShaderInfoLog(id, length, &length, log);
        std::cerr << "failed to compile shader: " << shader_src << "\n" << log;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int create_shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    unsigned int program = glCreateProgram();
    unsigned int vertex_shader = compile_shader(read_file(vertex_shader_path), GL_VERTEX_SHADER);
    unsigned int fragment_shader = compile_shader(read_file(fragment_shader_path), GL_FRAGMENT_SHADER);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    glValidateProgram(program);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

int main(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwInit()) std::cerr << "failed to initialize glfw" << std::endl;
    
    GLFWwindow* window = nullptr;
    window = glfwCreateWindow(1280, 720, "testing", nullptr, nullptr);
    if (window == nullptr) std::cerr << "failed to create glfw window" << std::endl;

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cerr << "failed to initialize glad" << std::endl;

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);

    unsigned int shader = create_shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }

    glDeleteShader(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}