#ifndef CONVERSIONS_H_
#define CONVERSIONS_H_

// shape includes
#include "shape.h"

// pre-processor directives
#include <string>

// using namespaces
using std::string;




// namespace
namespace convert
{

/*******************************************************************************
* ENUMERATED TYPES                                                             *
*******************************************************************************/
// DETERMINES WHICH ENUMERATED TYPE TO CONVERT TO STRING
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



// SHAPE ENUMERATION TYPES
//******************************************************
struct shapeConversion
{
    Shape::ShapeType e_shapeType;
    string           s_shapeType;
};

const int NUM_SHAPES = 9;
const shapeConversion shapeList[NUM_SHAPES]
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



// COLOR ENUMERATION TYPES
//******************************************************
struct colorConversion
{
    string          hex_color;
    string          s_color;
    QColor          e_color;
};

const int NUM_COLORS = 9;
const colorConversion colorList[NUM_COLORS]
{
    {"#ffffff",    "white",    QColorConstants::White},
    {"#000000",    "black",    QColorConstants::Black},
    {"#ff0000",      "red",    QColorConstants::Red},
    {"#00ff00",    "green",    QColorConstants::Green},
    {"#0000ff",     "blue",    QColorConstants::Blue},
    {"#00ffff",     "cyan",    QColorConstants::Cyan},
    {"#ff00ff",  "magenta",    QColorConstants::Magenta},
    {"#ffff00",   "yellow",    QColorConstants::Yellow},
    {"#a0a0a4",     "gray",    QColorConstants::Gray}
};



// PEN STYLE ENUMERATION TYPES
//******************************************************
struct penStyleConversion
{
    Qt::PenStyle    e_penStyle;
    string          s_penStyle;
};

const int NUM_PEN_STYLES = 6;
const penStyleConversion penStyleList[NUM_PEN_STYLES]
{
    {Qt::PenStyle::NoPen,          "NoPen"},
    {Qt::PenStyle::SolidLine,      "SolidLine"},
    {Qt::PenStyle::DashLine,       "DashLine"},
    {Qt::PenStyle::DotLine,        "DotLine"},
    {Qt::PenStyle::DashDotLine,    "DashDotLine"},
    {Qt::PenStyle::DashDotDotLine, "DashDotDotLine"}
};



// PEN CAP STYLE ENUMERATION TYPES
//******************************************************
struct penCapStyleConversion
{
    Qt::PenCapStyle e_capStyle;
    string          s_capStyle;
};

const int NUM_CAP_STYLES = 3;
const penCapStyleConversion penCapStyleList[NUM_CAP_STYLES]
{
    {Qt::PenCapStyle::FlatCap,   "FlatCap"},
    {Qt::PenCapStyle::SquareCap, "SquareCap"},
    {Qt::PenCapStyle::RoundCap,  "RoundCap"}
};



// PEN JOIN STYLE ENUMERATION TYPES
//******************************************************
struct penJoinStyleConversion
{
    Qt::PenJoinStyle e_joinStyle;
    string           s_joinStyle;
};

const int NUM_JOIN_STYLES = 3;
const penJoinStyleConversion penJoinStyleList[NUM_JOIN_STYLES]
{
    {Qt::PenJoinStyle::MiterJoin, "MiterJoin"},
    {Qt::PenJoinStyle::BevelJoin, "BevelJoin"},
    {Qt::PenJoinStyle::RoundJoin, "RoundJoin"}
};



// BRUSH STYLE ENUMERATION TYPES
//******************************************************
struct brushStyleConversion
{
    Qt::BrushStyle  e_brushStyle;
    string          s_brushStyle;
};

const int NUM_BRUSH_STYLES = 4;
const brushStyleConversion brushStyleList[NUM_BRUSH_STYLES]
{
    {Qt::BrushStyle::SolidPattern, "SolidPattern"},
    {Qt::BrushStyle::HorPattern,   "HorPattern"},
    {Qt::BrushStyle::VerPattern,   "VerPattern"},
    {Qt::BrushStyle::NoBrush,      "NoBrush"}
};



// TEXT ALIGNMENT ENUMERATION TYPES
//******************************************************
struct alignmentFlagConversion
{
    Qt::AlignmentFlag e_fontAlignFlag;
    string            s_fontAlignFlag;
};

const int NUM_ALIGN_FLAGS = 5;
const alignmentFlagConversion alignmentFlagList[NUM_ALIGN_FLAGS]
{
    {Qt::AlignmentFlag::AlignLeft,    "AlignLeft"},
    {Qt::AlignmentFlag::AlignRight,   "AlignRight"},
    {Qt::AlignmentFlag::AlignTop,     "AlignTop"},
    {Qt::AlignmentFlag::AlignBottom,  "AlignBottom"},
    {Qt::AlignmentFlag::AlignCenter,  "AlignCenter"}
};



// TEXT FONT STYLE ENUMERATION TYPES
//******************************************************
struct fontStyleConversion
{
    QFont::Style    e_fontStyle;
    string          s_fontStyle;
};

const int NUM_FONT_STYLES = 3;
const fontStyleConversion fontStyleList[NUM_FONT_STYLES]
{
    {QFont::Style::StyleNormal,  "StyleNormal"},
    {QFont::Style::StyleItalic,  "StyleItalic"},
    {QFont::Style::StyleOblique, "StyleOblique"}
};



// TEXT FONT WEIGHT ENUMERATION TYPES
//******************************************************
struct fontWeightConversion
{
    QFont::Weight   e_fontWeight;
    string          s_fontWeight;
};

const int NUM_FONT_WEIGHTS = 4;
const fontWeightConversion fontWeightList[NUM_FONT_WEIGHTS]
{
    {QFont::Weight::Thin,   "Thin"},
    {QFont::Weight::Light,  "Light"},
    {QFont::Weight::Normal, "Normal"},
    {QFont::Weight::Bold,   "Bold"},
};


} // namespace

#endif
