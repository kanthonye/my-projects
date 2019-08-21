/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLGraphics.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#include "Logger.hpp"
#include "enumtypes.hpp"
#include "../../../../graphics/core/platforms/opengl/LoadGLSL.hpp"
#include "../../../../graphics/core/platforms/opengl/GLVAO.hpp"
#include "../../../../graphics/core/platforms/opengl/GLVBO.hpp"
#include "../../../../graphics/core/platforms/opengl/GLIBO.hpp"
#include "../../../../graphics/core/platforms/opengl/GLUBO.hpp"
#include "../../../../graphics/core/platforms/opengl/GLWindow.hpp"
#include "../../../../graphics/core/platforms/opengl/GLTexture2D.hpp"
#include "../../../../graphics/core/platforms/opengl/GLTextureCube.hpp"
#include "../../../../graphics/core/platforms/opengl/GLShader.hpp"
#include "../../../../graphics/core/platforms/opengl/GLRenderContext.hpp"
#include "../../../../graphics/core/platforms/opengl/GLFramebuffer.hpp"
#include "../../../../graphics/core/platforms/opengl/GLWindow.hpp"
#include "../../../../graphics/core/platforms/opengl/GLGraphics.hpp"
namespace kege{namespace core{
    
    void callback_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        GraphicsFramework::OnKeyboardPress(key, scancode, action, mods);
    }
    void callback_mouse_cursor(GLFWwindow* window, double xpos, double ypos)
    {
        GraphicsFramework::OnMouseCursorMove(xpos, ypos);
    }
    void callback_mouse_wheel(GLFWwindow* window, double xoffset, double yoffset)
    {
        GraphicsFramework::OnScrollWheelMove(xoffset, yoffset);
    }
    void callback_mouse_button(GLFWwindow* window, int button, int action, int mods)
    {
        GraphicsFramework::OnMouseButtonPress(button, action, mods);
    }
    
    void callback_window_close(GLFWwindow* win)
    {
        GraphicsFramework::OnWindowClose(true);
    }
    
    void callback_window_size(GLFWwindow* glfw_window, int w, int h)
    {
        GraphicsFramework::OnWindowSize(w, h);
    }
    
    void callback_framebuffer_size(GLFWwindow* glfw_window, int w, int h)
    {
        GraphicsFramework::OnFramebufferSize(w, h);
    }
    
    void callback_window_position(GLFWwindow * glfw_window, int x, int y)
    {
        GraphicsFramework::OnWindowPosition(x, y);
    }
    
    Window* GLGraphics::CreateWindow(int width, int height, const char *title, bool fullscreen)
    {
        core::GLWindow* window = new core::GLWindow(width, height, title, fullscreen);
        if (window != nullptr)
        {
            glfwSetFramebufferSizeCallback(window->win, core::callback_framebuffer_size);
            glfwSetWindowPosCallback(window->win, core::callback_window_position);
            glfwSetWindowCloseCallback(window->win, core::callback_window_close);
            glfwSetWindowSizeCallback(window->win, core::callback_window_size);
            glfwSetMouseButtonCallback(window->win, core::callback_mouse_button);
            glfwSetCursorPosCallback(window->win, core::callback_mouse_cursor);
            glfwSetScrollCallback(window->win, core::callback_mouse_wheel);
            glfwSetKeyCallback(window->win, core::callback_keyboard);
            
            const unsigned char* str = glGetString(GL_VENDOR);
            if (str) printf("GL_VENDOR  : %s\n",str);
            str = glGetString(GL_VERSION);
            if (str) printf("GL_VERSION : %s\n",str);
            str = glGetString(GL_RENDERER);
            if (str) printf("GL_RENDERER: %s\n",str);
        }
        CheckError("GLGraphics::CreateWindow");
        return window;
    }
    
    Shader* GLGraphics::CreateShader(const ds::string& filename)
    {
        SHDR prog_files;
        if ( !LoadSHDR(prog_files, filename) )
        {
            return nullptr;
        }
        return CreateShader( prog_files );
    }
    
