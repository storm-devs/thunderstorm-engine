VertexShader WdmCloudsVS
{
	decl
	{
        stream[0];

        float position[3];	//Position
		color;				//color
		float texcoord[2];	//uv1
    }
    
	asm
	{
		vs.1.1

		dcl_position v0
		dcl_color v1
		dcl_texcoord v2

		//Позиция
		mov  r0, v0
		mul  r1, r0.xxxx, c[0]
		mad  r1, r0.yyyy, c[1], r1
		mad  r1, r0.zzzz, c[2], r1
		add  oPos, r1, c[3]
		//Цвет
		mov  oD0, v1.xxxw
		mul  oD1, v1.yyyw, c[6]
		//Текстурные координаты первой стадии
		mov  oT0, v2
		//Генерим текстурные координаты второй стадии
		//Длинна вектора для данного квадрата
		mov  r2, c[5]
		mad  r2.w, v1.z, r2.z, r2.x
		//Вертикальная компонента вектора
		dp4  r1, r0, c[4]
		//Нормализуем и приводим к единичному диапазону
		rcp  r2.w, r2.w
		mad  r1.w, r1.w, r2.w, c[5].w
		mov oT1, r1.wwww
	}
}