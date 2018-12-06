//--------------------------------------------------------------------------------------
// Vertex shader output structure
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 pos : POSITION;
    float4 clr : COLOR;
    float2 uv : TEXCOORD0;
};

//Таблицы
float3 ang_table[16];	//Таблица углов (sin(ay), cos(ay), (fabsf(-cos(ay)*lDir.x + sin(ay)*lDir.z)*0.3f + 0.7f))
float2 uv_table[16];
//Матрица вид*проекцию
float4x4 wpMatrix;
//Параметры освещения
float2 lDir;
float kLitWF;
float3 aColor;
float3 lColor;

//--------------------------------------------------------------------------------------
// This shader computes standard transform and lighting
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float3 pos : POSITION, float4 params : COLOR0, float4 offset : COLOR1, float3 wa : NORMAL)
{
    VS_OUTPUT Output;	
	
	//Надо заменить из кода!!!
	//float kLitWF = 1.23456f;
	
	//Получим ориентацию травинки
	float3 ang = ang_table[params.z*15.0f];
	//Освещение
	float kClr = (wa.x*lDir.x + wa.y*lDir.y);
	kClr = max(kClr, -0.2f/0.4f);
	kClr = min(kClr, 0.4f/0.4f);
	kClr = (kClr*0.4f + ang.z*0.2f)*kLitWF*offset.y;
	Output.clr.xyz = aColor + lColor*kClr;
	Output.clr.w = wa.z;
	//Позиция
	float2 size = params.xy*float2(0.3f*0.6f, 0.4f*0.6f) + float2(0.7f*0.6f, 0.6f*0.6f);
	float4 tmpPos;
	tmpPos.xz = pos.xz - ang.xy*size.xx*(offset.xx - 0.5f) + wa.xy*offset.yy;
	tmpPos.y = pos.y + sqrt(size.y - (wa.x*wa.x + wa.y*wa.y))*offset.y;
	tmpPos.w = 1.0f;
	Output.pos = mul(wpMatrix, tmpPos);
	//Текстурные координаты
	Output.uv = uv_table[params.w*15.0f].xy + offset.xy*float2(0.245f, -0.245f);
	//Всё
    return Output;    
}

technique GrassEx
{
	pass p0
	{
		lighting = false;
		alpharef = 80;
		cullmode = none;

		AlphaTestEnable = true;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;			
		ColorArg1[0] = diffuse;
		ColorArg2[0] = texture;
		ColorOp[0] = modulate2x;
		ColorOp[1] = disable;
		AlphaArg1[0] = diffuse;
		AlphaArg2[0] = texture;
		AlphaOp[0] = modulate;
		AlphaOp[1] = disable;
					
		
		VertexShader = compile vs_1_1 VS();/*asm {
			vs.1.1

			dcl_position v0
			dcl_color v1
			dcl_color1 v2
			dcl_texcoord v3

			mul r0.xy, v3, c36
			add r0.w, r0.y, r0.x
			max r0.w, -r0.w, c40.y
			mul r2.xw, v1.zyzw, c40.x
			min r0.w, r0.w, c40.z
			mov a0.x, r2.x
			mov r0.y, c[a0.x + 0].z
			mul r1.w, r0.y, c40.w
			mad r0.w, r0.w, c39.x, r1.w
			mul r1.w, r0.w, v2.y
			mul r0.xy, v3, v3
			add r0.w, r0.y, r0.x
			mad r0.xy, v1, c41, c41.zwzw
			mul r1.w, r1.w, c39.y
			add r0.w, -r0.w, r0.y
			mul r0.xy, r0.x, c[a0.x + 0]
			rsq r0.w, r0.w
			rcp r0.w, r0.w
			add r3.w, v2.x, c40.y
			mov r3.xy, v2
			//mad r0.w, r0.w, r3.y, v0.y
			mul r0.w, r0.w, r3.y //
			mad r0.w, v0.y, c38.w, r0.w //
			//mad r1.xy, r0, -r3.w, v0.xzzw
			mul r1.xy, r0, -r3.w //
			mad r1.xy, v0.xzzw, c38.w, r1.xy //
			mul r0, r0.w, c33
			mad r2.xy, v3, r3.y, r1
			mov r1.xyz, c38
			mad oD0.xyz, r1, r1.w, c37
			mad r0, c32, r2.x, r0
			mov r1.zw, c39
			mov a0.x, r2.w
			mad oT0.xy, r3, r1.zwzw, c[a0.x + 16]
			mad r0, c34, r2.y, r0
			add oPos, r0, c35
			mov oD0.w, v3.z
		};*/
	}
}

technique GrassEx_dark
{
	pass p0
	{
		lighting = false;
		alpharef = 80;
		cullmode = none;

		AlphaTestEnable = true;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;
		ColorArg1[0] = diffuse;
		ColorArg2[0] = texture;
		ColorOp[0] = modulate;
		ColorOp[1] = disable;
		AlphaArg1[0] = diffuse;
		AlphaArg2[0] = texture;
		AlphaOp[0] = modulate;
		AlphaOp[1] = disable;


		VertexShader = asm {
			vs.1.1

			dcl_position v0
			dcl_color v1
			dcl_color1 v2
			dcl_texcoord v3

			mul r0.xy, v3, c36
			add r0.w, r0.y, r0.x
			max r0.w, -r0.w, c40.y
			mul r2.xw, v1.zyzw, c40.x
			min r0.w, r0.w, c40.z
			mov a0.x, r2.x
			mov r0.y, c[a0.x + 0].z
			mul r1.w, r0.y, c40.w
			mad r0.w, r0.w, c39.x, r1.w
			mul r1.w, r0.w, v2.y
			mul r0.xy, v3, v3
			add r0.w, r0.y, r0.x
			mad r0.xy, v1, c41, c41.zwzw
			mul r1.w, r1.w, c39.y
			add r0.w, -r0.w, r0.y
			mul r0.xy, r0.x, c[a0.x + 0]
			rsq r0.w, r0.w
			rcp r0.w, r0.w
			add r3.w, v2.x, c40.y
			mov r3.xy, v2
			//mad r0.w, r0.w, r3.y, v0.y
			mul r0.w, r0.w, r3.y //
			mad r0.w, v0.y, c38.w, r0.w //
			//mad r1.xy, r0, -r3.w, v0.xzzw
			mul r1.xy, r0, -r3.w //
			mad r1.xy, v0.xzzw, c38.w, r1.xy //
			mul r0, r0.w, c33
			mad r2.xy, v3, r3.y, r1
			mov r1.xyz, c38
			mad oD0.xyz, r1, r1.w, c37
			mad r0, c32, r2.x, r0
			mov r1.zw, c39
			mov a0.x, r2.w
			mad oT0.xy, r3, r1.zwzw, c[a0.x + 16]
			mad r0, c34, r2.y, r0
			add oPos, r0, c35
			mov oD0.w, v3.z
		};
	}
}
