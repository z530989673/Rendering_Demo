//--------------------------------------------------------------------------------------
// Default Pixel Shader
//--------------------------------------------------------------------------------------
#include "common.fx"

float4 main( STANDARD_PS_IN input) : SV_Target
{
	//ambient
	float4 output = float4(0.0, 0.0, 0.0, 0.0);
	output += AmbientLightColor * float4(0.2, 0.2, 0.2, 0.0);

	float3 N = input.Normal;
	float3 V = normalize(EyePosition - input.WorldPos);
	float3 L = normalize(-Lights[0].Direction.xyz);
	
	if (dot(V, N) > 0 && dot(L, N) > 0)
	{
		//diffuse
		float3 H = normalize(L + V);
		float cosTheta = dot(N, H);
		output += Lights[0].Color * float4(0.5, 0.5, 0.5, 0.0) * cosTheta;

		//specular
		float n = 10;
		float3 R = N * 2 - L;
		float cosAlpha = dot(V, R);
		output += Lights[0].Color * float4(0.5, 0.5, 0.5, 0.0) * pow(cosAlpha,n);
	}

	//emission
	//output += float4(0.2, 0.4, 0.5, 0.0);

	return output;
}
