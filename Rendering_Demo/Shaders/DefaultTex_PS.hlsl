//--------------------------------------------------------------------------------------
// Default Pixel Shader
//--------------------------------------------------------------------------------------
#include "Common.fx"

float4 main( SCREEN_PS_IN input) : SV_Target
{
    return gDiffuseMap.Sample( samLinear, input.TexCoord );
}
