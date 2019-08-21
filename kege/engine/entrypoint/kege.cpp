/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 3/1/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       System.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "GameEngine.hpp"
int main(int argc, const char * argv[])
{
    static kege::GameEngine* game = nullptr;
    if (game == nullptr)
    {
        game = kege::CreateGameInstance( argv[0] );
        if (game != nullptr)
        {
            game->Run();
            delete game;
            game = nullptr;
        }
    }
    return 0;
}
