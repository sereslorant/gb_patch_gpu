
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

float BinomialCoefficient(uint k,uint n)
{
    float Accumulator = 1.0;
    for(uint i=1;i <= k;i++)
    {
        Accumulator *= (n + 1.0 - i)/i;
    }
    return Accumulator;
}

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
    
    vec4 GetControlPoint(uint side,uint row,uint column)
    {
        return PerSideCpArray[1 + side*GetLayerCpCount() + row*GetLayerWidth() + column];
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

/*
const Point2DVector &
Domain::parameters(size_t resolution) const {
  size_t size = 1 + n_ * resolution * (resolution + 1) / 2;
  if (parameters_.size() != size) {
    parameters_.reserve(size);
    parameters_.push_back(center_);
    for (size_t j = 1; j <= resolution; ++j) {
      double u = (double)j / (double)resolution;
      for (size_t k = 0; k < n_; ++k)
        for (size_t i = 0; i < j; ++i) {
          double v = (double)i / (double)j;
          Point2D ep = vertices_[prev(k)] * (1.0 - v) + vertices_[k] * v;
          Point2D p = center_ * (1.0 - u) + ep * u;
          parameters_.push_back(p);
        }
    }
  }
  return parameters_;
}

TriMesh
Domain::meshTopology(size_t resolution) const {
  TriMesh mesh;
  mesh.resizePoints(1 + n_ * resolution * (resolution + 1) / 2);

  size_t inner_start = 0, outer_vert = 1;
  for (size_t layer = 1; layer <= resolution; ++layer) {
    size_t inner_vert = inner_start, outer_start = outer_vert;
    for (size_t side = 0; side < n_; ++side) {
      size_t vert = 0;
      while(true) {
        size_t next_vert = (side == n_ - 1 && vert == layer - 1) ? outer_start : (outer_vert + 1);
        mesh.addTriangle(inner_vert, outer_vert, next_vert);
        ++outer_vert;
        if (++vert == layer)
          break;
        size_t inner_next = (side == n_ - 1 && vert == layer - 1) ? inner_start : (inner_vert + 1);
        mesh.addTriangle(inner_vert, next_vert, inner_next);
        inner_vert = inner_next;
      }
    }
    inner_start = outer_start;
  }

  return mesh;
}
*/

class GLApp
{
private:
    GLuint VertexArrayObject = 0;
    
    static constexpr unsigned int MODEL_COUNT = 9;
    GBPatch Patches[MODEL_COUNT];
    //GLuint VertexBuffersCsiga[MODEL_COUNT]     = {};
    //unsigned int NumVerticesCsiga[MODEL_COUNT] = {};
    
    //GLuint VertexBuffers[MODEL_COUNT]         = {};
    //unsigned int NumVertices[MODEL_COUNT]     = {};
    
    GLuint UniformBuffer = 0;
    
    GLuint ShaderProgram = 0;
    
    unsigned int Counter = 0;
    static constexpr unsigned int MAX_CNT = 100;
    
    unsigned int CurrentModel = 0;
    
    
    GLuint TmpVertexBuffer[MODEL_COUNT] = {};
    std::vector<vec4> PatchVertices[MODEL_COUNT];
    GLuint TmpIndexBuffer[MODEL_COUNT] = {};
    std::vector<unsigned int> IndexArrays[MODEL_COUNT];
    
    /*
     * Forrás: Salvi Péter
     * https://bitbucket.org/salvipeter/
     */
    void CalculateVertices(std::size_t patch_id)
    {
        constexpr float EPSILON = 1e-2;
        
        std::vector<vec4> Vertices(Patches[patch_id].SideCount);
        for(uint i=0;i < Patches[patch_id].SideCount;i++)
        {
            float SinParam = float(i)/ Patches[patch_id].SideCount;
            Vertices[i] = vec4(cos(SinParam * 2.0 * PI),sin(SinParam * 2.0 * PI),0.0);
        }
        
        std::vector<float> BaryCoords(Patches[patch_id].SideCount);
        std::vector<vec4>  SideCoords(Patches[patch_id].SideCount);
        
        std::size_t resolution = 12;
        std::size_t size = 1 + Patches[patch_id].SideCount * resolution * (resolution + 1) / 2;
        vec4 center_ = {0.0,0.0};
        
        PatchVertices[patch_id].reserve(size);
        PatchVertices[patch_id].push_back(center_);
        for (size_t j = 1; j <= resolution; ++j)
        {
            double u = (double)j / (double)resolution;
            for (size_t k = 0; k < Patches[patch_id].SideCount; ++k)
            {
                int prevk = (k + (Patches[patch_id].SideCount - 1)) % Patches[patch_id].SideCount;
                for (size_t i = 0; i < j; ++i)
                {
                    double v = (double)i / (double)j;
                    vec4 ep = Vertices[prevk] * (1.0 - v) + Vertices[k] * v;
                    vec4 UvCoord = center_ * (1.0 - u) + ep * u;
                    
                    float SumBaryCoords = 0.0;
                    for(uint i=0;i < Patches[patch_id].SideCount;i++)
                    {
                        uint Prev = (i-1);
                        uint Curr = i;
                        uint Next = (i+1) % Patches[patch_id].SideCount;
                        
                        if(i == 0)
                            {Prev = Patches[patch_id].SideCount - 1;}
                        
                        float A1 = length(cross(Vertices[Curr] - UvCoord,Vertices[Prev] - UvCoord))/2.0;
                        float A2 = length(cross(Vertices[Curr] - UvCoord,Vertices[Next] - UvCoord))/2.0;
                        
                        float C  = length(cross(Vertices[Prev] - Vertices[Curr],Vertices[Next] - Vertices[Curr]))/2.0;
                        
                        BaryCoords[i] = C/(A1*A2);
                        
                        SumBaryCoords += BaryCoords[i];
                    }
                    
                    for(uint i=0;i < Patches[patch_id].SideCount;i++)
                    {
                        {BaryCoords[i] /= SumBaryCoords;}
                    }
                    
                    for(uint i=0;i < Patches[patch_id].SideCount;i++)
                    {
                        vec4 SideVector = Vertices[(i + 1) % Patches[patch_id].SideCount] - Vertices[i];
                        SideVector = normalize(SideVector);
                        vec4 Normal = {SideVector.v[1],-SideVector.v[0]};
                        if(std::abs(dot(Normal,UvCoord - Vertices[i])) < EPSILON)
                        {
                            for(uint i=0;i < Patches[patch_id].SideCount;i++)
                                {BaryCoords[i] = 0.0;}
                            BaryCoords[i] = length(UvCoord - Vertices[(i + 1) % Patches[patch_id].SideCount])/length(Vertices[(i + 1) % Patches[patch_id].SideCount] - Vertices[i]);
                            BaryCoords[(i + 1) % Patches[patch_id].SideCount] = length(UvCoord - Vertices[i])/length(Vertices[(i + 1) % Patches[patch_id].SideCount] - Vertices[i]);
                            break;
                        }
                    }
                    
                    for(uint i=0;i < Patches[patch_id].SideCount;i++)
                    {
                        if(length(UvCoord - Vertices[i]) < EPSILON)
                        {
                            for(uint i=0;i < Patches[patch_id].SideCount;i++)
                                {BaryCoords[i] = 0.0;}
                            BaryCoords[i] = 1.0;
                            break;
                        }
                    }
                    
                    for(uint i=0;i < Patches[patch_id].SideCount;i++)
                    {
                        SideCoords[i] = {0.0,0.0};
                        
                        uint Prev = (i-1);
                        uint Curr = i;
                        
                        if(i == 0)
                            {Prev = Patches[patch_id].SideCount - 1;}
                        
                        float Denominator = BaryCoords[Prev] + BaryCoords[Curr]; 
                        SideCoords[i].v[0] = BaryCoords[Curr] / Denominator;
                        if(Denominator < EPSILON)
                            {SideCoords[i].v[0] = 0.0;}
                        
                        SideCoords[i].v[1] = 1.0 - BaryCoords[Prev] - BaryCoords[Curr];
                    }
                    
                    float CentralCoeff = 1.0;
                    vec4 Position = vec4(0.0,0.0,0.0,1.0);
                    for(uint i=0;i < Patches[patch_id].SideCount;i++)
                    {
                        uint Prev = (i-1);
                        uint Curr = i;
                        uint Next = (i+1) % Patches[patch_id].SideCount;
                        
                        if(i == 0)
                            {Prev = Patches[patch_id].SideCount- 1;}
                        
                        for(uint j=0;j <= Patches[patch_id].Degree;j++)
                        {
                            for(uint k=0;k < Patches[patch_id].Layers;k++)
                            {
                                float Bernstein = BinomialCoefficient(j,Patches[patch_id].Degree)*pow(1.0-SideCoords[i].v[0],Patches[patch_id].Degree-j)*pow(SideCoords[i].v[0],j) *
                                                  BinomialCoefficient(k,Patches[patch_id].Degree)*pow(1.0-SideCoords[i].v[1],Patches[patch_id].Degree-k)*pow(SideCoords[i].v[1],k);
                                
                                float Weight = 1.0;
                                
                                vec4 ControlPoint = Patches[patch_id].GetControlPoint(i,k,j);
                                
                                if(k < 2)
                                {
                                    if(j < 2)
                                    {
                                        float Denominator = (SideCoords[Prev].v[1] + SideCoords[Curr].v[1]);
                                        if(Denominator < EPSILON)
                                            {Weight = 1.0;}
                                        else
                                            {Weight = (SideCoords[Prev].v[1])/Denominator;}
                                    }
                                    
                                    if(j > (Patches[patch_id].Degree - 2))
                                    {
                                        float Denominator = (SideCoords[Next].v[1] + SideCoords[Curr].v[1]);
                                        if(Denominator < EPSILON)
                                            {Weight = 0.0;}
                                        else
                                            {Weight = (SideCoords[Next].v[1])/Denominator;}
                                    }
                                }
                                else
                                {
                                    if(j < Patches[patch_id].Layers)
                                    {
                                        if(j < k)
                                            {Weight = 0.0;}
                                        else if(j == k)
                                            {Weight = 0.5;}
                                    }
                                    else
                                    {
                                        if(j > (Patches[patch_id].Degree - k))
                                            {Weight = 0.0;}
                                        else if(j == (Patches[patch_id].Degree - k))
                                            {Weight = 0.5;}
                                    }
                                }
                                
                                float Coeff = Bernstein * Weight;
                                
                                Position += Coeff * ControlPoint;
                                
                                CentralCoeff -= Coeff;
                            }
                        }
                    }
                    
                    Position += CentralCoeff * Patches[patch_id].PerSideCpArray[0];
                    Position.v[3] = 1.0;
                    
                    PatchVertices[patch_id].push_back(Position);
                    //PatchVertices[patch_id].push_back(30*UvCoord);
                }
            }
        }
        
        IndexArrays[patch_id].clear();
        size_t inner_start = 0, outer_vert = 1;
        for (size_t layer = 1; layer <= resolution; ++layer) {
            size_t inner_vert = inner_start, outer_start = outer_vert;
            for (size_t side = 0; side < Patches[patch_id].SideCount; ++side) {
                size_t vert = 0;
                while(true) {
                    size_t next_vert = (side == Patches[patch_id].SideCount - 1 && vert == layer - 1) ? outer_start : (outer_vert + 1);
                    IndexArrays[patch_id].push_back(inner_vert);
                    IndexArrays[patch_id].push_back(outer_vert);
                    IndexArrays[patch_id].push_back(next_vert);
                    ++outer_vert;
                    if (++vert == layer)
                        {break;}
                    size_t inner_next = (side == Patches[patch_id].SideCount - 1 && vert == layer - 1) ? inner_start : (inner_vert + 1);
                    IndexArrays[patch_id].push_back(inner_vert);
                    IndexArrays[patch_id].push_back(next_vert);
                    IndexArrays[patch_id].push_back(inner_next);
                    inner_vert = inner_next;
                }
            }
            inner_start = outer_start;
        }
    }
    
public:
    
    void Loop()
    {
        if(Counter >= MAX_CNT)
        {
            CurrentModel = (CurrentModel + 1) % MODEL_COUNT;
            Counter = 0;
        }
        else
        {
            Counter++;
        }
        
        glClearColor(1.0,0.0,0.0,1.0);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        
        //glPointSize(5.0);
        
        glUseProgram(ShaderProgram);
        
        glBindBufferRange(GL_UNIFORM_BUFFER,0,UniformBuffer,0,sizeof(mat4));
        
        glBindVertexArray(VertexArrayObject);
        /*
        glBindVertexBuffer(0,VertexBuffersCsiga[CurrentModel],0,4*sizeof(float));
        glDrawArrays(GL_POINTS,0,NumVerticesCsiga[CurrentModel]);
        
        
        glPointSize(10.0);
        
        glBindVertexBuffer(0,VertexBuffers[CurrentModel],0,4*sizeof(float));
        
        glDrawArrays(GL_POINTS,0,1);
        */
        /*
        std::size_t StartIndex = 1 + CurrentLayer * Patches[CurrentModel].GetLayerCpCount();
        
        glDrawArrays(GL_POINTS,StartIndex,Patches[CurrentModel].GetLayerCpCount());
        */
        glPointSize(1.0);
        
        glBindVertexBuffer(0,TmpVertexBuffer[CurrentModel],0,4*sizeof(float));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,TmpIndexBuffer[CurrentModel]);
        glDrawArrays(GL_POINTS,0,PatchVertices[CurrentModel].size());
        glDrawElements(GL_TRIANGLES,IndexArrays[CurrentModel].size(),GL_UNSIGNED_INT,0);
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
        
        //glGenBuffers(MODEL_COUNT,VertexBuffersCsiga);
        //glGenBuffers(MODEL_COUNT,VertexBuffers);
        glGenBuffers(MODEL_COUNT,TmpVertexBuffer);
        glGenBuffers(MODEL_COUNT,TmpIndexBuffer);
        for(unsigned int i=0;i < MODEL_COUNT;i++)
        {
            LoadPatch(Patches[i],filenames[i],i);
            
            //NumVerticesCsiga[i] = Patches[i].ControlPointList.size();
            //NumVertices[i] = Patches[i].PerSideCpArray.size();
            
            CalculateVertices(i);
            
            //glBindBuffer(GL_ARRAY_BUFFER,VertexBuffersCsiga[i]);
            //glBufferData(GL_ARRAY_BUFFER,Patches[i].ControlPointList.size() * sizeof(vec4),Patches[i].ControlPointList.data(),GL_STATIC_DRAW);
            
            //glBindBuffer(GL_ARRAY_BUFFER,VertexBuffers[i]);
            //glBufferData(GL_ARRAY_BUFFER,Patches[i].PerSideCpArray.size() * sizeof(vec4),Patches[i].PerSideCpArray.data(),GL_STATIC_DRAW);
        
            glBindBuffer(GL_ARRAY_BUFFER,TmpVertexBuffer[i]);
            glBufferData(GL_ARRAY_BUFFER,PatchVertices[i].size()*sizeof(vec4),PatchVertices[i].data(),GL_STATIC_DRAW);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,TmpIndexBuffer[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,IndexArrays[i].size()*sizeof(unsigned int),IndexArrays[i].data(),GL_STATIC_DRAW);
        }
        
        double Time[MODEL_COUNT] = {};
        for(int i=0;i < MODEL_COUNT;i++)
        {
            for(int j=0;j < 20;j++)
            {
                auto Before = std::chrono::system_clock::now();
                CalculateVertices(i);
                auto After = std::chrono::system_clock::now();
                
                auto Difference = (After - Before);
                
                Time[i] += std::chrono::duration<double,std::milli>(Difference).count();
            }
            Time[i] /= 20;
            std::cout << "Time " << i << ": " << Time[i] << std::endl;
        }
        
        glGenBuffers(1,&UniformBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER,UniformBuffer);
        
        mat4 Transform = translate(vec4(0.0,0.0,-40.0)) * perspective<float>(PI/3.0,1.0,1.0,-400.0);
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
        glDeleteBuffers(MODEL_COUNT,TmpVertexBuffer);
        
        //glDeleteBuffers(MODEL_COUNT,VertexBuffers);
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

