// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
	float4 normal : TEXCOORD0;
};

// A constant buffer that stores the three basic column-major matrices for composing geometry.
struct DirectionalLight
{
	float3 Direction;
	float3 Strength;
};

struct AmbientLight
{
	float3 Strength;
};

cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
	DirectionalLight dirLight;
	AmbientLight ambientLight;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 dirLightDirection = float4(dirLight.Direction, 0.0f);
	// Scale light down by Lambert's cosine law.
	float ndotl = max(dot(dirLightDirection, input.normal), 0.0f);
	float3 lightStrength = dirLight.Strength * ndotl;

	float4 ambient = float4(ambientLight.Strength, 1.0f)*float4(input.color, 1.0f);
	float4 diffuse = float4(input.color, 1.0f)*float4(lightStrength, 1.0f);

	//return float4(input.color*lightStrength, 1.0f);
	return ambient+diffuse;
}
