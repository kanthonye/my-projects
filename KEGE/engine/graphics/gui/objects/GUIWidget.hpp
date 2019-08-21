/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIWidget.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIObject_hpp
#define GUIObject_hpp
#include <map>
#include <vector>
#include "string.hpp"
#include "Object.hpp"
#include "../../gui/events/GUIEvent.hpp"
#include "../../gui/actions/GUIAction.hpp"
#include "../../gui/modules/GUIModule.hpp"
namespace kege{namespace cg{
    class GUIManager;
    class GUIRenderer;
    class GUIControl;
    class GUIView;
    class GUI;
    
    enum GUIType { ELEMENT, TEXT, BUTTON, WIDGET, PANEL, VESSEL, ROW, COL, GRID };
    
    class GUIWidget : public kege::Object
    {
    public:
        
        static bool ReleaseControl(GUIWidget* contr);
        static void SetControl(GUIWidget* contr);
        static GUIWidget* GetControl();
        static bool ControlIsActive();
        static void FreeControl();
        
        inline const cg::vec3& GetLocalPosition() const {return _local_position;}
        inline const cg::vec3& GetWorldPosition() const {return _world_position;}
        inline       cg::vec3& GetLocalPosition()       {return _local_position;}
        inline       cg::vec3& GetWorldPosition()       {return _world_position;}
        
        virtual int onEvent(const cg::GUIEvent& event);
        virtual int onAction(cg::uint event);
        
        virtual void HandleMessage( const kege::Message& message );
        
        virtual bool TestMouseOverConst(double x, double y) const;
        virtual bool TestMouseOver(double x, double y);
        
        inline GUIType GetType()const {return _type;}
        
        virtual void SetState( short value ) { }
        virtual short GetState() const {return 0;}
        
        virtual void SetMouseOver( bool val );
        virtual bool GetMouseOver() const;
        
        virtual void Render( GUIRenderer* renderer ) const;
        virtual void UpdateTransform();
        
        virtual GUIWidget* Get(double x, double y);
        
        virtual const GUIManager* GetGUIMgr()const;
        virtual GUIManager* GetGUIMgr();
        
        virtual cg::uint Init();
        virtual void UnInit();
        
        void SetParent( cg::GUIWidget* parent );
        const cg::GUIWidget* GetParent() const;
        cg::GUIWidget* GetParent();
        cg::GUIWidget* GetRoot();
        
        virtual void SetSystem(GUI* system);
        const GUI* GetSystem()const;
        GUI* GetSystem();
        
        void SetName( const ds::string& name );
        const ds::string& GetName() const;
        ds::string& GetName();
        
        void SetColor(const cg::vec4& color);
        const cg::vec4& GetColor() const;
        cg::vec4& GetColor();
        
        void SetTexel(const cg::vec4& texel);
        const cg::vec4& GetTexel() const;
        cg::vec4& GetTexel();
        
        void  SetHeight(short value);
        short GetHeight() const;
        
        void  SetWidth(short value);
        short GetWidth() const;
        
        void SetVisible(bool value);
        bool IsVisible()const;
        
        void SetActive(bool value);
        bool IsActive()const;
        
        bool IsInit() const;
        
        cg::GUIWidget* GetNext();
        cg::GUIWidget* GetPrev();
        
        GUIWidget(const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr);
        GUIWidget(const ds::string& name, int w, int h, const cg::vec4& colr);
        GUIWidget(const ds::string& name, int w, int h);
        GUIWidget(const ds::string& name);
        virtual ~ GUIWidget();
        
    protected:
        
        GUIWidget(GUIType type, const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr);
        GUIWidget(GUIType type, const ds::string& name, int w, int h, const cg::vec4& colr);
        GUIWidget(GUIType type, const ds::string& name, int w, int h);
        GUIWidget(GUIType type, const ds::string& name);
        
    protected:
        
        cg::point3     _local_position;
        cg::point3     _world_position;
        cg::GUIWidget* _parent;
        GUI*           _system;
        ds::string     _name;
        cg::vec4       _color;
        cg::vec4       _texel;
        GUIType        _type;
        short          _height;
        short          _width;
        bool           _visible;
        bool           _active;
        bool           _init;
        
    private:
        
        static GUIWidget* control;
        static bool take_control;
        
        friend GUIManager;
        cg::GUIWidget* _next;
        cg::GUIWidget* _prev;
    };
    
    typedef std::vector<GUIWidget*> GUIObjectList;
}}
#endif /* GUIObject_hpp */
