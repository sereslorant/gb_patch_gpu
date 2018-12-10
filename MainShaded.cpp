
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <string>
#include <cstring>
#include <vector>

#include <fstream>

#include "glmath.hpp"

float PI = 3.14159265359;

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
#include <chrono>

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
    
    layout(vertices = 1) out;
    
    void main()
    {
        gl_TessLevelOuter[0] = 16.0;
        gl_TessLevelOuter[1] = 16.0;
        gl_TessLevelOuter[2] = 16.0;
        
        gl_TessLevelInner[0] = 16.0;
    }
)";

std::string TeShaderSrc = R"(
    #version 420
    
    layout(triangles,equal_spacing,ccw) in;
    
    out vec3 FragPos;
    
    const uint SIDE_COUNT = 0;
    const uint DEGREE     = 1;
    const uint LAYERS     = 2;
    
    layout(binding=0,std140) uniform MatrixBlock
    {
        mat4 MvpMatrix;
    };
    
    layout(binding=1,std140) uniform MetaDataBlock
    {
        ivec4 MetaData;
    };
    
    // Így küzdjük le a hardveres 32 kontroll pont korlátot.
    layout(binding=2,std140) uniform ControlPointBlock
    {
        vec4 ControlPoints[4096];   // UBO-nál kötelező felső korlátot adni, ha tetszőleges méretet akarnánk, akkor
                                    // Shader Storage Buffer Objectet kell használni.
    };
    
    int GetLayerWidth()
    {
        return MetaData[DEGREE] + 1;
    }
    
    int GetLayerCpCount()
    {
        return MetaData[LAYERS] * GetLayerWidth();
    }
    
    vec4 GetControlPoint(uint side,uint row,uint column)
    {
        return ControlPoints[1 + side*GetLayerCpCount() + row*GetLayerWidth() + column];
    }
    
    const uint MAX_SIDE_COUNT = 16;
    
    float BinomialCoefficient(uint k,uint n)
    {
        float Accumulator = 1.0;
        for(uint i=1;i <= k;i++)
        {
            Accumulator *= (n + 1.0 - i)/i;
        }
        return Accumulator;
    }
    
    void main()
    {
        const float PI         = 3.14159265359;
        const float EPSILON    = 1e-2;
        
        uint VertexId0 = (gl_PrimitiveID       % MetaData[SIDE_COUNT]);
        uint VertexId1 = ((gl_PrimitiveID + 1) % MetaData[SIDE_COUNT]);
        
        vec3 Vertices[MAX_SIDE_COUNT];
        for(uint i=0;i < MetaData[SIDE_COUNT];i++)
        {
            float SinParam = float(i)/ MetaData[SIDE_COUNT];
            Vertices[i] = vec3(cos(SinParam * 2.0 * PI),sin(SinParam * 2.0 * PI),0.0);
        }
        
        vec3 UvCoord = gl_TessCoord.y * Vertices[VertexId0] + gl_TessCoord.z * Vertices[VertexId1];
        
        float SumBaryCoords = 0.0;
        float BaryCoords[MAX_SIDE_COUNT];
        for(uint i=0;i < MetaData[SIDE_COUNT];i++)
        {
            uint Prev = (i-1);
            uint Curr = i;
            uint Next = (i+1) % MetaData[SIDE_COUNT];
            
            if(i == 0)
                {Prev = MetaData[SIDE_COUNT] - 1;}
            
            float A1 = length(cross(Vertices[Curr] - UvCoord,Vertices[Prev] - UvCoord))/2.0;
            float A2 = length(cross(Vertices[Curr] - UvCoord,Vertices[Next] - UvCoord))/2.0;
            
            float C  = length(cross(Vertices[Prev] - Vertices[Curr],Vertices[Next] - Vertices[Curr]))/2.0;
            
            BaryCoords[i] = C/(A1*A2);
            
            SumBaryCoords += BaryCoords[i];
        }
                
        for(uint i=0;i < MetaData[SIDE_COUNT];i++)
        {
            if(gl_TessCoord.x > EPSILON)
                {BaryCoords[i] /= SumBaryCoords;}
            else
                {BaryCoords[i] = 0.0;}
        }
        
        if(gl_TessCoord.x < EPSILON)
        {
            BaryCoords[VertexId0] = gl_TessCoord.y;
            BaryCoords[VertexId1] = gl_TessCoord.z;
        }
        
        vec2 SideCoords[MAX_SIDE_COUNT];
        for(uint i=0;i < MetaData[SIDE_COUNT];i++)
        {
            SideCoords[i] = vec2(0.0,0.0);
            
            uint Prev = (i-1);
            uint Curr = i;
            
            if(i == 0)
                {Prev = MetaData[SIDE_COUNT] - 1;}
            
            float Denominator = BaryCoords[Prev] + BaryCoords[Curr]; 
            SideCoords[i].x = BaryCoords[Curr] / Denominator;
            if(Denominator < EPSILON)
                {SideCoords[i].x = 0.0;}
            
            SideCoords[i].y = 1.0 - BaryCoords[Prev] - BaryCoords[Curr];
        }
        
        float CentralCoeff = 1.0;
        vec4 Position = vec4(0.0,0.0,0.0,1.0);
        for(uint i=0;i < MetaData[SIDE_COUNT];i++)
        {
            uint Prev = (i-1);
            uint Curr = i;
            uint Next = (i+1) % MetaData[SIDE_COUNT];
            
            if(i == 0)
                {Prev = MetaData[SIDE_COUNT] - 1;}
            
            for(uint j=0;j <= MetaData[DEGREE];j++)
            {
                for(uint k=0;k < MetaData[LAYERS];k++)
                {
                    float Bernstein = BinomialCoefficient(j,MetaData[DEGREE])*pow(1.0-SideCoords[i].x,MetaData[DEGREE]-j)*pow(SideCoords[i].x,j) *
                                      BinomialCoefficient(k,MetaData[DEGREE])*pow(1.0-SideCoords[i].y,MetaData[DEGREE]-k)*pow(SideCoords[i].y,k);
                    
                    float Weight = 1.0;
                    
                    vec4 ControlPoint = GetControlPoint(i,k,j);
                    
                    if(k < 2)
                    {
                        if(j < 2)
                        {
                            float Denominator = (SideCoords[Prev].y + SideCoords[Curr].y);
                            if(Denominator < EPSILON)
                                {Weight = 1.0;}
                            else
                                {Weight = (SideCoords[Prev].y)/Denominator;}
                        }
                        
                        if(j > (MetaData[DEGREE] - 2))
                        {
                            float Denominator = (SideCoords[Next].y + SideCoords[Curr].y);
                            if(Denominator < EPSILON)
                                {Weight = 0.0;}
                            else
                                {Weight = (SideCoords[Next].y)/Denominator;}
                        }
                    }
                    else
                    {
                        if(j < MetaData[LAYERS])
                        {
                            if(j < k)
                                {Weight = 0.0;}
                            else if(j == k)
                                {Weight = 0.5;}
                        }
                        else
                        {
                            if(j > (MetaData[DEGREE] - k))
                                {Weight = 0.0;}
                            else if(j == (MetaData[DEGREE] - k))
                                {Weight = 0.5;}
                        }
                    }
                    
                    float Coeff = Bernstein * Weight;
                    
                    Position += Coeff * ControlPoint;
                    
                    CentralCoeff -= Coeff;
                }
            }
        }
        
        Position += CentralCoeff * ControlPoints[0];
        Position.w = 1.0;
        
        FragPos = Position.xyz;
        
        gl_Position = MvpMatrix * Position;
    }
)";

