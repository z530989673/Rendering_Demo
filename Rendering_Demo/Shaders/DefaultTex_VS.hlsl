//--------------------------------------------------------------------------------------
// Default Vertex Shader
//--------------------------------------------------------------------------------------
#include "common.fx"

SCREEN_PS_IN main( SCREEN_VS_IN input )
{
    SCREEN_PS_IN output = (SCREEN_PS_IN)0;
    output.Pos = mul( input.Pos, gWorld );
    output.Pos = mul( output.Pos, gView );
    output.Pos = mul( output.Pos, gProjection );
    output.TexCoord = input.TexCoord;
    
    return output;
}
