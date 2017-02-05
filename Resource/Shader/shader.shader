cbuffer ConstantBuffer : register( b0 )
{
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;	// ����� World->View�� ��ȯ�ϴ� ��ĸ� ����Ǿ�����
	float Fov; // ī�޶��� �þ߰�
	float Far; // ī�޶��� ����� �Ÿ�
	float ScreenRatio;	// ȭ�� ��Ⱦ��
	float padding; // 16����Ʈ ������ Align
}

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;
	
	position.w = 1.0f;
	output.position = mul(position, ViewMatrix);
	output.position = mul(output.position, ProjectionMatrix);

	output.position /= output.position.w;
	
	output.color = color;

    return output;
}


float4 PShader(VOut input) : SV_TARGET
{
    return input.color;
}
