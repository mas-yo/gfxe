//
//  GFXRenderManager.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/09.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFXRenderManager.h"
#include "gfxe.h"
#include "GFXCamera.h"
#include <algorithm>

using namespace std;
using namespace gfxe;

//void GFXRenderer::AddRenderable( IRenderable* pRenderable )
//{
//    lock_guard< std::mutex > lock( m_mutex );
//
//    if( std::find( m_vecRenderable.begin(), m_vecRenderable.end(), pRenderable ) == m_vecRenderable.end() ) {
//        m_vecRenderable.push_back( pRenderable );
//    }
//}

GFXRenderer::~GFXRenderer()
{
}

void GFXRenderer::addFunc(void *obj, std::function<void ()> func)
{
    ObjFunc objFunc = { obj, func };
    _functions.push_back( objFunc );
}

void GFXRenderer::removeFunc( void* obj )
{
    auto end = std::remove_if( _functions.begin(), _functions.end(), [obj]( ObjFunc& objFunc ) -> bool { return objFunc._obj == obj; } );
    _functions.erase( end, _functions.end() );
}

void GFXRenderer::render()
{
    for( auto it = _functions.begin(); it != _functions.end(); ++it ) {
        it->_func();
    }
}

void GFXRenderManager::addFunc(void *obj, std::function<void ()> func, int renderGroup)
{
    _renderers[renderGroup].addFunc( obj, func );
}

void GFXRenderManager::removeFunc( void* obj )
{
    for( GFXRenderer& renderer : _renderers ) {
        renderer.removeFunc( obj );
    }
}

void GFXRenderManager::render()
{
    _renderers[ RenderGroup_Solid ].render();

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    _renderers[ RenderGroup_Alpha ].render();

}
