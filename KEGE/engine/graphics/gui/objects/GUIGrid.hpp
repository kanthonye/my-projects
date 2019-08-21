/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIGrid.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIGrid_hpp
#define GUIGrid_hpp
#include "array2.hpp"
#include "../../gui/objects/GUIRow.hpp"
#include "../../gui/objects/GUICol.hpp"
#include "../../gui/objects/GUIControl.hpp"
namespace kege{namespace cg{
    
    class GUIGrid : public cg::GUIControl
    {
    public:
        
        const GUICol& operator [](int index)const;
        GUICol& operator [](int index);
        
        int onEvent(const cg::GUIEvent& event) override;
        bool TestMouseOver(double x, double y) override;
        
        void Render(GUIRenderer* renderer)const override;
        void UpdateTransform() override;
        
        GUIWidget* Get(double x, double y) override;
        
        cg::uint Init() override;
        void UnInit() override;
        
        
        GUIGrid(int x, int y, int width, int height, int rows, int cols, const cg::vec4& colr);
        virtual ~ GUIGrid();
        GUIGrid();
        
    private:
        
        ds::array< GUICol > _rows;
    };
}}
#endif /* GUIGrid_hpp */
