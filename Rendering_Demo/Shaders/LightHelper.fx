#ifndef __LIGHTHELPER__
#define __LIGHTHELPER__

float3 GetLightDirection(Light l, float4 surfacePos)
{
	float lightType = l.X_SpotAngleAndY_AttenuationAndZ_LightType.z;
	if (lightType > 0.9 && lightType < 1.1)
		return normalize(-l.Direction.xyz);
	else 
		return normalize(l.Position - surfacePos).xyz;
}

float4 GetLightIntensity(Light l, float4 surfacePos)
{
	float lightType = l.X_SpotAngleAndY_AttenuationAndZ_LightType.z;
	if (lightType > 0.9 && lightType < 1.1)
		return l.Color;
	else
	{
		float d = distance(l.Position, surfacePos);
		if (d < 1)
			return l.Color;
		else
		{
			if (l.X_SpotAngleAndY_AttenuationAndZ_LightType.y < 0.1)
				d = 1;
			else if (l.X_SpotAngleAndY_AttenuationAndZ_LightType.y < 1.1)
				d = d;
			else
				d = d * d;
			return  l.Color / d;
		}
	}

}

float4 Diffuse_Phong(float4 lightColor, float NoH)
{
	return lightColor * NoH;
}

float4 Dis_Phong(float4 lightColor, float VoR, float roughness)
{
	return lightColor * pow(VoR,roughness);
}

#endif
