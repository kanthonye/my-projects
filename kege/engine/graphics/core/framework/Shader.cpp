/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Shader.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../../graphics/core/framework/Shader.hpp"
namespace kege{namespace core{
    void Shader::SetName(ds::string const& n)
    {
        name = n;
    }
    ds::string const& Shader::GetName()const
    {
        return name;
    }
    ds::string & Shader::GetName()
    {
        return name;
    }
}}
