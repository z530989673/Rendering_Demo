//--------------------------------------------------------------------------------------
// Default Vertex Shader
//--------------------------------------------------------------------------------------
#include "common.fx"

STANDARD_PS_IN main( STANDARD_VS_IN input)
{
	STANDARD_PS_IN output;
    output.Pos = mul( float4(input.Pos, 1.0f), gWorldViewProj );
    output.TexCoord = input.TexCoord;
    output.Normal = input.Normal;
	output.WorldPos = float4(input.Pos, 1.0f);
    return output;
}
