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
	
	// 당분간 모든 연산을 CPU에서 진행해보자.
	output.position = position;
	output.color = color;

    return output;
}


float4 PShader(VOut input) : SV_TARGET
{
    return input.color;
}
