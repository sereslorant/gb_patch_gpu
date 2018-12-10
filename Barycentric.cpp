
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <string>
#include <cstring>

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLMAPBUFFERPROC glMapBuffer;
PFNGLUNMAPBUFFERPROC glUnmapBuffer;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat;
PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding;
PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer;

PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLDELETESHADERPROC glDeleteShader;

PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram;

PFNGLPATCHPARAMETERIPROC glPatchParameteri;

void GLLoadExtensions()
{
    glGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");
    glBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");
    glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)SDL_GL_GetProcAddress("glBindBufferRange");
    glBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");
    glMapBuffer = (PFNGLMAPBUFFERPROC)SDL_GL_GetProcAddress("glMapBuffer");
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)SDL_GL_GetProcAddress("glUnmapBuffer");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)SDL_GL_GetProcAddress("glDeleteBuffers");
    
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glGenVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)SDL_GL_GetProcAddress("glBindVertexArray");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glDeleteVertexArrays");
    
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
    glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)SDL_GL_GetProcAddress("glVertexAttribFormat");
    glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)SDL_GL_GetProcAddress("glVertexAttribBinding");
    glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)SDL_GL_GetProcAddress("glBindVertexBuffer");
    
    glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)SDL_GL_GetProcAddress("glDrawElementsBaseVertex");
    
    glCreateShader	= (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
    glShaderSource	= (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
    glCompileShader	= (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
    glDeleteShader	= (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
    
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
    glDetachShader = (PFNGLDETACHSHADERPROC)SDL_GL_GetProcAddress("glDetachShader");
    glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
    
    glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)SDL_GL_GetProcAddress("glPatchParameteri");
}

PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB;

PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

void GLDbgLoadExtensions()
{
    glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)SDL_GL_GetProcAddress("glGetObjectParameterivARB");
    glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)SDL_GL_GetProcAddress("glGetInfoLogARB");
    
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
}

#include <iostream>

void lGLDbgPrintShaderCompileError(GLuint shader)
{
    GLint compiled;
    
    glGetObjectParameterivARB(shader,GL_COMPILE_STATUS,&compiled);
    if(!compiled)
    {
        GLint ret_size;
        char log[256];
        glGetInfoLogARB(shader,sizeof(log),&ret_size,log);
        
        std::cerr << log << std::endl;
    }
}

void lGLDbgPrintProgramLinkError(GLuint program)
{
    GLint linked;
    
    glGetProgramiv(program,GL_LINK_STATUS,&linked);
    if(!linked)
    {
        GLint ret_size;
        char log[256];
        glGetProgramInfoLog(program,sizeof(log),&ret_size,log);
        
        std::cerr << log << std::endl;
    }
}

std::string VertexShaderSrc   = R"(
    #version 400
    
    
    void main()
    {
        
    }
)";

std::string TcShaderSrc = R"(
    #version 400
    
    layout(vertices = 3) out;
    
    void main()
    {
        gl_TessLevelOuter[0] = 8.0;
        gl_TessLevelOuter[1] = 8.0;
        gl_TessLevelOuter[2] = 8.0;
        
        gl_TessLevelInner[0] = 8.0;
    }
)";

std::string TeShaderSrc = R"(
    #version 400
    
    layout(triangles,equal_spacing,ccw) in;
    
    const uint MAX_SIDE_COUNT = 5;
    
    out vec3 OutColor;
    
    
    
    void main()
    {
        const uint  SIDE_COUNT = 5;
        const float PI         = 3.14159265359;
        const float EPSILON    = 1e-2;
        
        uint VertexId0 = (gl_PrimitiveID       % SIDE_COUNT);
        uint VertexId1 = ((gl_PrimitiveID + 1) % SIDE_COUNT);
        
        vec3 Vertices[MAX_SIDE_COUNT];
        for(uint i=0;i < SIDE_COUNT;i++)
        {
            float SinParam = float(i)/ SIDE_COUNT;
            Vertices[i] = vec3(cos(SinParam * 2.0 * PI),sin(SinParam * 2.0 * PI),0.0);
        }
        
        vec3 UvCoord = gl_TessCoord.y * Vertices[VertexId0] + gl_TessCoord.z * Vertices[VertexId1];
        
        float SumBaryCoords = 0.0;
        float BaryCoords[MAX_SIDE_COUNT];
        for(uint i=0;i < SIDE_COUNT;i++)
        {
            uint Prev = (i-1);
            uint Curr = i;
            uint Next = (i+1) % SIDE_COUNT;
            
            if(i == 0)
                {Prev = SIDE_COUNT - 1;}
            
            float A1 = length(cross(Vertices[Curr] - UvCoord,Vertices[Prev] - UvCoord))/2.0;
            float A2 = length(cross(Vertices[Curr] - UvCoord,Vertices[Next] - UvCoord))/2.0;
            
            float C  = length(cross(Vertices[Prev] - Vertices[Curr],Vertices[Next] - Vertices[Curr]))/2.0;
            
            BaryCoords[i] = C/(A1*A2);
            
            SumBaryCoords += BaryCoords[i];
        }
        
        float BaryNorm = 1.0/SumBaryCoords;
        if(gl_TessCoord.x < EPSILON)
            {BaryNorm = 0.0;}
                
        for(uint i=0;i < SIDE_COUNT;i++)
        {
            BaryCoords[i] *= BaryNorm;
        }
        
        if(gl_TessCoord.x < EPSILON)
        {
            BaryCoords[VertexId0] = gl_TessCoord.y;
            BaryCoords[VertexId1] = gl_TessCoord.z;
        }
        
        
        OutColor = vec3(BaryCoords[0],BaryCoords[1],BaryCoords[2]);
        //OutColor = vec3(BaryCoords[1],BaryCoords[2],BaryCoords[3]);
        //OutColor = vec3(BaryCoords[2],BaryCoords[3],BaryCoords[4]);
        //OutColor = vec3(BaryCoords[3],BaryCoords[4],BaryCoords[0]);
        
        gl_Position = vec4(UvCoord,1.0);
    }
)";

