/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUI.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUI_hpp
#define GUI_hpp
#include "Keycode.hpp"
#include "dlist.hpp"
#include "SubSystem.hpp"
#include "../../gui/objects/GUITheme.hpp"
#include "../../gui/objects/GUIView.hpp"
#include "../../gui/objects/GUIRenderer.hpp"
namespace kege{namespace cg{
    
    class GUI : public kege::SubSystem
    {
    public:
        typedef ds::dlist< GUIView* > GUIViews;
        
        void HandleMessage( const kege::Message& message ) override;
        bool OnMouseCursorMove(const kege::Cursor& cursor);
        void OnScrollWheelMove(const kege::Cursor& cursor);
        bool OnMouseButtonPress(const kege::Key& key);
        void OnKeyboardPress(const kege::Key& key);
        
        int onEvent(const cg::GUIEvent& event);

        GUIView* GetView( const ds::string& name );
        GUIView* AddView(GUIView* canvas);
        GUIView* RemView(GUIView* canvas);

        
        GUIWidget* Get(double x, double y);
        
        void SetFocus(GUIWidget* object);
        const GUIWidget* GetFocus() const;
        GUIWidget* GetFocus();
        
        void SetGrabbing( bool val );
        
        void Update( double delta ) override;
        void Render() override;
        void UnInit() override;
        bool Init() override;
        
        ~ GUI();
        GUI();
        
    private:
        
        GUIViews _views;
        GUIRenderer renderer;
        GUIWidget* _active;
        GUIWidget* _focus;
        kege::Cursor _cursor;
        kege::Key _key;
        int state;
        int _grabbing;
    };
}}
#endif /* GUI_hpp */
