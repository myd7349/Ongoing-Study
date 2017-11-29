#! /usr/bin/env python3
# coding: utf-8

# 2017-11-29T18:56+08:00

# In GDI/GDI+, the PolyBezier/DrawBezier functions draw cubic Bézier curves
# by using the endpoints and control points specified by the parameters.
# Then, how to draw a Quadratic Bézier Curve with GDI/GDI+?
# Here is an example.


import clr  # pip install pythonnet
clr.AddReference('System.Windows')
from System import (
    ArgumentException, 
    Array,
    )
import System.Windows.Forms as WinForms
from System.Drawing import (
    Color,
    Pen,
    PointF,
    Size,
    SizeF,
    )
from System.Drawing.Drawing2D import (
    GraphicsPath,
    SmoothingMode,
    )


class MainForm(WinForms.Form):
    def __init__(self):
        self._InitializeComponent()
        
        self.DoubleBuffered = True
        self.CenterToScreen()
        
    def _InitializeComponent(self):
        self.SuspendLayout()
        self.AutoScaleDimensions = SizeF(6.0, 12.0)
        self.AutoScaleMode = WinForms.AutoScaleMode.Font
        self.ClientSize = Size(640, 480)
        self.Text = 'Draw Quadratic Bézier Curve Demo'
        self.LayOut = self._OnLayout
        self.Paint += self._OnPaint
        self.SizeChanged += self._OnSizeChanged  # What if we comment out this line???
        self.ResumeLayout()
        
    def _OnLayout(self, sender, e):
        self.Invalidate()
        
    def _OnSizeChanged(self, sender, e):
        self.Invalidate()
        
    def _OnPaint(self, sender, e):
        offset = 25.0
        
        P0 = PointF(offset, offset)
        P1 = PointF(offset, self.ClientRectangle.Bottom - offset);
        P2 = PointF(self.ClientRectangle.Right - offset, self.ClientRectangle.Bottom - offset);
        points = Array[PointF]((P0, P1, P2))
        
        pen = Pen(Color.Blue, 6.0)
        
        e.Graphics.SmoothingMode = SmoothingMode.AntiAlias
        
        # 0. The wrong way. The reason is explained in:
        # Ongoing-Study/algorithm/graphics/BezierCurve/DeCasteljau.hpp
        e.Graphics.DrawBezier(pen, P0, P1, P1, P2)
        
        # 1. Draw nothing
        e.Graphics.DrawBeziers(pen, points)
        
        # 2. ArgumentException
        #https://stackoverflow.com/questions/1447659/draw-quadratic-curve
        try:
            path = GraphicsPath()
            path.AddBeziers(points)
            e.Graphics.DrawPath(pen, path)
        except ArgumentException as ex:
            print(ex.Message)
            
        # 3.
        # Convert a quadratic Bezier curve to a cubic Bezier curve, and then
        # draw it with DrawBezier.
        # https://stackoverflow.com/questions/3162645/convert-a-quadratic-bezier-to-a-cubic
        CP0 = P0
        CP1 = PointF(
            P0.X + 2.0 / 3.0 * (P1.X - P0.X),
            P0.Y + 2.0 / 3.0 * (P1.Y - P0.Y))
        CP2 = PointF(
            P2.X + 2.0 / 3.0 * (P1.X - P2.X),
            P2.Y + 2.0 / 3.0 * (P1.Y - P2.Y))
        CP3 = P2
        e.Graphics.DrawBezier(pen, CP0, CP1, CP2, CP3)
        
    def run(self):
        WinForms.Application.Run(self)
        
        
def main():
    form = MainForm()
    app = WinForms.Application
    app.Run(form)
    

if __name__ == '__main__':
    main()
    
    
# References:
# http://pythonnet.github.io/
