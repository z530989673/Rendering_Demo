//--------------------------------------------------------------------------------------
// Default Vertex Shader
//--------------------------------------------------------------------------------------
#include "Common.fx"

STANDARD_PS_IN main( STANDARD_VS_IN input)
{
	STANDARD_PS_IN output;
    output.Pos = mul(float4(input.Pos.xyz, 1.0f), gWorldViewProj );
    output.TexCoord = input.TexCoord;
    output.Normal = mul(float4(input.Normal.xyz,0.0f), gWorldInvTranspose).xyz;
	output.WorldPos = mul( float4(input.Pos.xyz, 1.0f), gWorld);
    return output;
}
