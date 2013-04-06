/*
 * GFXStringComparer.h
 *
 *  Created on: 2013/04/06
 *      Author: yoshi
 */

#ifndef GFXSTRINGCOMPARER_H_
#define GFXSTRINGCOMPARER_H_

#include <vector>

namespace gfxe {

class GFXShaderParamManager
{
private:
    struct strInfo {
        int id;
        const char* str;
        int compLen;
    };
    std::vector< strInfo > m_vecInfo;

public:
    GFXShaderParamManager();
    virtual ~GFXShaderParamManager();

    void RegisterString( int id, const char* string, int compareLen );
    int GetId( const char* );
};

}

#endif /* GFXSTRINGCOMPARER_H_ */
