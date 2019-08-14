/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModule.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModule_hpp
#define GUIModule_hpp
#include "../../../scene/core/Object.hpp"
#include "../../gui/events/GUIEvent.hpp"
namespace kege{namespace cg{
    
    class GUIControl;
    
    class GUIModule// : public kege::Object
    {
    public:
        
        virtual int onEvent(const cg::GUIEvent& event) {return GUIEvent::NOTHING;}
        virtual int onAction(cg::uint event)  {return GUIEvent::NOTHING;}
        
        virtual void SetParent(cg::GUIControl* parent){_parent = parent;}
        const cg::GUIControl* GetParent()const{return _parent;}
        cg::GUIControl* GetParent(){return _parent;}
        
        virtual void UnInit(){}
        virtual bool Init(){return true;}
       
        virtual ~ GUIModule(){}
        GUIModule(GUIEvent::Type type)
        :   _parent( nullptr )
        ,   _type( type )
        {}
        
        cg::GUIControl* _parent;// owner of the module
        const GUIEvent::Type _type;  // type of module
    };
}}
#endif /* GUIModule_hpp */
