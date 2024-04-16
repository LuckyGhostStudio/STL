#pragma once

#include <graphics.h>

#include "Utils/Vector2.h"
#include "Utils/StringUtils.h"
#include "UIElement.h"

using namespace Math;

namespace UI
{
    /// <summary>
    /// 字体样式
    /// </summary>
    enum class FontStyle
    {
        Normal,     // 正常
        Bold,       // 粗体
        Italic,     // 斜体
        Underline,  // 下划线
        StrikeOut   // 删除线
    };

    /// <summary>
    /// 文本格式
    /// </summary>
    enum class TextFormat : uint32_t
    {
        Left                = DT_LEFT,          // 左对齐
        Top                 = DT_TOP,           // 上对齐
        HorizontalCenter    = DT_CENTER,        // 水平居中
        Right               = DT_RIGHT,         // 右对齐
        VerticalCenter      = DT_VCENTER,       // 垂直居中
        Bottom              = DT_BOTTOM,        // 下对齐
        WordBreak           = DT_WORDBREAK,     // 自动换行（不拆开单词）
        SingleLine          = DT_SINGLELINE,    // 单行
    };

    /// <summary>
    /// 对齐方式
    /// </summary>
    struct Alignment
    {
        TextFormat Horizontal = TextFormat::HorizontalCenter;
        TextFormat Vertical = TextFormat::VerticalCenter;

        operator uint32_t() const
        {
            return (uint32_t)Horizontal | (uint32_t)Vertical;
        }
    };

    struct Color
    {
        float Red;
        float Green;
        float Blue;

        Color() : Red(1.0f), Green(1.0f), Blue(1.0f) {}

        Color(float r = 1.0f, float g = 1.0f, float b = 1.0f) : Red(r), Green(g), Blue(b) {}

        COLORREF ToColorref()
        {
            return RGB(Red * 255, Green * 255, Blue * 255);
        }
    };

	class Text : public UIElement
	{
    private:
        std::string m_Text;     // 文本内容
        std::string m_Font;     // 字体名称
        FontStyle m_Style;      // 字体样式（粗体、斜体等）
        int m_FontSize;         // 字体大小
        // int m_LineSpacing;
        Alignment m_Alignment;  // 对齐方式
        Color m_Color;          // 文本颜色
    public:
        Text(
            const Vector2& position = 0.0f,
            const Vector2& size = Vector2(100.0f, 40.0f),
            const std::string& text = "Text",
            const std::string& font = "Consolas",
            FontStyle style = FontStyle::Normal,
            int fontSize = 20,
            Alignment alignment = Alignment(TextFormat::HorizontalCenter, TextFormat::VerticalCenter),
            Color color = Color(1.0f, 1.0f, 1.0f)
        )
            : UIElement(position, size), m_Text(text), m_Font(font), m_Style(style), m_FontSize(fontSize), m_Alignment(alignment), m_Color(color)
        {}

        virtual void Render() override
        {
            RECT rect = { m_Position.X, m_Position.Y, m_Position.X + m_Size.X, m_Position.Y + m_Size.Y };   // 文本矩形区域

            settextcolor(m_Color.ToColorref());     // 设置文本颜色
            
            LOGFONT font;                                                       // 字体
            gettextstyle(&font);                                                // 获取当前字体设置
            font.lfHeight = m_FontSize;                                         // 字号
            font.lfWidth = 0;
            _tcscpy_s(font.lfFaceName, Utils::StringToWChar(m_Font));           // 字体
            font.lfWeight = m_Style == FontStyle::Bold ? FW_BOLD : FW_NORMAL;   // 是否为粗体
            font.lfItalic = m_Style == FontStyle::Italic;                       // 斜体
            font.lfUnderline = m_Style == FontStyle::Underline;                 // 下划线
            font.lfStrikeOut = m_Style == FontStyle::StrikeOut;                 // 删除线
            font.lfQuality = ANTIALIASED_QUALITY;		                        // 输出效果为抗锯齿  
            settextstyle(&font);						                        // 设置字体样式

            drawtext(Utils::StringToWChar(m_Text), &rect, (uint32_t)TextFormat::SingleLine | m_Alignment);  // 绘制文本

            rectangle(m_Position.X, m_Position.Y, m_Position.X + m_Size.X, m_Position.Y + m_Size.Y);    // TODO delete
        }

		virtual void OnEvent() override
		{

		}
	};
}