    Shader* GLGraphics::CreateShader(SHDR& prog_files)
    {
        core::GLShader* program = new GLShader(true);
        ds::string program_name = prog_files[ kege::ENUM::_STRING ];
        program->SetName( program_name );
        
        ds::dlist<core::ShaderVars> shader_vars;
        
        int shader_target;
        ds::string filename;
        core::ShaderVars* vars = nullptr;
        for (SHDR::iterator m=prog_files.begin(); m!=prog_files.end(); m++)
        {
            shader_target = m->first;
            filename = m->second;
            
            if ((shader_target == core::SHADER_VERTEX)   ||
                (shader_target == core::SHADER_FRAGMENT)  ||
                (shader_target == core::SHADER_GEOMETRY)  ||
                (shader_target == core::SHADER_TESS_EVAL) ||
                (shader_target == core::SHADER_TESS_CTROL) )
            {
                ds::string shader_source;
                ds::string shader_filename = kege::VFS::GetInstance().GetFilename( filename.c_str() );
                
                vars = &shader_vars.push_back();
                vars->target = shader_target;
                
                LoadGLSL(shader_source, vars, shader_filename );
                if ( shader_source.empty() )
                {
                    KEGE_ERROR("loading shader %s fail FAILED.", filename.c_str() );
                    delete program;
                    program = nullptr;
                    return program;
                }
                switch ( shader_target )
                {
                    case core::SHADER_VERTEX:
                        program->VertexShader( shader_source.c_str() );
                        break;
                        
                    case core::SHADER_GEOMETRY:
                        program->GeometryShader( shader_source.c_str() );
                        break;
                        
                    case core::SHADER_FRAGMENT:
                        program->FragmentShader( shader_source.c_str() );
                        break;
                        
                    case core::SHADER_TESS_EVAL:
                        program->TessEvalShader( shader_source.c_str() );
                        break;
                        
                    case core::SHADER_TESS_CTROL:
                        program->TessContShader( shader_source.c_str() );
                        break;
                        
                    default: break;
                }
            }
        }
        
        if ( !program->Create() )
        {
            delete program;
            program = nullptr;
            return program;
        }
        
        program->Enable();
        {
//            KEGE_INFO("%s", program_name.c_str());
            core::ShaderVars::Variable* var;
            core::ShaderVars::ShaderVarList::iterator u;
            for (ds::dlist<core::ShaderVars>::iterator s=shader_vars.begin(); s!=nullptr; s++)
            {
                vars = &s.element();
                source src = EnumToString( vars->target );
                KEGE_INFO("# %s", src);
                for (u=vars->uniform_blocks.begin(); u!=nullptr; u++)
                {
                    var = &u.element();
                    program->LinkUBO( var->id );
                }
                //program->LinkShaderSubroutines( (core::SHADER) vars->target );
                //for (u=vars->attributes.begin(); u!=nullptr; u++)
                //{
                //    var = &u.element();
                //    program->ShaderAttribute(var->value, var->id);
                //    KEGE_INFO("%s : (%s : location = [%i])", program_name.c_str(), var->id.c_str(), var->value);
                //}
                CheckError("ShaderVars");
            }
        }
        program->Disable();
        return program;
    }
    
    Shader* GLGraphics::CreateShader()
    {
        return new GLShader(true);
    }
    
    Framebuffer* GLGraphics::CreateFramebuffer()
    {
        return new GLFramebuffer;
    }
    
    VBO* GLGraphics::CreateVBO(long size, const void* data, cg::uint usage)
    {
        return new GLVBO(size, data, usage);
    }
    UBO* GLGraphics::CreateUBO(long size, const void* data, cg::uint usage, const ds::string& name)
    {
        return new GLUBO(size, data, usage, name);
    }
    VAO* GLGraphics::CreateVAO( core::VertexBuffer* vb, core::IndexBuffer* ib )
    {
        VAO* vao = CreateVAO();
        if ( vb != nullptr ) vao->AttachVBO( *vb, core::STATIC_DRAW );
        if ( ib != nullptr ) vao->AttachIBO( *ib, core::STATIC_DRAW );
        return vao;
    }
    IBO* GLGraphics::CreateIBO(long size, const void* data, cg::uint usage)
    {
        return new GLIBO(size, data, usage);
    }
    
