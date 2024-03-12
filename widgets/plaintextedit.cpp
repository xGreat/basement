#include "plaintextedit.h"
#include <QLabel>
#include <QStyle>

const int kMaxLength = 2000;

namespace QRCode {

PlainTextEdit::PlainTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
    , m_indicator(new QLabel(this))
    , m_maxLength(kMaxLength)
{
    setContextMenuPolicy(Qt::NoContextMenu);

    // Set placeholder color
    QPalette pal(palette());
    pal.setColor(QPalette::PlaceholderText, Qt::gray);
    setPalette(pal);
    setAutoFillBackground(true);

    {
        m_indicator->setFixedSize(80, 30);
        m_indicator->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        m_indicator->setAttribute(Qt::WA_TranslucentBackground);
        m_indicator->setAttribute(Qt::WA_TransparentForMouseEvents);
        m_indicator->setText(QString("0/%1").arg(m_maxLength));

        QFont font(m_indicator->font());
        font.setPointSize(10);
        m_indicator->setFont(font);
    }

    connect(this, &QPlainTextEdit::textChanged, [=]() {
        style()->unpolish(this);
        style()->polish(this);

        QString plainText = toPlainText();
        int length = plainText.length();

        if (length > m_maxLength) {
            setPlainText(plainText.left(m_maxLength));
            textCursor().clearSelection();
            moveCursor(QTextCursor::End);
        }

        m_indicator->setStyleSheet(length > m_maxLength ? "QLabel{color: red;}" : "");
        m_indicator->setText(QString("%1/%2").arg(toPlainText().length()).arg(m_maxLength));
    });
}

PlainTextEdit::~PlainTextEdit()
{
}

void PlainTextEdit::setMaxLength(int length)
{
    m_maxLength = length;

    m_indicator->setText(QString("%1/%2").arg(toPlainText().length()).arg(m_maxLength));
}

void PlainTextEdit::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    m_indicator->move(rect().right() - m_indicator->width() - 20,
                      rect().bottom() - m_indicator->height());
}

} // namespace QRCode