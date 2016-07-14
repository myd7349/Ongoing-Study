// 2016-07-14T13:02+08:00
// typemap for RECT
struct RECT {
  %extend {
      RECT(int left, int top, int right, int bottom) {
	      RECT *rc = new RECT();
	      rc->left = left;
		  rc->top = top;
		  rc->right = right;
		  rc->bottom = bottom;
		  return rc;
	  }
  }

  LONG left;
  LONG top;
  LONG right;
  LONG bottom; 
};

%typemap(cstype) const RECT & "System.Drawing.Rectangle"
%typemap(csin, 
         pre="    RECT temp$csinput = new RECT($csinput.Left, $csinput.Top, $csinput.Right, $csinput.Bottom);"
        ) const RECT &
         "$csclassname.getCPtr(temp$csinput)"
%typemap(cstype) RECT & "out System.Drawing.Rectangle"
%typemap(csin,
         pre="    RECT temp$csinput = new RECT();",
         post=" $csinput = new System.Drawing.Rectangle(temp$csinput.left,"
              " temp$csinput.top, temp$csinput.right - temp$csinput.left, temp$csinput.bottom - temp$csinput.top);",
         cshin="out $csinput"
        ) RECT &
         "$csclassname.getCPtr(temp$csinput)"

// References:
// SWIG 3.0 Documentation
// -- 20.8 C# Typemap examples
