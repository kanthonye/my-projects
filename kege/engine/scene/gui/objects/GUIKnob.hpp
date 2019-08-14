/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIKnob.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIKnob_hpp
#define GUIKnob_hpp
#include "../../gui/objects/GUIWidget.hpp"
namespace kege{namespace cg{
    
    /**
     * GUIKnob is a kind of vessel that can only contain a single GUIWidget.
     * It is the main container used in GUIGrid, GUICol, GUIRow and any other
     * GUIWidget that can use a container that only needs one child element
     */
    class GUIKnob : public cg::GUIWidget
    {
    public:
        
        int onEvent(const cg::GUIEvent& event);
        bool TestMouseOver(double x, double y);
        
        void Render(GUIRenderer* renderer) const;
        
        void SetElem( cg::GUIWidget* elem );
        const cg::GUIWidget* GetElem()const;
        cg::GUIWidget* GetElem();
        
        void UpdateTransform();
        
        bool IsOccupied() const;
        bool FreeElem();
        
        cg::uint Init();
        void UnInit();
        
        
        GUIKnob( const GUIKnob& knob );
        ~ GUIKnob();
        GUIKnob();
        
    private:
        
        cg::GUIWidget* elem;
        bool occupied;
    };
    
}}
#endif /* GUIKnob_hpp */
