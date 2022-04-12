#include "CMyString.h"

class CInternetURL
{
private:
    CMyString url;
    CMyString Domain;

public:
    CInternetURL(const char s[]);
    CMyString GetDomain();        /* 获取域名 */
    CMyString GetDomainCountry(); /* 获取国家级域名 */
    CMyString GetDomainType();    /* 获取域名类别 */
};

CInternetURL::CInternetURL(const char s[])
{
    url = s;
}

CMyString CInternetURL::GetDomain()
{
    Domain = url.Mid(8, url.Find(8, '/') - 8);
    return Domain;
}

CMyString CInternetURL::GetDomainCountry()
{
    GetDomain();

    int temp = 0, index = 0;

    while (temp != -1)
    {
        temp = Domain.Find(index + 1, '.');
        if (temp != -1)
            index = temp;
    }

    return Domain.Mid(index + 1, 2);
}

CMyString CInternetURL::GetDomainType()
{
    GetDomain();
    if (Domain.Find("org") != -1)
        return "org";
    if (Domain.Find("com") != -1)
        return "com";
    if (Domain.Find("gov") != -1)
        return "gov";
    if (Domain.Find("edu") != -1)
        return "edu";
    if (Domain.Find("net") != -1)
        return "net";
    if (Domain.Find("top") != -1)
        return "top";
    if (Domain.Find("tv") != -1)
        return "tv";

    return "Unknown";
}