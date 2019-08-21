//
//  octree.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/3/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef octree_hpp
#define octree_hpp
#define octree_template_def template<typename itemT,typename containerT>
#define octree_template octree<itemT,containerT>
//#define octree<itemT,containerT> octree_template

#include <vector>
namespace kege{ namespace ds{
    
    // containerT item
    template<typename itemT,typename containerT> class octree
    {
    public:
        void put(const cg::vec3& p, float r, itemT a, void (*func)(containerT&, itemT));
        void print( void (*func)(float x, float y, float z, float w, containerT&) );
        void set(float x, float y, float z, float size, short min_size);
        
        // get all octree leaf nodes that the box overlaps with
        void get(std::vector<octree_template*>& nodes, const cg::vec3& min, const cg::vec3& max);
        
        // get octree leaf nodes that the box overlaps with
        octree* get(const cg::vec3& p);
        void clear();
        
        containerT& item(){return _container;}
        
        octree(float x, float y, float z, float size, short min_size);
        ~ octree();
        octree();
    private:
        bool sub_divide();
    private:
        
        float x, y, z, size;
        octree* children;
        containerT _container;
        short min_size;
    };
    
    octree_template_def
    void octree_template::put(const cg::vec3& s, float sr, itemT item, void (*addf)(containerT&, itemT))
    {
        if ((x + size) <= (s.x - sr) || (x - size) >= (s.x + sr)) return;
        if ((y + size) <= (s.y - sr) || (y - size) >= (s.y + sr)) return;
        if ((z + size) <= (s.z - sr) || (z - size) >= (s.z + sr)) return;
        
        if (sr == 0.0) sr = 1.0;
        bool sub_div = (size / sr) >= min_size;
        
        if (sub_div == true)
        {
            if ( sub_divide() )
            {
                for (int i=0; i<8; i++)
                {
                    children[i].put(s, sr, item, addf);
                }
            }
        }
        else
        {
            addf(_container, item);
        }
    }
    
    octree_template_def
    void octree_template::get(std::vector<octree_template*>& nodes, const cg::vec3& min, const cg::vec3& max)
    {
        if ((x + size) < min.x || (x - size) > max.x) return;
        if ((y + size) < min.y || (y - size) > max.y) return;
        if ((z + size) < min.z || (z - size) > max.z) return;
        
        if (children == nullptr)
        {
            nodes.push_back( this );
            return;
        }
        else
        {
            for (int i=0; i<8; i++)
            {
                children[i].get(nodes, min, max);
            }
        }
    }
    
    octree_template_def
    octree_template* octree_template::get(const cg::vec3& p)
    {
        if ((x + size) < p.x || (x - size) > p.x) return nullptr;
        if ((y + size) < p.y || (y - size) > p.y) return nullptr;
        if ((z + size) < p.z || (z - size) > p.z) return nullptr;
        
        if (children == nullptr)
        {
            return this;
        }
        else
        {
            for (int i=0; i<8; i++)
            {
                octree< itemT,containerT >* t = children[i].get(p);
                if (t != nullptr)
                {
                    return t;
                }
            }
            return nullptr;
        }
    }
    
    octree_template_def
    void octree_template::set(float x, float y, float z, float size, short min_size)
    {
        clear();
        this->min_size = min_size;
        this->size = size;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    octree_template_def
    void octree_template::clear()
    {
        if (children != nullptr)
        {
            for (int i=0; i<8; i++)
            {
                children[i].clear();
            }
            delete [] children;
            children = nullptr;
        }
    }
    
    octree_template_def octree_template::octree(float x, float y, float z, float size, short min_size)
    :   x(x)
    ,   y(y)
    ,   z(z)
    ,   size(size)
    ,   children(nullptr)
    ,   min_size(min_size)
    {}
    
    octree_template_def octree_template::~ octree()
    {
        clear();
    }
    
    octree_template_def octree_template::octree()
    :   x(0.0f)
    ,   y(0.0f)
    ,   z(0.0f)
    ,   size(0.0)
    ,   children(nullptr)
    ,   min_size(1)
    {}
    
    octree_template_def bool octree_template::sub_divide()
    {
        if (children != nullptr) return true;
        float half_size = size * 0.5;
        float px, pz, py;
        int count = 0;
        children = new octree[8];
        for (py = -half_size; py < size; py += size)
        {
            for (pz = -half_size; pz < size; pz += size)
            {
                for (px = -half_size; px < size; px += size)
                {
                    children[count].min_size = min_size;
                    children[count].size  = half_size;
                    children[count].x = x + px;
                    children[count].y = y + py;
                    children[count].z = z + pz;
                    count++;
                }
            }
        }
        return true;
    }
    
    octree_template_def void octree_template::print(  void (*func)(float x, float y, float z, float w, containerT&) )
    {
        if (children != nullptr)
        {
            for (int i=0; i<8; i++)
            {
                children[i].print( func );
            }
        }
        else
        {
            func( x,y,x,size, _container );
        }
    }
}}
//#include "octree.inl"
#endif /* octree_hpp */
