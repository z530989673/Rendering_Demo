//--------------------------------------------------------------------------------------
// Default Vertex Shader
//--------------------------------------------------------------------------------------
#include "common.fx"

float4 main( float3 Pos : POSITION ) : SV_POSITION
{
	float4 output = float4(Pos, 1.0f);
    output = mul( output, gWorldViewProj );
    return output;
}
