/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SkydomeModel.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "GUI.hpp"
#include "myGUI.hpp"
#include "Scene.hpp"

#include "OBJParser.hpp"
#include "RenderingSystem.hpp"

#include "Graphics.hpp"
#include "SkydomeModel.hpp"
namespace kege {namespace gfx{
    
    void SkydomeModel::Update(double delta_ms)
    {
        float skydome_scale = GetParent()->GetScene()->GetCamera()->GetFarView() * 0.95;
        GetParent()->GetLocal().scale( skydome_scale );
    }
    
    SkydomeModel::SkydomeModel()
    :   gfx::Model( "SkydomeModel" )
    {
        ds::array< shared::Geometry > geometries;
        if ( !kege::OBJLoadGeometies( geometries, "skydome-uvsphere.obj" ) )
        {
            return;
        };
        
        shared::DrawElement element = new gfx::DrawElement();
        element->SetDrawCount( (int) geometries[0]->GetIndexBuffer()->size() );
        element->SetMaterial( new gfx::SkydomeMaterial );
        element->SetDrawMode( core::DRAW_TRIANGLES );
        element->SetStartingIndex( 0 );
        
        _mesh = new gfx::Mesh( geometries[0], element );
    }
}}
