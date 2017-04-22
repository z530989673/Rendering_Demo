//--------------------------------------------------------------------------------------
// Default Pixel Shader
//--------------------------------------------------------------------------------------
#include "Common.fx"
#include "LightHelper.fx"

float4 main( STANDARD_PS_IN input) : SV_Target
{
	//ambient
	float4 output = float4(0.0, 0.0, 0.0, 0.0);
	output += AmbientLightColor * float4(0.2, 0.2, 0.2, 0.0);

	float3 N = normalize(input.Normal);
	float3 V = normalize(EyePosition - input.WorldPos).xyz;

	for(int i =0; i < MAX_LIGHT_NUM; i++)
	{
		if (Lights[i].X_SpotAngleAndY_AttenuationAndZ_LightType.z > 0.1)
		{
			float3 L = GetLightDirection(Lights[i],input.WorldPos);
			float3 H = normalize(L + V);
			float3 R = normalize(N * 2 * dot(L, N) - L);
			float4 Color = GetLightIntensity(Lights[i], input.WorldPos);
			float roughness = 10;
	
			if (dot(V, N) > -0.000001 && dot(L, N) > -0.000001)
			{
				//diffuse 
				float NoH = saturate(dot(N, H));
				output += float4(0.560, 0.570, 0.580, 0.0) * Diffuse_Phong(Color, NoH);

				//specular
				float VoR = saturate(dot(V, R));
				output +=  float4(0.560, 0.570, 0.580, 0.0) * Dis_Phong(Color, VoR, roughness);
			}

			//emission
			//output += float4(0.2, 0.4, 0.5, 0.0);
		}
	}

	return output;
}
