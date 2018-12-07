#include "grass_shader.h"

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

		VertexShader = SHADER;
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

		VertexShader = SHADER;
	}
}
