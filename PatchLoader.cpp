
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "glmath.hpp"

float PI = 3.14159265359;

#include <vector>
#include <string>
#include <cstring>

#include <fstream>

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
    #version 420
    
    layout(location=0) in vec2 Position;
    
    layout(binding=0,std140) uniform MatrixBlock
    {
        mat4 MvpMatrix;
    };
    
    void main()
    {
        gl_Position = MvpMatrix * vec4(Position,0.0,1.0);
    }
)";

std::string FragmentShaderSrc = R"(
    #version 400
    
    layout(location=0) out vec4 FragColor; 
    
    void main()
    {
        FragColor = vec4(0.0,0.0,1.0,1.0);
    }
)";

struct GBPatch
{
    std::size_t SideCount;
    std::size_t Degree;
    std::size_t Layers;
    
    std::vector<vec4> ControlPointList;
    std::vector<vec4> PerSideCpArray;
    
    std::size_t GetLayerWidth()
    {
        return Degree + 1;
    }
    
    std::size_t GetLayerCpCount()
    {
        return Layers * GetLayerWidth();
    }
};

/*
 * Forrás: Salvi Péter
 * https://bitbucket.org/salvipeter/
 */
void LoadPatch(GBPatch &patch,const std::string &filename,std::size_t i)
{
    std::ifstream file(filename);
    
    if(file.is_open())
    {
        file >> patch.SideCount;
        file >> patch.Degree;
        
        patch.Layers = (patch.Degree + 1)/2;
        
        std::cout << "Side count: " << patch.SideCount << "\nDegree: " << patch.Degree << std::endl;
        
        patch.ControlPointList.resize(patch.SideCount * (1 + patch.Degree/2) * patch.Layers + 1);
        
        
        for(auto &ControlPoint : patch.ControlPointList)
        {
            file >> ControlPoint.v[0] >> ControlPoint.v[1] >> ControlPoint.v[2];
            
            // Egy kis postprocesszálás, mert néhány modell túl kicsi, néhány meg túl nagy.
            if(i > 3)
            {ControlPoint *= 50.0;}
            else if(i == 1)
            {ControlPoint *= 0.005;}
            else
            {ControlPoint *= 0.125;}
        }
        
        patch.PerSideCpArray.resize(patch.SideCount * patch.GetLayerCpCount() + 1);
        
        patch.PerSideCpArray[0] = patch.ControlPointList[0];
        for(std::size_t cpid = 1, side = 0, col = 0, row = 0; cpid < patch.ControlPointList.size(); ++cpid, ++col)
        {
            if(col >= patch.Degree - row)
            {
                if(++side >= patch.SideCount)
                {
                    side = 0;
                    ++row;
                }
                
                col = row;
            }
            
            patch.PerSideCpArray[1 + side * patch.GetLayerCpCount() + row * patch.GetLayerWidth() + col] = patch.ControlPointList[cpid];
            
            if(col < patch.Layers)
            {
                std::size_t prev = (side + patch.SideCount - 1) % patch.SideCount;
                std::size_t prev_col = patch.Degree - row;
                std::size_t prev_row = col;
                
                patch.PerSideCpArray[1 + prev * patch.GetLayerCpCount() + prev_row * patch.GetLayerWidth() + prev_col] = patch.ControlPointList[cpid];
            }
            else if(patch.Degree - col < patch.Layers)
            {
                std::size_t next = (side + 1) % patch.SideCount;
                std::size_t prev_row = patch.Degree - col;
                std::size_t prev_col = row;
                
                patch.PerSideCpArray[1 + next * patch.GetLayerCpCount() + prev_row * patch.GetLayerWidth() + prev_col] = patch.ControlPointList[cpid];
            }
        }
    }
}

class GLApp
{
private:
    GLuint VertexArrayObject = 0;
    
    static constexpr unsigned int MODEL_COUNT = 9;
    GBPatch Patches[MODEL_COUNT];
    GLuint VertexBuffersCsiga[MODEL_COUNT]     = {};
    unsigned int NumVerticesCsiga[MODEL_COUNT] = {};
    
    GLuint VertexBuffers[MODEL_COUNT]         = {};
    unsigned int NumVertices[MODEL_COUNT]     = {};
    
    GLuint UniformBuffer = 0;
    
    GLuint ShaderProgram = 0;
    
    unsigned int Counter = 0;
    static constexpr unsigned int MAX_CNT = 500;
    
    
    unsigned int LayerCounter = 0;
    static constexpr unsigned int LAYER_MAX_CNT = 60;
    
    unsigned int CurrentModel = 0;
    
    unsigned int CurrentLayer = 0;
    
public:
    
