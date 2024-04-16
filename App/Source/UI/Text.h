#pragma once

#include <graphics.h>

#include "Utils/Vector2.h"
#include "Utils/StringUtils.h"
#include "UIElement.h"

using namespace Math;

namespace UI
{
    /// <summary>
    /// ������ʽ
    /// </summary>
    enum class FontStyle
    {
        Normal,     // ����
        Bold,       // ����
        Italic,     // б��
        Underline,  // �»���
        StrikeOut   // ɾ����
    };

    /// <summary>
    /// �ı���ʽ
    /// </summary>
    enum class TextFormat : uint32_t
    {
        Left                = DT_LEFT,          // �����
        Top                 = DT_TOP,           // �϶���
        HorizontalCenter    = DT_CENTER,        // ˮƽ����
        Right               = DT_RIGHT,         // �Ҷ���
        VerticalCenter      = DT_VCENTER,       // ��ֱ����
        Bottom              = DT_BOTTOM,        // �¶���
        WordBreak           = DT_WORDBREAK,     // �Զ����У����𿪵��ʣ�
        SingleLine          = DT_SINGLELINE,    // ����
    };

    /// <summary>
    /// ���뷽ʽ
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
        std::string m_Text;     // �ı�����
        std::string m_Font;     // ��������
        FontStyle m_Style;      // ������ʽ�����塢б��ȣ�
        int m_FontSize;         // �����С
        // int m_LineSpacing;
        Alignment m_Alignment;  // ���뷽ʽ
        Color m_Color;          // �ı���ɫ
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
            RECT rect = { m_Position.X, m_Position.Y, m_Position.X + m_Size.X, m_Position.Y + m_Size.Y };   // �ı���������

            settextcolor(m_Color.ToColorref());     // �����ı���ɫ
            
            LOGFONT font;                                                       // ����
            gettextstyle(&font);                                                // ��ȡ��ǰ��������
            font.lfHeight = m_FontSize;                                         // �ֺ�
            font.lfWidth = 0;
            _tcscpy_s(font.lfFaceName, Utils::StringToWChar(m_Font));           // ����
            font.lfWeight = m_Style == FontStyle::Bold ? FW_BOLD : FW_NORMAL;   // �Ƿ�Ϊ����
            font.lfItalic = m_Style == FontStyle::Italic;                       // б��
            font.lfUnderline = m_Style == FontStyle::Underline;                 // �»���
            font.lfStrikeOut = m_Style == FontStyle::StrikeOut;                 // ɾ����
            font.lfQuality = ANTIALIASED_QUALITY;		                        // ���Ч��Ϊ�����  
            settextstyle(&font);						                        // ����������ʽ

            drawtext(Utils::StringToWChar(m_Text), &rect, (uint32_t)TextFormat::SingleLine | m_Alignment);  // �����ı�

            rectangle(m_Position.X, m_Position.Y, m_Position.X + m_Size.X, m_Position.Y + m_Size.Y);    // TODO delete
        }

		virtual void OnEvent() override
		{

		}
	};
}