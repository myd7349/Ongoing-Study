// 2015-08-28T10:56+08:00
#pragma once

class CODBCFilter {
public:
    struct Operator {
        LPCTSTR lpcsz;
    };
    CODBCFilter(const CODBCFieldInfo &fieldInfo);

private:
    CODBCFilter(const CODBCFilter &);
    CODBCFilter &operator=(const CODBCFilter &);

    CODBCFieldInfo m_FieldInfo;
};
