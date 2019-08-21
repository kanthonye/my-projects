//
//  GenID.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/29/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "GenID.hpp"
namespace kege{
    ds::queue<cg::uint> GenID::ids;
    cg::uint GenID::counter = 0;
}