    RenderContext* GLGraphics::CreateRenderSetting()
    {
        return new GLRenderContext();
    }
    
    TextureCube* GLGraphics::CreateTextureCube()
    {
        return new GLTextureCube();
    }
    Texture2D* GLGraphics::CreateTexture2D()
    {
        return new GLTexture2D();
    }
    
    void GLGraphics::SetBackgroundColor(const cg::vec4& color)const
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }
    
    void GLGraphics::EnablePointFrame()const
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    
    void GLGraphics::EnableWireFrame()const
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    
    void GLGraphics::EnableFillFrame()const
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    void GLGraphics::DisableCulling()const
    {
        glDisable(GL_CULL_FACE);
    }
    
    void GLGraphics::EnableCullingCCW()const
    {
        glEnable(GL_CULL_FACE);
        glFrontFace (GL_CCW);
        glCullFace (GL_FRONT);
    }
    
    void GLGraphics::EnableCullingCW()const
    {
        glEnable(GL_CULL_FACE);
        glFrontFace (GL_CW);
        glCullFace (GL_FRONT);
    }
    
    void GLGraphics::DisableDepthTest()const
    {
        glDisable(GL_DEPTH_TEST);
    }
    void GLGraphics::EnableDepthTest()const
    {
        glEnable(GL_DEPTH_TEST);
    }
    
    void GLGraphics::DisableBlending()const
    {
        glDisable(GL_BLEND);
    }
    
    void GLGraphics::EnableBlending()const
    {
        glEnable(GL_BLEND);
    }
    void GLGraphics::AlphaBlending()const
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
    }
    
    void GLGraphics::ClearScreen(void)const
    {
        //glViewport(0, 0, core::Window::framebuffer_width, core::Window::framebuffer_height);
        //glClearColor(bgcolr.x, bgcolr.y, bgcolr.z, bgcolr.w);
        //glClear( flags );
    }
    
    VAO* GLGraphics::CreateVAO()
    {
        VAO* vao = new GLVAO();
        vao->Create();
        return vao;
    }
    VBO* GLGraphics::CreateVBO()
    {
        return new GLVBO();
    }
    UBO* GLGraphics::CreateUBO()
    {
        return new GLUBO();
    }
    IBO* GLGraphics::CreateIBO()
    {
        return new GLIBO();
    }
    
    cg::uint GLGraphics::GetConstant(int target)
    {
        return GLGetConstant(target);
    }
    
    cg::uint GLGraphics::GLGetConstant(int target)
    {
        switch (target)
        {
            case core::STATIC_DRAW: return GL_STATIC_DRAW;
            case core::DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
            case core::STREAM_DRAW: return GL_STREAM_DRAW;
                
            case core::DRAW_LINES: return GL_LINES;
            case core::DRAW_POINTS: return GL_POINTS;
            case core::DRAW_TRIANGLES: return GL_TRIANGLES;
            case core::DRAW_TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
            case core::DRAW_PATCH: return GL_PATCHES;
                
            case core::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
            case core::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
            case core::UNSIGNED_INT: return GL_UNSIGNED_INT;
            case core::FLOAT: return GL_FLOAT;
            case core::SHORT: return GL_SHORT;
            case core::BYTE: return GL_BYTE;
            case core::INT: return GL_INT;
            case core::VEC2: return GL_FLOAT_VEC2;
            case core::VEC3: return GL_FLOAT_VEC3;
            case core::VEC4: return GL_FLOAT_VEC4;
            case core::MAT2: return GL_FLOAT_MAT2;
            case core::MAT3: return GL_FLOAT_MAT3;
            case core::MAT4: return GL_FLOAT_MAT4;
                
            case core::RGB16: return GL_RGB16F;
            case core::RGB32: return GL_RGB32F;
                
            case core::RED: return GL_RED;
            case core::RGB: return GL_RGB;
            case core::RGBA: return GL_RGBA;
            case core::LINEAR_FILTER: return GL_LINEAR;
            case core::NEAREST_FILTER: return GL_NEAREST;
            case core::REPEAT: return GL_REPEAT;
            case core::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
            case core::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
                
            case core::DEPTH_BUFFER_BIT: return GL_DEPTH_BUFFER_BIT;
            case core::COLOR_BUFFER_BIT: return GL_COLOR_BUFFER_BIT;
            case core::STENCIL_BUFFER_BIT: return GL_STENCIL_BUFFER_BIT;
                
            default: return 0;
        }
    }
    
    
    
    
    source GLGraphics::EnumToString(int target)
    {
        switch (target)
        {
            default: return "UNKNOWN_ENUM";
                
            case core::SHADER_VERTEX:
            case GL_VERTEX_SHADER:          return "VERTEX_SHADER";
                
            case core::SHADER_FRAGMENT:
            case GL_FRAGMENT_SHADER:        return "FRAGMENT_SHADER";
                
            case core::SHADER_GEOMETRY:
            case GL_GEOMETRY_SHADER:        return "GEOMETRY_SHADER";
                
            case core::SHADER_TESS_CTROL:
            case GL_TESS_CONTROL_SHADER:    return "TESS_CONTROL_SHADER";
                
            case core::SHADER_TESS_EVAL:
            case GL_TESS_EVALUATION_SHADER: return "TESS_EVALUATION_SHADER";
                
            case core::STATIC_DRAW: return "STATIC_DRAW";
            case core::DYNAMIC_DRAW: return "DYNAMIC_DRAW";
            case core::STREAM_DRAW: return "TREAM_DRAW";
            case core::DRAW_POINTS: return "POINTS";
            case core::DRAW_TRIANGLES: return "TRIANGLES";
            case core::DRAW_TRIANGLE_STRIP: return "TRIANGLE_STRIP";
            case core::DRAW_PATCH: return "PATCHES";
            case core::REPEAT: return "REPEAT";
            case core::CLAMP_TO_EDGE: return "CLAMP_TO_EDGE";
            case core::MIRRORED_REPEAT: return "MIRRORED_REPEAT";
                
            case core::DEPTH_BUFFER_BIT: return "DEPTH_BUFFER_BIT";
            case core::COLOR_BUFFER_BIT: return "COLOR_BUFFER_BIT";
            case core::STENCIL_BUFFER_BIT: return "STENCIL_BUFFER_BIT";
                
        }
    }
    
    void GLGraphics::CheckError(source msg)
    {
        int err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            switch (err)
            {
                case GL_INVALID_ENUM:
                    KEGE_ERROR("GL_INVALID_ENUM %s\n",msg);
                    break;
                    
                case GL_INVALID_VALUE:
                    KEGE_ERROR("GL_INVALID_VALUE %s\n",msg);
                    break;
                    
                case GL_INVALID_OPERATION:
                    KEGE_ERROR("GL_INVALID_OPERATION %s\n",msg);
                    break;
                    
                case GL_OUT_OF_MEMORY:
                    KEGE_ERROR("GL_OUT_OF_MEMORY %s\n",msg);
                    break;
                    
//                case GL_STACK_UNDERFLOW:
//                    KEGE_ERROR("GL_STACK_UNDERFLOW %s\n",msg);
//                    break;
//                    
//                case GL_STACK_OVERFLOW:
//                    KEGE_ERROR("GL_STACK_OVERFLOW %s\n",msg);
//                    break;
                    
                default:
                    break;
            }
        }
    }
    GLGraphics::~ GLGraphics()
    {
        glfwTerminate();
    }
    GLGraphics::GLGraphics()
    {
        if (glfwInit())
        {
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        }
    }
}}