std::string FragmentShaderSrc = R"(
    #version 400
    
    in vec3 FragPos;
    
    layout(location=0) out vec4 FragColor; 
    
    void main()
    {
        vec3 ApproxNormal = normalize(FragPos); // Csak ahhoz kell, hogy jól nézzen ki.
        
        vec3 PointLightPos = vec3(-50.0,50.0,50.0);
        vec3 PointLightDir = normalize(PointLightPos - FragPos);
        
        float NormalDotDir = max(0.0,min(dot(ApproxNormal,PointLightDir),1.0));
        
        FragColor = vec4(NormalDotDir * vec3(1.0,1.0,1.0),1.0);
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

struct GBMetaData
{
    int SideCount;
    int Degree;
    int Layers;
};

class GLApp
{
private:
    
    static constexpr unsigned int MODEL_COUNT = 9;
    GBPatch Patches[MODEL_COUNT]              = {};
    GLuint PatchBuffers[MODEL_COUNT]          = {};
    GLuint MetaDataBuffers[MODEL_COUNT]       = {};
    
    GLuint UniformBuffer = 0;
    
    GLuint VertexArrayObject = 0;
    
    GLuint ShaderProgram = 0;
    
    unsigned int Counter = 0;
    static constexpr unsigned int MAX_CNT = 100;
    
    unsigned int CurrentModel = 0;
    
    double Time[MODEL_COUNT] = {};
    
public:

    void Loop()
    {
        if(Counter >= MAX_CNT)
        {
            Time[CurrentModel] /= MAX_CNT;
            CurrentModel = (CurrentModel + 1) % MODEL_COUNT;
            Time[CurrentModel] = 0.0;
            Counter = 0;
        }
        else
        {
            Counter++;
        }
        
        glClearColor(0.5,0.5,0.5,1.0);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        
        glUseProgram(ShaderProgram);
        
        glBindBufferRange(GL_UNIFORM_BUFFER,0,UniformBuffer,0,sizeof(mat4));
        glBindBufferRange(GL_UNIFORM_BUFFER,1,MetaDataBuffers[CurrentModel],0,sizeof(GBMetaData));
        glBindBufferRange(GL_UNIFORM_BUFFER,2,PatchBuffers[CurrentModel],0,Patches[CurrentModel].PerSideCpArray.size() * sizeof(vec4));
        
        glFinish();
        
        auto Before = std::chrono::system_clock::now();
        glPatchParameteri(GL_PATCH_VERTICES,1);
        glDrawArrays(GL_PATCHES,0,Patches[CurrentModel].SideCount);
        
        glFinish();
        auto After = std::chrono::system_clock::now();
        
        auto Difference = (After - Before);
        
        Time[CurrentModel] += std::chrono::duration<double,std::milli>(Difference).count();
        
        std::cout << "Patch generation time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
        
        for(int i=0;i < MODEL_COUNT;i++)
        {
            std::cout << "Time " << i << ": " << Time[i] << std::endl;
        }
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
        
        glGenBuffers(MODEL_COUNT,PatchBuffers);
        glGenBuffers(MODEL_COUNT,MetaDataBuffers);
        for(unsigned int i=0;i < MODEL_COUNT;i++)
        {
            LoadPatch(Patches[i],filenames[i],i);
            
            GBMetaData MetaData =
            {
                .SideCount = (int)Patches[i].SideCount,
                .Degree    = (int)Patches[i].Degree,
                .Layers    = (int)Patches[i].Layers,
            };
            
            glBindBuffer(GL_UNIFORM_BUFFER,PatchBuffers[i]);
            glBufferData(GL_UNIFORM_BUFFER,Patches[i].PerSideCpArray.size() * sizeof(vec4),Patches[i].PerSideCpArray.data(),GL_STATIC_DRAW);
            
            glBindBuffer(GL_UNIFORM_BUFFER,MetaDataBuffers[i]);
            glBufferData(GL_UNIFORM_BUFFER,sizeof(GBMetaData),&MetaData,GL_STATIC_DRAW);
        }
        
        glGenBuffers(1,&UniformBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER,UniformBuffer);
        
        mat4 Transform = translate(vec4(0.0,0.0,-50.0)) * perspective<float>(PI/3.0,1.0,1.0,-400.0);
        glBufferData(GL_UNIFORM_BUFFER,sizeof(mat4),&Transform,GL_STREAM_DRAW);
        
        glGenVertexArrays(1,&VertexArrayObject);
        glBindVertexArray(VertexArrayObject);
    }
    
    ~GLApp()
    {
        glDeleteBuffers(MODEL_COUNT,PatchBuffers);
        glDeleteBuffers(MODEL_COUNT,MetaDataBuffers);
        glDeleteBuffers(1,&UniformBuffer);
        
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
