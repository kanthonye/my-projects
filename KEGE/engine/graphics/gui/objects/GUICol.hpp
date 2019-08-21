/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUICol.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUICol_hpp
#define GUICol_hpp
#include "array.hpp"
#include "../../gui/objects/GUIKnob.hpp"
#include "../../gui/objects/GUIControl.hpp"
namespace kege{namespace cg{
    
    class GUICol : public cg::GUIControl
    {
    public:
        
        void SetSize(int w, int h, int divs, const cg::vec4& colr);
        
        const GUIKnob& operator [](int index)const;
        GUIKnob& operator [](int index);
        
        void SetElem(int index, cg::GUIWidget* widget);
        const cg::GUIWidget* GetElem(int index) const;
        cg::GUIWidget* GetElem(int index);
        
        int onEvent(const cg::GUIEvent& event) override;
        bool TestMouseOver(double x, double y) override;
        void Render(GUIRenderer* renderer)const override;
        void UpdateTransform() override;
        
        GUIWidget* Get(double x, double y) override;
        
        cg::uint Init() override;
        void UnInit() override;
        
        GUICol(const ds::string& name, int x, int y, int w, int h, int divisions, const cg::vec4& colr);
        ~ GUICol();
        GUICol();
        
    private:
        
        ds::array< GUIKnob > elems;
    };
}}
#endif /* GUICol_hpp */
