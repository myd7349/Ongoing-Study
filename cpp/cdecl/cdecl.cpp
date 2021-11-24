// cdecl using FSM.
#include <cassert>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <unordered_set>


class Cdecl
{
public:
    void Gibber(const std::string &declaration)
    {
        sstream_.clear();
        sstream_.str(declaration);

        std::stack<Token>().swap(tokens_);

        next_ = std::bind(&Cdecl::ReadToFirstIdentifier, this);

        while (next_)
            next_();
    }

private:
    enum TokenType
    {
        None,
        Type,
        Qualifier,
        Identifier,
        Char,
    };

    struct Token
    {
        Token() : type(None) {}

        TokenType type;
        std::string string;
    };

    void ReadToFirstIdentifier()
    {
        Token token;
        while (GetToken(token))
        {
            if (token.type == Identifier)
            {
                std::cout << '\'' << token.string << "\' is ";
                break;
            }
            else
            {
                tokens_.push(token);
            }
        }

        GetToken(currentToken_);

        next_ = std::bind(&Cdecl::DealWithArray, this);
    }

    void DealWithArray()
    {
        next_ = std::bind(&Cdecl::DealWithFunction, this);

        while (currentToken_.type == '[')
        {
            std::cout << "array ";

            if (!GetToken(currentToken_))
            {
                Terminate();
                return;
            }

            if (std::isdigit(currentToken_.string[0]))
            {
                std::cout << currentToken_.string << ' ';

                if (!GetToken(currentToken_))
                {
                    Terminate();
                    return;
                }
            }

            if (currentToken_.type != Char && currentToken_.string[0] != ']')
            {
                std::cerr << "Error: \n']' is expected!\n";
                Terminate();
                return;
            }

            std::cout << "of ";

            if (!GetToken(currentToken_))
            {
                Terminate();
                return;
            }

            next_ = std::bind(&Cdecl::DealWithLParen, this);
        }
    }

    void DealWithFunction()
    {
        next_ = std::bind(&Cdecl::DealWithLParen, this);

        if (currentToken_.type == Char && currentToken_.string[0] == '(')
        {
            int leftBrackets = 0;

            while (GetToken(currentToken_))
            {
                if (currentToken_.type == Char)
                {
                    if (currentToken_.string[0] == '(')
                    {
                        leftBrackets += 1;
                    }
                    else if (currentToken_.string[0] == ')')
                    {
                        if (leftBrackets > 0)
                        {
                            leftBrackets -= 1;
                        }
                        else
                        {
                            if (!GetToken(currentToken_))
                            {
                                Terminate();
                                return;
                            }

                            break;
                        }
                    }
                }
            }

            std::cout << "function returning ";
        }
    }

    void DealWithLParen()
    {
        next_ = std::bind(&Cdecl::DealWithPointer, this);

        if (!tokens_.empty())
        {
            if (tokens_.top().type == Char && tokens_.top().string[0] == '(')
            {
                tokens_.pop();

                if (!GetToken(currentToken_))
                {
                    Terminate();
                    return;
                }

                next_ = std::bind(&Cdecl::DealWithArray, this);
            }
        }
    }

    void DealWithPointer()
    {
        next_ = std::bind(&Cdecl::DealWithType, this);

        if (!tokens_.empty())
        {
            if (tokens_.top().type == Char && tokens_.top().string[0] == '*')
            {
                std::cout << "pointer to ";
                tokens_.pop();

                next_ = std::bind(&Cdecl::DealWithLParen, this);
            }
            else if (tokens_.top().type == Qualifier)
            {
                std::cout << tokens_.top().string << ' ';

                next_ = std::bind(&Cdecl::DealWithLParen, this);
            }
        }
    }

    void DealWithType()
    {
        while (!tokens_.empty())
        {
            std::cout << tokens_.top().string << ' ';
            tokens_.pop();
        }

        std::cout << '\n';

        Terminate();
    }

    void Terminate()
    {
        next_ = std::function<void()>();
    }

    TokenType ClassifyToken(const std::string &token)
    {
        assert(!token.empty());

        if (KnownTypes_.find(token) != KnownTypes_.cend())
            return Type;
        else if (KnownQualifiers_.find(token) != KnownQualifiers_.cend())
            return Qualifier;

        return Identifier;
    }

    bool GetToken(Token &token)
    {
        char ch;

        sstream_ >> ch;
        if (!sstream_)
            return false;

        if (std::isalpha(ch) || ch == '_')
        {
            token.string = ch;

            while (sstream_ >> ch)
            {
                if (std::isalnum(ch) || ch == '_')
                {
                    token.string.push_back(ch);
                }
                else
                {
                    sstream_.unget();
                    break;
                }
            }

            token.type = ClassifyToken(token.string);
        }
        else
        {
            token.type = Char;
            token.string = ch;
        }

        return true;
    }

    std::istringstream sstream_;
    std::stack<Token> tokens_;
    Token currentToken_;
    std::function<void()> next_;

    static std::unordered_set<std::string> KnownTypes_;
    static std::unordered_set<std::string> KnownQualifiers_;
};


std::unordered_set<std::string> Cdecl::KnownTypes_ =
{
    "signed", "unsigned", "void",   "char",   "short", "int",
    "long",   "float",    "double", "struct", "union", "enum",
};


std::unordered_set<std::string> Cdecl::KnownQualifiers_ =
{
    "const", "volatile", "restrict",
};


void ProcessDeclarationsInStream(std::istream &istream)
{
    Cdecl drunkard;

    std::string declaration;
    while (std::getline(istream, declaration))
        drunkard.Gibber(declaration);
}


int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        for (int i = 1; i < argc; ++i)
        {
            std::ifstream istream(argv[i]);
            if (!istream)
            {
                std::cerr << "Failed to open '" << argv[i] << "'!\n";
                continue;
            }

            ProcessDeclarationsInStream(istream);

            istream.close();
        }
    }
    else
    {
        ProcessDeclarationsInStream(std::cin);
    }

    return 0;
}

// TODO:
// int x;

// References:
// Expert C Programming: Deep C Secrets, Ch3.8, Ch8
// ../../c/cdecl
// https://stackoverflow.com/questions/40201711/how-can-i-clear-a-stack-in-c-efficiently
// https://stackoverflow.com/questions/6774825/reading-from-ifstream-wont-read-whitespace
// https://stackoverflow.com/questions/7582546/using-generic-stdfunction-objects-with-member-functions-in-one-class
