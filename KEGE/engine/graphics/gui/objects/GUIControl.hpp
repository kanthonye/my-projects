/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIControl.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIControl_hpp
#define GUIControl_hpp
#include "../../gui/objects/GUIWidget.hpp"
#include "../../gui/objects/GUIModuleList.hpp"
namespace kege{namespace cg{
    typedef std::map<cg::uint, GUIModuleList> GUIModulMap;
    
    class GUIControl : public GUIWidget
    {
    public:
        
        virtual int HandleEvent( const cg::GUIEvent &event );
        virtual int onEvent( const cg::GUIEvent &event );
        virtual int onAction(cg::uint event);
        
        GUIModuleList* GetModules( GUIEvent::Type type );
        GUIModule* AddModule( GUIModule* module );
        
        virtual bool TestMouseOver(double x, double y);
        void SetMouseOver( bool val );
        bool GetMouseOver() const;
        
        virtual void SetValue( double val ){}
        virtual double GetValue() const {return 0.0;};
        
        void SetState(short value);
        short GetState() const;
        
        void SetEnable(short value);
        bool GetEnable() const;
        virtual ~ GUIControl();
        
    protected:
        
        GUIControl(GUIType type, const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr);
        GUIControl(GUIType type, const ds::string& name, int w, int h, const cg::vec4& colr);
        GUIControl(GUIType type, const ds::string& name, int w, int h);
        GUIControl(GUIType type, const ds::string& name);
        
    protected:
        
        GUIModulMap _modules;
        bool  _mouse_over;
        bool  _enable;
        short _state;
    };
}}
#endif /* GUIControl_hpp */
