#include "blur_shader.h"

technique PostProcessBlur
{
	pass p0
	{
		addressu[0] = clamp;
		addressv[0] = clamp;
		addressu[1] = clamp;
		addressv[1] = clamp;
		addressu[2] = clamp;
		addressv[2] = clamp;
		addressu[3] = clamp;
		addressv[3] = clamp;

		ZEnable = false;
		AlphaTestEnable = false;
		AlphaBlendEnable = false;
		fogEnable = false;

		PixelShader = SHADER;
	}
}