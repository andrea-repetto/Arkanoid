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

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
//	float3 color : COLOR0;
	float3 normal : TEXCOORD0;
	float3 tangU : TEXCOORD1;
	float2 texC : TEXCOORD2;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
//	float3 color : COLOR0;
	float4 normal : TEXCOORD0;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);
	float4 norm = float4(input.normal, 0.0f);

	// Transform the vertex position into projected space.
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// Pass the color through without modification.
	//output.color = input.color;
	norm = mul(norm, model);
	output.normal = normalize(norm);

	return output;
}
