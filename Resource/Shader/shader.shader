cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;
	float Fov;
	float Far;
	float padding[2];
}

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

	output.position = mul(position, WorldViewProjection);
	/*
	float fDistance = output.position[2];
	
	float FOVRate = tan(Fov * acos(-1) / 360);

	output.position[0] /= fDistance;
	output.position[0] *= FOVRate;
	output.position[0] = output.position[0] * 2 - 1.0f;

	output.position[1] /= fDistance;%
	output.position[1] *= FOVRate;
	output.position[1] = output.position[1] * 2 - 1.0f;
	
	output.position[2] = fDistance / Far;
	*/
    output.color = color;

    return output;
}


float4 PShader(VOut input) : SV_TARGET
{
    return input.color;
}
