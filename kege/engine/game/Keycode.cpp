//
//  Keycodes.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 5/22/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "Keycode.hpp"
namespace kege {

    void kege::Key::Set(int key, int action, int mod)
    {
        this->action = action;
        this->key = key;
        this->mod = mod;
    }
    
    bool kege::Key::IsKey(short k)const
    {
        return key == k;
    }
    bool kege::Key::IsRelease()const
    {
        return action == KEY_RELEASE;
    }
    bool kege::Key::IsRepeat()const
    {
        return action >= KEY_REPEAT;
    }
    bool kege::Key::IsPress()const
    {
        return action == KEY_PRESS;
    }
    bool kege::Key::IsDown()const
    {
        return IsPress() || IsRepeat();
    }
    short kege::Key::GetAction()const
    {
        return action;
    }
    short kege::Key::GetKey()const
    {
        return key;
    }
    short kege::Key::GetMod()const
    {
        return mod;
    }
    kege::Key::Key(int key, int action, int mod)
    :   action(action)
    ,   key(key)
    ,   mod(mod)
    {}
    kege::Key::Key()
    :   action(0)
    ,   key(0)
    ,   mod(0)
    {}
    
    
    
    

    kege::Button::Button(int key, int action, int mod)
    :   kege::Key(key, action, mod)
    ,   x(0.0)
    ,   y(0.0)
    {}
    kege::Button::Button()
    :   kege::Key(0, 0, 0)
    ,   x(0.0)
    ,   y(0.0)
    {}
    
    
    void kege::Cursor::Update(double px, double py)
    {
        if (x == 0) x = px;
        if (y == 0) y = py;
        dx = px - x;
        dy = py - y;
        x = px;
        y = py; 
    }
    
    void kege::Cursor::SetXY(double px, double py)
    {
        x = px;
        y = py;
        
        if (isinf(x) || isnan(x))
        {
            KEGE_ERROR("Cursor SetXY invalide value X\n");
            x = 0;
        }
        if (isinf(y) || isnan(y))
        {
            KEGE_ERROR("Cursor SetXY invalide value Y\n");
            y = 0;
        }
    }
    double kege::Cursor::GetDx()const
    {
        return dx;
    }
    double kege::Cursor::GetDy()const
    {
        return dy;
    }
    double kege::Cursor::GetX()const
    {
        return x;
    }
    double kege::Cursor::GetY()const
    {
        return y;
    }
    bool kege::Cursor::Moved()const
    {
        return (dx != 0 || dy != 0);
    }
    kege::Cursor::Cursor(double x, double y)
    :   dx(0)
    ,   dy(0)
    ,   x(0)
    ,   y(0)
    ,   state(0)
    ,   key(0)
    {
        Update(x, y);
    }
    kege::Cursor::Cursor()
    :   dx(0)
    ,   dy(0)
    ,   x(0)
    ,   y(0)
    ,   state(0)
    ,   key(0)
    {}
}


