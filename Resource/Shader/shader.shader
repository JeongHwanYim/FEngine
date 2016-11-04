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

	// World->View�� ��ǥ�� ��ȯ
	output.position = mul(position, WorldViewProjection);

	// ī�޶�� Z���� �ٶ󺸰� �ִ�. Z���� �������� x, y�� Normalize.
	float fDistance = output.position[2];
	
	float FOVRate = tan(Fov / 2 * acos(-1) / 180);

	// Normalize
	output.position[0] /= fDistance;
	// FOV Rate�� ���ؼ� ī�޶� �þ߰��� �´� ��ġ ���
	output.position[0] *= FOVRate;
	// Screen ��ǥ���� x��� y���� ���� ������ [-1, 1]�̹Ƿ�, �� �ȿ� �µ��� ��ǥ�� ����
	output.position[0] = output.position[0] * 2 - 1.0f;
	// ȭ�� ��Ⱦ�� �����ش�.
	output.position[0] /= ScreenRatio;

	// y��
	output.position[1] /= fDistance;
	output.position[1] *= FOVRate;
	output.position[1] = output.position[1] * 2 - 1.0f;
	
	// z���� Far ���� �������� �����ش�.
	output.position[2] = fDistance / Far;

    output.color = color;

    return output;
}


float4 PShader(VOut input) : SV_TARGET
{
    return input.color;
}
