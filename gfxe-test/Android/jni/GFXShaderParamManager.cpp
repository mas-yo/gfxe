/*
 * GFXStringComparer.cpp
 *
 *  Created on: 2013/04/06
 *      Author: yoshi
 */

#include "GFXStringComparer.h"

using namespace gfxe;
using namespace std;

GFXShaderParamManager::GFXShaderParamManager()
{
    // TODO Auto-generated constructor stub

}

GFXShaderParamManager::~GFXShaderParamManager()
{
    // TODO Auto-generated destructor stub
}

void GFXShaderParamManager::RegisterString( int id, const char* string, int compareLen )
{
    m_vecInfo.resize( m_vecInfo.size() + 1 );
    strInfo& info = m_vecInfo[ m_vecInfo.size() - 1 ];
    info.id = id;
    info.str = string;
    info.compLen = compareLen;
}

int GFXShaderParamManager::GetId( const char* s )
{
    vector<strInfo>::iterator it = m_vecInfo.begin();
    for(; it != m_vecInfo.end(); ++it ) {
        if( !strncmp( it->str, s ) ) {
            return it->id;
        }
    }

    return 0;
}
