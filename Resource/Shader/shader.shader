cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;
}

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

	output.position = position;

//	output.position = mul(position, WorldViewProjection);

//	output.position[0] /= output.position[2];

//	output.position[1] /= output.position[2];

    output.color = color;

    return output;
}


float4 PShader(VOut input) : SV_TARGET
{
    return input.color;
}
