#pragma once

#include "gamex86.h"

void iHudDraw3d(int cl_num, int index, vec3_t vector, int ent_num, qboolean bAlwaysShow, qboolean depth);
void iHudDrawShader(int cl_num, int info, const char *name);
void iHudDrawAlign(int cl_num, int info, int horizontalAlign, int verticalAlign);
void iHudDrawRect(int cl_num, int info, int x, int y, int width, int height);
void iHudDrawVirtualSize(int cl_num, int info, int virtualScreen);
void iHudDrawColor(int cl_num, int info, float r, float g, float b);
void iHudDrawAlpha(int cl_num, int info, float alpha);
void iHudDrawString(int cl_num, int info, const char *string);
void iHudDrawFont(int cl_num, int info, const char *fontName);
void iHudDrawTimer(int cl_num, int index, float duration, float fade_out_time);

