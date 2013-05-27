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
    _funcList.push_back( make_tuple( obj, func ) );
}

void GFXRenderer::removeFunc( void* obj )
{
    auto end = std::remove_if( _funcList.begin(), _funcList.end(), [obj]( render_func_t func ) -> bool { return std::get<0>(func) == obj; } );
    _funcList.erase( end, _funcList.end() );
}

void GFXRenderer::render()
{
    for( auto it = _funcList.begin(); it != _funcList.end(); ++it ) {
        std::get<1>(*it)();
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
