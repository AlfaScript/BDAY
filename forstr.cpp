#include "forstr.h"

bool forStr::reviewStr(QString & str) noexcept
{
    auto itEnd = str.end();
    for (auto it = str.begin(); it != itEnd; ++it)
    {
        QChar ch = *it;
        if(!ch.isLetter() || ch.isNonCharacter() || ch.isDigit() || ch.isSpace())
        {
            if(!ch.isSymbol('-'))
            {
                str.replace(ch, "");
                --it;
            }
        }
    }
    return !str.isEmpty();
}
