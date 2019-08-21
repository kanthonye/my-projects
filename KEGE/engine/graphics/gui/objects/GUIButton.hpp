/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIButton.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIButton_hpp
#define GUIButton_hpp
#include "../../gui/objects/GUIControl.hpp"
#include "../../gui/objects/GUIModuleList.hpp"
namespace kege{namespace cg{
    
    class GUIButton : public GUIControl
    {
    public:
        
        void SetValue( double val );
        double GetValue() const;
        
        GUIButton(const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr);
        GUIButton(const ds::string& name, int w, int h, const cg::vec4& colr);
        GUIButton(const ds::string& name, int w, int h);
        GUIButton(const ds::string& name);
        virtual ~ GUIButton(){}
        
    protected:
        
        GUIButton(GUIType type, const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr);
        GUIButton(GUIType type, const ds::string& name, int w, int h, const cg::vec4& colr);
        GUIButton(GUIType type, const ds::string& name, int w, int h);
        GUIButton(GUIType type, const ds::string& name);
        
    protected:
        
        double _value;
    };
}}
#endif /* GUIButton_hpp */
