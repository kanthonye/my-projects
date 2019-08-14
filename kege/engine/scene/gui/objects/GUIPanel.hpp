/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIPanel.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIPanel_hpp
#define GUIPanel_hpp
#include "../../gui/objects/GUIControl.hpp"
#include "../../gui/objects/GUIManager.hpp"
namespace kege{namespace cg{
    
    class GUIPanel : public GUIControl
    {
    public:
        
        int onEvent(const cg::GUIEvent& event) override;
        bool TestMouseOver(double x, double y) override;
        
        void Render(GUIRenderer* renderer) const override;
        
        GUIWidget* Get(double x, double y) override;
        
        GUIWidget* AddGUI(GUIWidget* object);
        bool RemGUI(GUIWidget* object);
        
        void SetSystem(cg::GUI* gui) override;
        
        const GUIManager* GetGUIMgr()const override;
        GUIManager* GetGUIMgr() override;
        
        cg::uint Init() override;
        void UnInit() override;
        void UpdateTransform() override;
        
        GUIPanel(const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr);
        GUIPanel(const ds::string& name, int w, int h, const cg::vec4& colr);
        GUIPanel(const ds::string& name, int w, int h);
        GUIPanel(const ds::string& name);
        ~ GUIPanel();
        
    protected:
        
        GUIPanel(GUIType type, const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr);
        GUIPanel(GUIType type, const ds::string& name, int w, int h, const cg::vec4& colr);
        GUIPanel(GUIType type, const ds::string& name, int w, int h);
        GUIPanel(GUIType type, const ds::string& name);
        
    protected:
        
        GUIManager _manager;
    };
}}
#endif /* GUIPanel_hpp */
