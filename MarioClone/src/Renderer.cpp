#include "Renderer.h"

Renderer::Renderer(GameObject& go)
    :object(go)
{
    // create our compiled shaders
    vertShader = LoadShader(std::string("src/shaders/vert/VertexShader.vert"), GL_VERTEX_SHADER);
    fragShader = LoadShader(std::string("src/shaders/frag/FragmentShader.frag"), GL_FRAGMENT_SHADER);

    // then create a shader program, and attach the vertex shader to it
    shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertShader);

    // set the colour of the back buffer to whatever colourOut is (in our vertex shader), then attach the fragment shader to it
    glBindFragDataLocation(shaderProg, 0, "colourOut");
    glAttachShader(shaderProg, fragShader);

    // link the shaders in the program together, then check to make sure the linking was successful
    glLinkProgram(shaderProg);
    CheckLinkSuccess(shaderProg);
    
    // we've made the program and linked it, which means we're free to remove our individual shaders from memory
    glDetachShader(shaderProg, vertShader);
    glDetachShader(shaderProg, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    // and now we can tell OpenGL to start using our shader program
    glUseProgram(shaderProg);

    // creates a vertex array object, which essentially tells us how data should be read, what format it is, etc. - hence triangleSettings rather than triangleVAO
    glGenVertexArrays(1, &triangleSettings);
    glBindVertexArray(triangleSettings);

    // the actual vertex data - first 3 bytes are xyz positional data, last 3 bytes are rgb colour values, both normalised
    float triangleData[] = { -0.4, -0.4, 0, 0.0, 0.0, 1.0,
                             -0.4,  0.3, 0, 0.0, 0.0, 1.0,
                              0.2, -0.5, 0, 0.0, 0.0, 1.0,
                              0.2,  0.2, 0, 0.0, 0.0, 1.0,
                             -0.4,  0.3, 0, 0.0, 0.0, 1.0,
                              0.2, -0.5, 0, 0.0, 0.0, 1.0,
                              0.6,  0.4, 0, 1.0, 0.0, 0.0,
                              0.2,  0.25, 0, 1.0, 0.0, 0.0,
                              0.6, -0.25, 0, 1.0, 0.0, 0.0,
                              0.2, -0.5, 0, 1.0, 0.0, 0.0,
                              0.2,  0.25, 0, 1.0, 0.0, 0.0,
                              0.6, -0.25, 0, 1.0, 0.0, 0.0,
                             -0.4,  0.3, 0, 0.0, 1.0, 0.0,
                              0.2,  0.2, 0, 0.0, 1.0, 0.0,
                              0.6,  0.4, 0, 0.0, 1.0, 0.0,
                             -0.4,  0.3, 0, 0.0, 1.0, 0.0,
                              0.0,  0.5, 0, 0.0, 1.0, 0.0,
                              0.6,  0.4, 0, 0.0, 1.0, 0.0 };

    // creates a vertex buffer object, tells OpenGL that this is the buffer we're using, then loads the triangle data into the buffer
    glGenBuffers(1, &triangleBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

    // gets a handle to the vertexPos attribute, then reads from triangleBuffer the first three floats of the six from a given vertex of triangleData
    GLint vertexPosAttribute = glGetAttribLocation(shaderProg, "vertexPos");
    glVertexAttribPointer(vertexPosAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vertexPosAttribute);

    // same as above, just offset by 3 floats - where the colour values are in triangleData
    GLint colourInAttribute = glGetAttribLocation(shaderProg, "colourIn");
    glVertexAttribPointer(colourInAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(colourInAttribute);
}

void Renderer::Render(SDL_Window* win)
{
    // clear screen and colour background
    glClearColor(object.backgroundColour[0], object.backgroundColour[1], object.backgroundColour[2], object.backgroundColour[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw the triangle we set up
    glDrawArrays(GL_TRIANGLES, 0, 18);

    // execute all previously given instructions
    glFlush();

    // swap draw buffer with view buffer
    SDL_GL_SwapWindow(win);
}

GLuint Renderer::LoadShader(std::string fileLocation, GLenum shaderType)
{
    // grab the shader code from the location given, and put it into an array of GLchars
    std::ifstream shaderFile(fileLocation);
    if (!shaderFile) { std::cout << "Invalid file location: " << fileLocation << std::endl; }

    std::string fileContents = std::string((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
    const GLchar* shaderCode = fileContents.c_str();

    // create a shader, give it the shader code, then compile it
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    // check to make sure it compiled correctly, and if it didn't, print an error to the console
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        std::cout << "Error compiling shader at: " << fileLocation << std::endl;
        char buffer[512];
        glGetShaderInfoLog(shader, 512, nullptr, buffer);
        std::cout << buffer << std::endl;
    }

    return shader;
}

void Renderer::CheckLinkSuccess(GLuint& shaderProgram)
{
    GLint linkStatus;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE)
    {
        std::cout << "Error linking shader in Renderer constructor" << std::endl;
        char buffer[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, buffer);
        std::cout << buffer << std::endl;
    }
}
