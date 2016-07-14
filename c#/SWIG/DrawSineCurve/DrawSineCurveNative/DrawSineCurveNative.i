// 2016-07-14T09:47+08:00
%module DrawSineCurveNative

%{
#include "DrawSineCurve.h"
%}

%include "COLORREF.i"
%include "HDC.i"
%include "RECT.i"

%extend PenProperty {
    PenProperty(PenStyle style, int width, COLORREF color) {
	    PenProperty *pen = new PenProperty();
		pen->Style = style;
		pen->Width = width;
		pen->Color = color;
		return pen;
	}
}

%include "DrawSineCurve.h"


