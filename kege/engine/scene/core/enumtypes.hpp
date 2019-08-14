/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       enumtypes.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#ifndef enumtypes_h
#define enumtypes_h
namespace kege{
    
    enum ERROR
    {
        SUCCESSFUL_INITIALIZATION = 1,
        FAILED_INITIALIZATION,
        ERROR_REQUIRED_CORE_SYSTEM,
        ERROR_NULL_WINDOW
    };
    
    struct ENUM
    {
        enum
        {
            _NONE,
            _INT,
            _CHAR,
            _SHORT,
            _FLOAT,
            _DOUBLE,
            _STRING,
            _SLIST,
            _DLIST,
            _STACK,
            _QUEUE,
            _ARRAY,
            _BIT8,
            _BIT32,
            _BIT64,
            _BITVEC,
            _VEC2,
            _VEC3,
            _VEC4,
            _QUAT,
            _MAT22,
            _MAT33,
            _MAT44,
            _GRAD,
            _WINDOW,
            _GLWINDOW,
            _MOUSE,
            _MOUSE_CURSOR,
            _KEYBOARD,
            _KEYBOARD_KEY,
            _INPUT,
            _INPUT_MANAGER,
            _SYSTEM_INPUT_MANAGER,
            _USER_INTERFACE,
            _FBO,
            _UBO,
            _DATABUFFER,
            _INDEX_BUFFER,
            _VERTEX_BUFFER,
            _MESH,
            _CAMERA,
            _FRUSTUM,
            _LIGHT,
            _MATERIAL,
            _TEXTURE,
            _TEXTURE_2D,
            _TEXTURE_CUBE,
            _TRANSFORM,
            _RIGIDBODY,
            _PROGRAM,
            _UNIFORM,
            _SHADER_LOADER,
            _SHADER_PARSER,
            _SHADER_SOURCE,
            _SHADER_PROGRAM,
            _OBJECT,
            _GAMEOBJECT,
            _COMPONENT,
            _ENTITY_COMPONENT,
            
            _COMPONENT_INPUT,

            _COMPONENT_TIMER,
            _COMPONENT_PHYSICS,
            _COMPONENT_FALLOW,
            _COMPONENT_MOVEMENT,
            _COMPONENT_ROTATION,
            _ROTBYCAM_COMPONENT,
            _SKELETAL_ANIMATOR,
            _PARTICLE,
            _PARTICLE_EMITTER,
            _PARTICLE_GENERATOR,
            _PARTICLE_SYSTEM,
            _COMPONENT_JUMP,
            
            _RENDERABLE,
            
            _SCENE,
            _SCENE_NODE,
            _SCENE_JOINT,
            _SCENE_LIGHT,
            _SCENE_CAMERA,
            _SCENE_ENTITY,
            _SCENE_TERRAIN,
            _SCENE_GAMEOBJECT,
            _SCENE_SKY,
            
            _CONTROL_JUMP,
            _CONTROL_MOTION,
            _CONTROL_ROTATION,
            
            _COLLIDER_COMPONANT,
            _COLLIDER_AABB,
            _COLLIDER_OBB,
            _COLLIDER_SPHERE,
            _COLLIDER_PLANE,
            _COLLISION_CONE,
            _COLLISION_CYLINDER,
            _TILE_LOAD,
            _TERRAIN_TILE,
            _TERRAIN_PAGER,
            _TILE_MSG_HANDLER,
            
            _RENDERER,
            _RENDERER_ENTITY,
            _RENDERER_TERRAIN,
            _RENDERER_LIGHT,
            _OBJECT_RENDERER,
            _LIGHT_RENDERER,
            _RENDERER_ATMOSPHERE,
            _RESRMNGR,
            _RESRMNGR_SYSTEM,
            _MAPLIST,
            _XML,
            _VFS,
            _LOGGER,
            _MESSAGE,
            _MSG_T,
            _MESSENGER,
            _CHANNEL,
            _RADIO,
            _Core,
            
            _SELECT_OBJECT,
            
            COMP_DECAY,
            
            _GUI,
            _GUI_OBJ,
            _GUI_TEXT,
            _GUI_NODE,
        };
    };
}
#endif /* enumtypes_h */