std::string FragmentShaderSrc = R"(
    #version 400
    
    in vec3 OutColor;
    
    layout(location=0) out vec4 FragColor; 
    
    void main()
    {
        FragColor = vec4(OutColor,1.0);
    }
)";

class GLApp
{
private:
    GLuint VertexArrayObject = 0;
    
    GLuint ShaderProgram = 0;
    
public:

    void Loop()
    {
        glClearColor(0.5,0.5,0.5,1.0);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        
        glUseProgram(ShaderProgram);
        glBindVertexArray(VertexArrayObject);
        
        glPatchParameteri(GL_PATCH_VERTICES,3);
        glDrawArrays(GL_PATCHES,0,15);
    }
    
    GLApp()
    {
        std::cout << VertexShaderSrc << std::endl;
        std::cout << TcShaderSrc << std::endl;
        std::cout << TeShaderSrc << std::endl;
        std::cout << FragmentShaderSrc << std::endl;
        
        GLLoadExtensions();
        GLDbgLoadExtensions();
        
        {
            const char *ShaderSource = VertexShaderSrc.c_str();
            GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(VertexShader,1,&ShaderSource,nullptr);
            glCompileShader(VertexShader);
            
            lGLDbgPrintShaderCompileError(VertexShader);
            
            ShaderSource = TcShaderSrc.c_str();
            GLuint TcShader = glCreateShader(GL_TESS_CONTROL_SHADER);
            glShaderSource(TcShader,1,&ShaderSource,nullptr);
            glCompileShader(TcShader);
            
            lGLDbgPrintShaderCompileError(TcShader);
            
            ShaderSource = TeShaderSrc.c_str();
            GLuint TeShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
            glShaderSource(TeShader,1,&ShaderSource,nullptr);
            glCompileShader(TeShader);
            
            lGLDbgPrintShaderCompileError(TeShader);
            
            ShaderSource = FragmentShaderSrc.c_str();
            GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(FragmentShader,1,&ShaderSource,nullptr);
            glCompileShader(FragmentShader);
            
            lGLDbgPrintShaderCompileError(FragmentShader);
            
            ShaderProgram = glCreateProgram();
            
            glAttachShader(ShaderProgram,VertexShader);
            glAttachShader(ShaderProgram,TcShader);
            glAttachShader(ShaderProgram,TeShader);
            glAttachShader(ShaderProgram,FragmentShader);
            
            glLinkProgram(ShaderProgram);
            
            glDetachShader(ShaderProgram,VertexShader);
            glAttachShader(ShaderProgram,TcShader);
            glAttachShader(ShaderProgram,TeShader);
            glDetachShader(ShaderProgram,FragmentShader);
            
            lGLDbgPrintProgramLinkError(ShaderProgram);
            
            glDeleteShader(VertexShader);
            glDeleteShader(TcShader);
            glDeleteShader(TeShader);
            glDeleteShader(FragmentShader);
        }
        
        glGenVertexArrays(1,&VertexArrayObject);
    }
    
    ~GLApp()
    {
        glDeleteVertexArrays(1,&VertexArrayObject);
        glDeleteProgram(ShaderProgram);
    }
};

int main(int argc, char **argv)
{
    SDL_Window *Window;
    SDL_GLContext GLContext;
    
    SDL_Init(SDL_INIT_EVERYTHING);
        
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    
    Window = SDL_CreateWindow("GLRenderSample",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,600,SDL_WINDOW_OPENGL);
    GLContext = SDL_GL_CreateContext(Window);
    
    SDL_ShowWindow(Window);
    
    GLApp App;
    
    bool Running = true;
    while(Running)
    {
        int BeginTime = SDL_GetTicks();
        
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                Running = false;
            }
        }
        
        App.Loop();
        
        SDL_GL_SwapWindow(Window);
        
        int EndTime = SDL_GetTicks();
        std::cout << "Frame time: " << (EndTime-BeginTime) << "ms\nFps: " << 1000.0/(EndTime-BeginTime) << std::endl;
    }
    
    SDL_GL_DeleteContext(GLContext);
    SDL_DestroyWindow(Window);
    
    SDL_Quit();
        
    return 0;
}
