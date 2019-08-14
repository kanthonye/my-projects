/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIVessel.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIVessel_hpp
#define GUIVessel_hpp
#include "../../gui/objects/GUIWidget.hpp"
#include "../../gui/objects/GUIManager.hpp"
namespace kege{namespace cg{
    
    class GUIVessel : public GUIWidget
    {
    public:
        
        virtual int onEvent(const cg::GUIEvent& event) override;
        virtual bool TestMouseOver(double x, double y) override;
        
        virtual GUIWidget* AddGUI(GUIWidget* object);
        virtual bool RemGUI(GUIWidget* object);
        
        virtual GUIWidget* Get(double x, double y) override;
        
        void Render(GUIRenderer* renderer) const override;
        void SetSystem(cg::GUI* gui) override;
        void UpdateTransform() override;
        
        const GUIManager* GetGUIMgr()const override;
        GUIManager* GetGUIMgr() override;
        
        virtual cg::uint Init() override;
        virtual void UnInit() override;
        
        GUIVessel(const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr);
        GUIVessel(const ds::string& name, int w, int h, const cg::vec4& colr);
        GUIVessel(const ds::string& name, int w, int h);
        GUIVessel(const ds::string& name);
        ~ GUIVessel();
        
    protected:
        
        GUIManager _manager;
    };
}}
#endif /* GUIVessel_hpp */
