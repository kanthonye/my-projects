/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIText.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIText_hpp
#define GUIText_hpp
#include "../../gui/objects/Font.hpp"
#include "../../gui/objects/GUIWidget.hpp"
namespace kege{namespace cg{
    
    class GUIText : public GUIWidget
    {
    public:
        
        inline void SetText(const ds::string& text) {_text = text;}
        inline const ds::string* GetText() const {return &_text;}
        inline ds::string* GetText() {return &_text;}
        
        float GetLetterSpacing() const {return _letter_spacing;}
        float GetWordSpacing() const {return _word_spacing;}
        bool GetWrapAround() const {return _wrap_around;}
        short GetFontSize() const {return _font_size;}
        
        
        short GetFontID() const {return _font_id;}
        void Render(GUIRenderer* renderer) const;
        
        GUIText(int x, int y, const cg::vec4& colr, const ds::string& text);
        ~ GUIText(){}
        GUIText();
        
    private:
        
        ds::string _text;
        float _letter_spacing;
        float _word_spacing;
        short _font_size;
        short _font_id;
        bool _wrap_around;
    };
}}
#endif /* GUIText_hpp */