    void Loop()
    {
        if(Counter >= MAX_CNT)
        {
            CurrentModel = (CurrentModel + 1) % MODEL_COUNT;
            Counter = 0;
            CurrentLayer = 0;
        }
        else
        {
            Counter++;
        }
        
        if(LayerCounter >= LAYER_MAX_CNT)
        {
            CurrentLayer = (CurrentLayer + 1) % Patches[CurrentModel].SideCount;
            LayerCounter = 0;
        }
        else
        {
            LayerCounter++;
        }
        
        glClearColor(1.0,0.0,0.0,1.0);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glPointSize(5.0);
        
        glUseProgram(ShaderProgram);
        
        glBindBufferRange(GL_UNIFORM_BUFFER,0,UniformBuffer,0,sizeof(mat4));
        
        glBindVertexArray(VertexArrayObject);
        
        glBindVertexBuffer(0,VertexBuffersCsiga[CurrentModel],0,4*sizeof(float));
        glDrawArrays(GL_POINTS,0,NumVerticesCsiga[CurrentModel]);
        
        
        glPointSize(10.0);
        
        glBindVertexBuffer(0,VertexBuffers[CurrentModel],0,4*sizeof(float));
        
        glDrawArrays(GL_POINTS,0,1);
        
        std::size_t StartIndex = 1 + CurrentLayer * Patches[CurrentModel].GetLayerCpCount();
        
        glDrawArrays(GL_POINTS,StartIndex,Patches[CurrentModel].GetLayerCpCount());
    }
    
    GLApp()
    {
        std::cout << VertexShaderSrc << std::endl;
        std::cout << FragmentShaderSrc << std::endl;
        
        GLLoadExtensions();
        GLDbgLoadExtensions();
        
        {
            const char *ShaderSource = VertexShaderSrc.c_str();
            GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(VertexShader,1,&ShaderSource,nullptr);
            glCompileShader(VertexShader);
            
            lGLDbgPrintShaderCompileError(VertexShader);
            
            ShaderSource = FragmentShaderSrc.c_str();
            GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(FragmentShader,1,&ShaderSource,nullptr);
            glCompileShader(FragmentShader);
            
            lGLDbgPrintShaderCompileError(FragmentShader);
            
            ShaderProgram = glCreateProgram();
            
            glAttachShader(ShaderProgram,VertexShader);
            glAttachShader(ShaderProgram,FragmentShader);
            
            glLinkProgram(ShaderProgram);
            
            glDetachShader(ShaderProgram,VertexShader);
            glDetachShader(ShaderProgram,FragmentShader);
            
            lGLDbgPrintProgramLinkError(ShaderProgram);
            
            glDeleteShader(VertexShader);
            glDeleteShader(FragmentShader);
        }
        
        const char *filenames[MODEL_COUNT]=
        {
            "./Models/cagd86.gbp",
            "./Models/car.gbp",
            "./Models/dolphin.gbp",
            "./Models/octant.gbp",
            "./Models/Trebol_3sided.gbp",
            "./Models/Trebol_4bsided.gbp",
            "./Models/Trebol_4esided.gbp",
            "./Models/Trebol_5sided.gbp",
            "./Models/Trebol_6sided.gbp",
        };
        
        glGenBuffers(MODEL_COUNT,VertexBuffersCsiga);
        glGenBuffers(MODEL_COUNT,VertexBuffers);
        for(unsigned int i=0;i < MODEL_COUNT;i++)
        {
            LoadPatch(Patches[i],filenames[i],i);
            
            NumVerticesCsiga[i] = Patches[i].ControlPointList.size();
            NumVertices[i] = Patches[i].PerSideCpArray.size();
            
            glBindBuffer(GL_ARRAY_BUFFER,VertexBuffersCsiga[i]);
            glBufferData(GL_ARRAY_BUFFER,Patches[i].ControlPointList.size() * sizeof(vec4),Patches[i].ControlPointList.data(),GL_STATIC_DRAW);
            
            glBindBuffer(GL_ARRAY_BUFFER,VertexBuffers[i]);
            glBufferData(GL_ARRAY_BUFFER,Patches[i].PerSideCpArray.size() * sizeof(vec4),Patches[i].PerSideCpArray.data(),GL_STATIC_DRAW);
        }
        
        glGenBuffers(1,&UniformBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER,UniformBuffer);
        
        mat4 Transform = translate(vec4(0.0,0.0,-50.0)) * perspective<float>(PI/3.0,1.0,1.0,-400.0);
        glBufferData(GL_UNIFORM_BUFFER,sizeof(mat4),&Transform,GL_STREAM_DRAW);
        
        glGenVertexArrays(1,&VertexArrayObject);
        
        glBindVertexArray(VertexArrayObject);
        
        glEnableVertexAttribArray(0);
        glVertexAttribFormat(0,
                             3,
                             GL_FLOAT,
                             GL_FALSE,
                             0
                            );
        glVertexAttribBinding(0,0);
    }
    
    ~GLApp()
    {
        glDeleteBuffers(MODEL_COUNT,VertexBuffersCsiga);
        glDeleteBuffers(MODEL_COUNT,VertexBuffers);
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

