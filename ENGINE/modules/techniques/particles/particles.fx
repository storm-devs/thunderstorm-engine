#include "particles_shaders.h"

technique Particles
{
	pass p0
	{
		CullMode = none;
		AlphaTestEnable = false;
		AlphaBlendEnable = true;
		ZWriteEnable = false;
		FogEnable = true;
		Lighting = false;
		Texcoordindex[0] = 0;
		Colorarg1[0] = texture;
		Colorarg2[0] = current;
		Colorop[0] = modulate;
		ColorOp[1] = disable;
		Srcblend = srcalpha;
		Destblend = invsrcalpha;
		AlphaArg1[0] = texture;
		AlphaArg2[0] = diffuse;
		AlphaOp[1] = disable;
		Alphaop[0] = modulate;
	}
}

technique Particles_Inv
{
	pass p0
	{
		CullMode = none;
		AlphaTestEnable = false;
		AlphaBlendEnable = true;
		ZWriteEnable = false;
		FogEnable = true;
		Lighting = false;
		Texcoordindex[0] = 0;
		Colorarg1[0] = texture_complement;
		Colorarg2[0] = current;
		Colorop[0] = modulate;
		ColorOp[1] = disable;
		Srcblend = srcalpha;
		Destblend = invsrcalpha;
		AlphaArg1[0] = texture;
		AlphaArg2[0] = diffuse;
		AlphaOp[1] = disable;
		Alphaop[0] = modulate;
	}
}


technique Particles_InvOld
{
	pass p0
	{
		CullMode = none;
		AlphaTestEnable = false;
		AlphaBlendEnable = true;
		ZWriteEnable = false;
		FogEnable = true;
		Texcoordindex[0] = 0;
		Colorarg2[0] = tfactor;
		Colorarg1[0] = texture;
		Colorop[0] = blenddiffusealpha;
		ColorOp[1] = disable;
		alphaop[0] = disable;
		TextureFactor = 0xff000000;
		Srcblend = zero;
		Destblend = invsrccolor;
	}
}

technique ParticlesFire
{
	pass p0
	{
		CullMode = none;
		AlphaTestEnable = false;
		AlphaBlendEnable = true;
		ZWriteEnable = false;
		FogEnable = true;
		Lighting = false;
		Texcoordindex[0] = 0;
		Colorarg1[0] = texture;
		Colorarg2[0] = current;
		Colorop[0] = modulate;
		ColorOp[1] = disable;
		Srcblend = srcalpha;
		Destblend = one;
		AlphaArg1[0] = texture;
		AlphaArg2[0] = diffuse;
		AlphaOp[1] = disable;
		Alphaop[0] = modulate;
	}
}

technique AdvancedParticles
{
	pass p0
	{
		FogEnable = false;
		ZWriteenable = false;
	  
		SrcBlend = one;
		DestBlend = invsrcalpha;
		AlphaTestEnable = false;
		AlphaBlendEnable = true;
  
		PixelShader = PIXEL_SHADER;
		VertexShader = VERTEX_SHADER;
	}
}
