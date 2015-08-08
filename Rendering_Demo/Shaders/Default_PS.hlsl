//--------------------------------------------------------------------------------------
// Default Pixel Shader
//--------------------------------------------------------------------------------------
#include "common.fx"

float4 main( float4 Pos : SV_POSITION ) : SV_Target
{
    return float4( 1.0f, 1.0f, 1.0f, 1.0f );    // White, with Alpha = 1
}
