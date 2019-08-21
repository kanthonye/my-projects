/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIRow.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIRow_hpp
#define GUIRow_hpp
#include "array.hpp"
#include "../../gui/objects/GUIKnob.hpp"
#include "../../gui/objects/GUIControl.hpp"
namespace kege{namespace cg{
    
    class GUIRow : public cg::GUIControl
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
        
        void Resize(int size);
        cg::uint Init() override;
        void UnInit() override;
        
        GUIRow(const ds::string& name, int x, int y, int w, int h, int divisions, const cg::vec4& colr);
        ~ GUIRow();
        GUIRow();
        
    private:
        
        ds::array< GUIKnob > elems;
    };
}}
#endif /* GUIRow_hpp */
