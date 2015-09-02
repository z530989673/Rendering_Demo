//--------------------------------------------------------------------------------------
// Default Vertex Shader
//--------------------------------------------------------------------------------------
#include "Common.fx"

STANDARD_PS_IN main( STANDARD_VS_IN input)
{
	STANDARD_PS_IN output;
    output.Pos = mul( float4(input.Pos, 1.0f), gWorldViewProj );
    output.TexCoord = input.TexCoord;
    output.Normal = input.Normal;
	output.WorldPos = mul( float4(input.Pos, 1.0f), gWorld);
    return output;
}
