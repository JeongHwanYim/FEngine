cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;	// 현재는 World->View로 변환하는 행렬만 적용되어있음
	float Fov; // 카메라의 시야각
	float Far; // 카메라의 원평면 거리
	float ScreenRatio;	// 화면 종횡비
	float padding; // 16바이트 단위로 Align
}

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

	// World->View로 좌표값 변환
	output.position = mul(position, WorldViewProjection);

	// 카메라는 Z축을 바라보고 있다. Z값을 기준으로 x, y를 Normalize.
	float fDistance = output.position[2];
	
	float FOVRate = tan(Fov / 2 * acos(-1) / 180);

	// Normalize
	output.position[0] /= fDistance;
	// FOV Rate를 곱해서 카메라 시야각에 맞는 위치 계산
	output.position[0] *= FOVRate;
	// Screen 좌표에서 x축과 y축의 값의 범위는 [-1, 1]이므로, 이 안에 맞도록 좌표값 수정
	output.position[0] = output.position[0] * 2 - 1.0f;
	// 화면 종횡비를 곱해준다.
	output.position[0] /= ScreenRatio;

	// y값
	output.position[1] /= fDistance;
	output.position[1] *= FOVRate;
	output.position[1] = output.position[1] * 2 - 1.0f;
	
	// z값은 Far 값을 기준으로 나눠준다.
	output.position[2] = fDistance / Far;

    output.color = color;

    return output;
}


float4 PShader(VOut input) : SV_TARGET
{
    return input.color;
}
