#ifndef CAS_COMMON_PARSER_HPP_
#define CAS_COMMON_PARSER_HPP_

#include <string>
#include <sstream>

template<class Number>
class CommonParser
{
    //std::unordered_map<std::string, Number> variables;
    //std::unordered_map<std::string, int> functions;
    std::string error;

public:
    const std::string &get_error() { return error; }

    Number evaluate_value(std::stringstream &ss)
    {
        Number res;
        ss >> res;

        if (!ss.fail()) {
            return std::move(res);
        }

        char c;
        ss >> c;

        if (c == '(') {
            res = evaluate_sum(ss);
            ss >> c;

            if (c != ')') {
                error = "Expected ')'";
                return Number();
            }
        }

        // TODO: make functions here??? maybe

        error = "Expected value or '(' or function name";
        return Number();
    }

    Number evaluate_mul(std::stringstream &ss)
    {
        Number res("1");
        Number tmp;
        
        enum {
            OP_MUL,
            OP_DIV,
            OP_MOD
        } operation = OP_MUL;
        
        while (1) {
            Number tmp = evaluate_value(ss);
            
            switch (operation) {
                case OP_MUL: res *= tmp; break;
                case OP_DIV: res = res / tmp; break;
                case OP_MOD: res = res % tmp; break;
            }
            
            char c;
            ss >> c;

            if (c == '*') operation = OP_MUL;
            else if (c == '/') operation = OP_DIV;
            else if (c == '%') operation = OP_MOD;
            else {
                ss.unget();
                return res;
            }
        }
    }

    Number evaluate_sum(std::stringstream &ss)
    {
        Number res;
        Number tmp;
        bool sign = false;

        while (1) {
            Number tmp = evaluate_mul(ss);
            
            if (sign) res -= tmp;
            else      res += tmp;

            char c;
            ss >> c;

            if (c == '+') sign = false;
            else if (c == '-') sign = true;
            else {
                ss.unget();
                return res;
            }
        }
    }

    Number evaluate(const char *str)
    {
        error.clear();
        std::stringstream ss;
        ss << str;
        
        Number res = evaluate_sum(ss);
        
        std::string end = ss.str();
        if (!end.empty()) {
            error = "Unexpected junk: " + end;
        }
        return res;
    }
};

#endif
