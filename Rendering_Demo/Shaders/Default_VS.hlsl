//--------------------------------------------------------------------------------------
// Default Vertex Shader
//--------------------------------------------------------------------------------------
#include "common.fx"

float4 main( float4 Pos : POSITION ) : SV_POSITION
{
	float4 output = Pos;
    output = mul( output, gWorld );
    output = mul( output, gView );
    output = mul( output, gProjection );
    return output;
}
