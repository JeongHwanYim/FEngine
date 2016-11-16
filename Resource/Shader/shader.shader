cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;	// ����� World->View�� ��ȯ�ϴ� ��ĸ� ����Ǿ�����
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
	
	// ��а� ��� ������ CPU���� �����غ���.
	output.position = position;
	output.color = color;

    return output;
}


float4 PShader(VOut input) : SV_TARGET
{
    return input.color;
}
