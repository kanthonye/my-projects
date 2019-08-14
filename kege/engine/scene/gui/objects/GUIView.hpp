/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIView.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIView_hpp
#define GUIView_hpp
#include "../../gui/objects/GUIWidget.hpp"
#include "../../gui/objects/GUIManager.hpp"
#include "../../gui/objects/GUIRenderer.hpp"
namespace kege{namespace cg{
    class GUI;
    
    class GUIView
    {
    public:
        
        
        int onEvent(const cg::GUIEvent& event);
        int TestMouseOver(double x, double y);
        GUIWidget* Add( GUIWidget* widget );
        
        void Render(GUIRenderer* renderer) const;
        void UpdateTransform();
        cg::uint Init();
        void UnInit();
        
        GUIWidget* Get(double x, double y);
        
        void SetFocus(GUIWidget* object);
        const GUIWidget* GetFocus() const;
        GUIWidget* GetFocus();
        
        const ds::string& GetName();
        
        void SetGUI(GUI* gui);
        const GUI* GetGUI() const;
        GUI* GetGUI();
        
        GUIView(const ds::string& name, const cg::mat44& view, const cg::mat44& proj);
        GUIView(const cg::mat44& view, const cg::mat44& proj);
        ~ GUIView();
        
    protected:
        
        cg::mat44 _proj;
        cg::mat44 _view;
        
        ds::string _name;
        GUIManager _manager;
        GUIWidget* _focus;
        GUI* _gui;
    };
}}
#endif /* GUIView_hpp */
