#include <iostream>
#include <vector>
#include <ctype.h>
#include <string> 


std::vector < std::string > parse(std::string input) {
    std::vector < std::string > parsedInput;
    std::string begin;
    begin.push_back(input[0]);
    parsedInput.push_back(begin);

    

    for (int i = 1; i < input.size(); i++) {
        if (((std::isdigit(input[i])) && (std::isdigit(input[i - 1]))) || ((std::isdigit(input[i])) && (input[i - 1] == '.'))|| ((std::isdigit(input[i-1])) && (input[i] == '.'))) {
            std::string initialDigitsInNumber = parsedInput.back();
            std::string back = (initialDigitsInNumber)+input[i];
            parsedInput.pop_back();
            parsedInput.push_back(back);
        }
        else if ((std::isalpha(input[i])) && (std::isalpha(input[i - 1]))) {
            std::string initialSignInNumber = parsedInput.back();
            std::string back = (initialSignInNumber)+input[i];
            parsedInput.pop_back();
            parsedInput.push_back(back);
        }
        else {
            std::string s;
            s.push_back(input[i]);
            parsedInput.push_back(s);
        }
    }
    return parsedInput;

}

double calculate(double a, std::string math0perator, double b) {

    std::cout << std::endl << a << math0perator << b << std::endl;

    if (math0perator == "+") {
        return a + b;
    }
    else if (math0perator == "-") {
        return a - b;
    }
    else if (math0perator == "*") {
        return a * b;
    }
    else if (math0perator == "/") {
        return a / b;
    }
    else if (math0perator == "sqrt") {
        return pow(b, 1 / double(a)); //TO DO:
    }
    else if (math0perator == "^") {

        return pow(a,b);//TO DO:
    }

    else return 0;

}

int prio(std::string math_operator) {
    if (math_operator == "+") {
        return 1;
    }
    else if (math_operator == "-") {
        return 1;
    }
    else if (math_operator == "*") {
        return 2;
    }
    else if (math_operator == "/") {
        return 2;
    }
    else if (math_operator == "sqrt") {
        return 2;
    }
    else if (math_operator == "^") {
        return 2;
    }
    else return 0;
}

int findOperator(std::vector < std::string > parsedInput) {
    int max = 1;
    int maxP = prio(parsedInput[1]);
    for (int i = 1; i < parsedInput.size(); i = i + 2) {
        if (maxP < prio(parsedInput[i])) {
            max = i;
            maxP = prio(parsedInput[i]);
        }
    }
    return max;
}

bool containBracket(std::vector < std::string > parsedInput) {
    for (int i = 0; i < parsedInput.size(); i++) {
        if (parsedInput[i] == "(") {
            return true;
        }
    }
    return false;
}

double calculate(std::vector < std::string > parsedInput) {

    std::cout << "\n[";
    for (int i = 0; i < parsedInput.size(); i++) {
        std::cout << parsedInput[i] << " ";
    }
    std::cout << "]\n";

    if (parsedInput.size() == 3) {
        return calculate(stod(parsedInput[0]), parsedInput[1], stod(parsedInput[2]));
    } if (containBracket(parsedInput)) {
        std::cout << " () \n";

        int open;
        int close;
        for (int i = 0; i < parsedInput.size(); i++) {
            if (parsedInput[i] == "(") {
                open = i;
            }
            if (parsedInput[i] == ")") {
                close = i;
                break;
            }
        }
        std::vector<std::string> newVec(parsedInput.begin() + open + 1, parsedInput.begin() + close);
        int result = calculate(newVec);

        for (int i = open; i < close; i++) {
            parsedInput.erase(parsedInput.begin() + open);///spr z i
        }
        parsedInput[open] = std::to_string(result);
        return calculate(parsedInput);

    }
    else {
        int i = findOperator(parsedInput);
        // std::cout << i <<" operator\n";
        int result = calculate(stoi(parsedInput[i - 1]), parsedInput[i], stoi(parsedInput[i + 1]));
        parsedInput.erase(parsedInput.begin() + i);
        parsedInput.erase(parsedInput.begin() + i);
        parsedInput[i - 1] = std::to_string(result);
        return calculate(parsedInput);
    }
}

int main(int argc, char* argv[]) {
    std::string a ;
    std::cout << "********** NoSaSiCa **********" << std::endl;
    std::cout << "a+b - dodawanie a + b" << std::endl;
    std::cout << "a-b - odejmowanie a - b" << std::endl;
    std::cout << "a*b - mnozenie a razy b" << std::endl;
    std::cout << "a/b - dzielenie a przez b" << std::endl;
    std::cout << "a^b - a do potegi b " << std::endl;
    std::cout << "asqrtb - pierwiastkowanie a-tego stopnia liczby b" << std::endl << std::endl;
    std::cout << "Podaj swoje dzialanie (kalkulator uwzglednia nawiasy):" <<std::endl;
    std::cin >> a;

    std::vector<std::string> parsedVec = parse(a);
    for (int i = 0; i < parsedVec.size(); i++) {
        std::cout << parsedVec[i] << " ";
    }
    std::cout << " MOJ WYNIK = \n\n" << calculate(parsedVec);


    return 0;
}