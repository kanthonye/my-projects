/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Interface.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef kege_Interface_hpp
#define kege_Interface_hpp
#include <map>
#include "dlist.hpp"
#include "Keycode.hpp"
#include "../../scene/core/Object.hpp"
namespace kege{
    
    class Interface
    {
    public:
        
        bool Bind( short key, cg::uint command, bool force_bind = false );
        void UnBind( short key, cg::uint command );
        
        void RemvMsgHandler(cg::uint msgtyp, kege::Object* object);
        void AddMsgHandler(cg::uint msgtyp, kege::Object* object);
        void HandleMessage(const kege::Message& message);
        
        void OnMouseCursor(const kege::Cursor& cursor);
        void OnMouseWheel(const kege::Cursor& cursor);
        void OnKey(const kege::Key& key);
        
        Interface();
        
    private:
        
        std::map<long, ds::dlist<kege::Object*>> _message_handlers;
        cg::uint commands[ 512 ];
    };
}
#endif /* Interface_hpp */
