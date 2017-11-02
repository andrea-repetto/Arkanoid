// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	//float3 color : COLOR0;
	float4 normal : TEXCOORD0;
};

// A constant buffer that stores the three basic column-major matrices for composing geometry.
struct DirectionalLight
{
	float4 Direction;
	float4 Strength;
};

struct AmbientLight
{
	float4 Strength;
};

struct Material
{
	float4 albedoColor;
};

cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix				model;
	matrix				view;
	matrix				projection;
	DirectionalLight	dirLight;
	AmbientLight		ambientLight;
	Material			material;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	// Scale light down by Lambert's cosine law.
	float ndotl = max(dot(dirLight.Direction, input.normal), 0.0f);
	float4 lightStrength = dirLight.Strength * ndotl;
	
	float4 ambient = ambientLight.Strength * material.albedoColor;
	float4 diffuse = material.albedoColor * lightStrength;
	
	//return ambient;
	return ambient+diffuse;
}
