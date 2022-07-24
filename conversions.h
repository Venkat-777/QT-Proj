#ifndef CONVERSIONS_H_
#define CONVERSIONS_H_

#include "shape.h"
#include <string>

using std::string;





namespace convert
{

enum ListTypes
{
    SHAPES,
    COLOR,
    PEN_STYLE,
    PEN_CAP,
    PEN_JOIN,
    BRUSH_STYLE,
    ALIGNMENT_FLAG,
    FONT_STYLE,
    FONT_WEIGHT
};

//******************************************************
struct shapeConversion
{
    Shape::ShapeType e_shapeType;
    string           s_shapeType;
};

const shapeConversion shapeList[]
{
    {Shape::ShapeType::None,        "None"},
    {Shape::ShapeType::Line,        "Line"},
    {Shape::ShapeType::Polyline,    "Polyline"},
    {Shape::ShapeType::Polygon,     "Polygon"},
    {Shape::ShapeType::Rectangle,   "Rectangle"},
    {Shape::ShapeType::Ellipse,     "Ellipse"},
    {Shape::ShapeType::Text,        "Text"},
    {Shape::ShapeType::Circle,      "Circle"},
    {Shape::ShapeType::Square,      "Square"}
};

//******************************************************
struct colorConversion
{
    int             e_color;
    string          s_color;
};

const colorConversion colorList[]
{
    {0xffffff,    "white"},
    {0x000000,    "black"},
    {0xff0000,      "red"},
    {0x00ff00,    "green"},
    {0x0000ff,     "blue"},
    {0x00ffff,     "cyan"},
    {0xff00ff,  "magenta"},
    {0xffff00,   "yellow"},
    {0xa0a0a4,     "gray"}
};

//******************************************************
struct penStyleConversion
{
    Qt::PenStyle    e_penStyle;
    string          s_penStyle;
};

const penStyleConversion penStyleList[]
{
    {Qt::PenStyle::NoPen,          "NoPen"},
    {Qt::PenStyle::SolidLine,      "SolidLine"},
    {Qt::PenStyle::DashLine,       "DashLine"},
    {Qt::PenStyle::DotLine,        "DotLine"},
    {Qt::PenStyle::DashDotLine,    "DashDotLine"},
    {Qt::PenStyle::DashDotDotLine, "DashDotDotLine"}
};

//******************************************************
struct penCapStyleConversion
{
    Qt::PenCapStyle e_capStyle;
    string          s_capStyle;
};

const penCapStyleConversion penCapStyleList[]
{
    {Qt::PenCapStyle::FlatCap,   "FlatCap"},
    {Qt::PenCapStyle::SquareCap, "SquareCap"},
    {Qt::PenCapStyle::RoundCap,  "RoundCap"}
};

//******************************************************
struct penJoinStyleConversion
{
    Qt::PenJoinStyle e_joinStyle;
    string           s_joinStyle;
};

const penJoinStyleConversion penJoinStyleList[]
{
    {Qt::PenJoinStyle::MiterJoin, "MiterJoin"},
    {Qt::PenJoinStyle::BevelJoin, "BevelJoin"},
    {Qt::PenJoinStyle::RoundJoin, "RoundJoin"}
};

//******************************************************
struct brushStyleConversion
{
    Qt::BrushStyle  e_brushStyle;
    string          s_brushStyle;
};

const brushStyleConversion brushStyleList[]
{
    {Qt::BrushStyle::SolidPattern, "SolidPattern"},
    {Qt::BrushStyle::HorPattern,   "HorPattern"},
    {Qt::BrushStyle::VerPattern,   "VerPattern"},
    {Qt::BrushStyle::NoBrush,      "NoBrush"}
};

//******************************************************
struct alignmentFlagConversion
{
    Qt::AlignmentFlag e_fontAlignFlag;
    string            s_fontAlignFlag;
};

const alignmentFlagConversion alignmentFlagList[]
{
    {Qt::AlignmentFlag::AlignLeft,    "AlignLeft"},
    {Qt::AlignmentFlag::AlignRight,   "AlignRight"},
    {Qt::AlignmentFlag::AlignTop,     "AlignTop"},
    {Qt::AlignmentFlag::AlignBottom,  "AlignBottom"},
    {Qt::AlignmentFlag::AlignCenter,  "AlignCenter"}
};

//******************************************************
struct fontStyleConversion
{
    QFont::Style    e_fontStyle;
    string          s_fontStyle;
};

const fontStyleConversion fontStyleList[]
{
    {QFont::Style::StyleNormal,  "StyleNormal"},
    {QFont::Style::StyleItalic,  "StyleItalic"},
    {QFont::Style::StyleOblique, "StyleOblique"}
};

//******************************************************
struct fontWeightConversion
{
    QFont::Weight   e_fontWeight;
    string          s_fontWeight;
};

const fontWeightConversion fontWeightList[]
{
    {QFont::Weight::Thin,   "Thin"},
    {QFont::Weight::Light,  "Light"},
    {QFont::Weight::Normal, "Normal"},
    {QFont::Weight::Bold,   "Bold"},
};

} // namespace

#endif
