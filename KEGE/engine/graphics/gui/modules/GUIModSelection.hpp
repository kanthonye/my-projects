/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModSelection.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModSelection_hpp
#define GUIModSelection_hpp
#include "KeyCode.hpp"
#include "../../gui/modules/GUIModule.hpp"
#include "../../gui/modules/GUIModButton.hpp"
namespace kege{namespace cg{
    
    class GUIModSelection : public cg::GUIModButton
    {
    public:
        int onButtonRelease(const cg::GUIEventButton& event) override;
        int onButtonPressed(const cg::GUIEventButton& event) override;
        
        GUIModSelection()
        :   curr( nullptr )
        ,   prev( nullptr )
        ,   _selecttion( false )
        ,   state( 0 )
        {}
        
    private:
        
        GUIWidget* curr;
        GUIWidget* prev;
        cg::ushort state;
        bool _selecttion;
    };
}}


namespace kege{namespace cg{
    
    class GUIModPressSelection : public cg::GUIModButton
    {
    public:
        int onButtonRelease(const cg::GUIEventButton& event) override;
        int onButtonPressed(const cg::GUIEventButton& event) override;
    };
}}


namespace kege{namespace cg{
    
    class GUIModTabSelection : public cg::GUIModButton
    {
    public:
        int onButtonRelease(const cg::GUIEventButton& event) override;
        int onButtonPressed(const cg::GUIEventButton& event) override;
        
        GUIModTabSelection()
        :   curr( nullptr )
        ,   prev( nullptr )
        ,   state( 0 )
        {}
        
    private:
        
        GUIWidget* curr;
        GUIWidget* prev;
        cg::ushort state;
    };
}}





namespace kege{namespace cg{
    
    class GUIModColor : public cg::GUIModule
    {
    public:
        
        int onEvent(const cg::GUIEvent& event) override;
        GUIModColor(GUIEvent::Type type, const cg::vec4& color);
        cg::vec4 color;
    };
}}

namespace kege{namespace cg{
    
    class GUIModColor2 : public cg::GUIModule
    {
    public:
        
        int onAction(cg::uint event) override;
        GUIModColor2(GUIEvent::Type type, const cg::vec4& colr);
        cg::vec4 color;
    };
}}
#endif /* GUIModSelection_hpp */
