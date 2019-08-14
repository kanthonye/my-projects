/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/22/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainMap.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Singleton.hpp"
#include "Scene.hpp"
#include "Region.hpp"
#include "Terrain.hpp"
#include "Graphics.hpp"
#include "TerrainSystem.hpp"
#include "TerrainMaterial.hpp"
#include "MeshComponent.hpp"
#include "CoreTaskManager.hpp"
namespace kege{namespace gfx{
    
    void Region::operator()(float x, float z, int size)
    {
        _size = size;
        _x = x;
        _z = z;
    }
    
    void Region::GetRenderables( kege::SceneFrame& frame )
    {
        if (_region.type == RegionType::NODE)
        {
            _region.node[0].GetRenderables( frame );
            _region.node[1].GetRenderables( frame );
            _region.node[2].GetRenderables( frame );
            _region.node[3].GetRenderables( frame );
        }
        else
        {
            if (_region.tile->IsInit())
            {
                _region.tile->GetRenderables( frame );
            }
            else if (_region.tile->IsLoaded() && !_region.tile->IsInit())
            {
                _region.tile->Init(nullptr);
            }
        }
    }
    
    void Region::CreateTerrainTile(Terrain* terrain)
    {
        int scale_size = terrain->GetSystem()->GetTileSize() * terrain->GetSystem()->GetScale();
        
        float tx = _x + 0.5 - _size;
        float tz = _z + 0.5 - _size;
        
        _region.type = RegionType::OBJECT;
        _region.tile = new TerrainTile;
        _region.tile->GetLocal().translation.x = tx * scale_size;
        _region.tile->GetLocal().translation.z = tz * scale_size;
        _region.tile->GetLocal().scale.x = terrain->GetSystem()->GetScale();
        _region.tile->GetLocal().scale.z = terrain->GetSystem()->GetScale();
        _region.tile->SetRadius( sqrt( 2 * cg::sq(scale_size) ) );
        _region.tile->SetLoaded(false);
        
        int hs = terrain->_system->GetColumns() * 0.5;
        int mx = terrain->_coord.x - hs;
        int mz = terrain->_coord.y - hs;
        
        tx = tx - mx;
        tz = tz - mz;
        tx = tx * terrain->GetSystem()->GetTileSize();
        tz = tz * terrain->GetSystem()->GetTileSize();
        
        kege::CoreTaskManager* manager = kege::Singleton::Get<CoreTaskManager>();
        if (manager != nullptr)
        {
            manager->AddTask( new TerrainLoader(tx, tz, _region.tile, terrain) );
        }
    }
    
    void Region::Update(Terrain* terrain)
    {
        gfx::Transform& transform = terrain->GetScene()->GetCamera()->GetWorld();
        
        long scale_size = terrain->GetSystem()->GetTileSize() * terrain->GetSystem()->GetScale();
        int cx = _x * scale_size - transform.translation.x;
        int cz = _z * scale_size - transform.translation.z;
        double distance = cg::sq(cx) + cg::sq(cz);
        
        scale_size = scale_size * _size;
        scale_size = cg::sq(scale_size + scale_size);
        double res = distance / scale_size;
        
        if (res <= terrain->GetSystem()->resolution)
        {
            if ( SubDivide(terrain) && _region.type == RegionType::NODE)
            {
                _region.node[0].Update(terrain);
                _region.node[1].Update(terrain);
                _region.node[2].Update(terrain);
                _region.node[3].Update(terrain);
            }
            else if (_size == 1 && _region.tile == nullptr)
            {
                CreateTerrainTile(terrain);
            }
            else
            {
                _region.tile->Update(0);
            }
        }
        else
        {
            if (_region.node != nullptr)
            {
                UnDivide(terrain);
            }
        }
    }
    
    bool Region::SubDivide(Terrain* terrain)
    {
        if ( _region.node != nullptr )
        {
            return true;
        }
        if (_size <= 1)
        {
            return false;
        }
        
        AddChild();
        return true;
    }
    
    void Region::RemoveChild(Terrain* terrain)
    {
        if ( _region.node != nullptr )
        {
            if (_region.type == RegionType::OBJECT)
            {
                delete _region.tile;
                _region.tile = nullptr;
            }
            else
            {
                _region.node[0].RemoveChild(terrain);
                _region.node[1].RemoveChild(terrain);
                _region.node[2].RemoveChild(terrain);
                _region.node[3].RemoveChild(terrain);
                delete [] _region.node;
                _region.node = nullptr;
            }
        }
    }
    
    void Region::AddChild()
    {
        if ( _region.node == nullptr )
        {
            int half_size = _size * 0.5;
            float quat_size = half_size * 0.5;
            
            _region.type = RegionType::NODE;
            _region.node = new Region[4];
            _region.node[0](_x - quat_size, _z - quat_size, half_size);
            _region.node[1](_x + quat_size, _z - quat_size, half_size);
            _region.node[2](_x - quat_size, _z + quat_size, half_size);
            _region.node[3](_x + quat_size, _z + quat_size, half_size);
        }
    }
    
    void Region::UnDivide(Terrain* terrain)
    {
        RemoveChild( terrain );
    }
    
    Region::Region(int x, int z, int size)
    :   _x(x)
    ,   _z(z)
    ,   _size(size)
    {
    }
    
    Region::~ Region()
    {
        UnDivide(nullptr);
    }
    Region::Region()
    :   _x(0)
    ,   _z(0)
    ,   _size(0)
    {
    }
}}
