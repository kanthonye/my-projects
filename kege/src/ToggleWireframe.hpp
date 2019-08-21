/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/17/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ToggleWireframe.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ToggleWireframe_hpp
#define ToggleWireframe_hpp
#include "Object.hpp"
#include "Keycode.hpp"
#include "Graphics.hpp"
namespace kege{
    
    
    class ToggleWireframe : public kege::Object
    {
    public:
        
        void HandleMessage( const kege::Message& message )
        {
            if (message.GetType() == kege::MSG::COMMAND )
            {
                kege::MsgCommand& msg = (kege::MsgCommand&) message;
                if (msg.command == kege::MSG::WIRE_FRAME )
                {
                    
                    if ( !pressed && msg.action )
                    {
                        pressed = true;
                        toggle = !toggle;
                    }
                    else if ( !msg.action )
                    {
                        pressed = false;
                    }
                    
                    if (toggle)
                    {
                        gfx::Graphics::EnableWireFrame();
                    }
                    else
                    {
                        gfx::Graphics::EnableFillFrame();
                    }
                }
            }
        }
        
        bool onKey(const kege::Key& key)
        {
            if (!pressed)
            {
                pressed = true;
                toggle = !toggle;
            }
            else if (!key.action)
            {
                pressed = false;
            }
            
            if (toggle)
            {
                gfx::Graphics::EnableWireFrame();
            }
            else
            {
                gfx::Graphics::EnableFillFrame();
            }
            return false;
        }
        ToggleWireframe()
        :   settings()
        ,   toggle(false)
        ,   pressed(false)
        {
        }
        ~ ToggleWireframe()
        {
            if (settings != nullptr)
            {
                delete settings;
                settings = nullptr;
            }
        }
        
        core::RenderContext* settings;
        bool toggle;
        bool pressed;
    };
}
#endif /* ToggleWireframe_hpp */
