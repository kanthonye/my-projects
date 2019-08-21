//
//  GUIRenderer.hpp
//  KEGE_GUI
//
//  Created by Kenneth Esdaile on 2/26/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef DebugRenderer_hpp
#define DebugRenderer_hpp
#include "Graphics.hpp"
namespace kege { namespace gfx{ namespace debug{

    void DrawQuad( const cg::point3& p0, const cg::point3& p1, const cg::point3& p2, const cg::point3& p3 );
    void DrawLine( const cg::point3& p0, const cg::point3& p1);
    void DrawBox( const cg::point3& min,const cg::point3& max );
    void VertexColor( const cg::point3& p0 );
    void DrawVertex( const cg::point3& p0 );
    void BeginDraw();
    void EndDraw();
    
}}}

#endif /* Renderer2D_hpp */
