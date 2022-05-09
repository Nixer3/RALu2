/*
Zadanie RAL 2022
Stanislava Peckova a Matej Skulsky

text zadania:
2. Aritmetika  modulo 2^n, t.j. určenie polynómu rozšírenia poľa, potom súčet, súčin, inverzia - 2 ľudia
*/


#include <iostream>
#include <sstream>
#include <stack>
#include <utility>      // std::pair
#include "main.h" 

#include <NTL/GF2.h>
#include <NTL/GF2X.h>
#include <NTL/GF2E.h>
#include <NTL/GF2XFactoring.h>

using namespace std;
NTL_CLIENT


string operiations = "+-*/^()e^";
string singleOp = "i'ts"; // i or ' inverse; t trace; s square

//PROTOTYPES (infile functions)
GF2E calculate(const GF2E& g1, const GF2E& g2, char op);
GF2E calculate(GF2E& g1, char op);
GF2E fpow(GF2E g1, int left);
GF2E evaluate(string& s);

int8_t prio(char c) {
    switch (c) {
    case '+':
    case '-':   return 1;
    case '*':
    case '/':   return 2;
    case '^':   
    case 'e':   return 4;
    case '(':
    case ')':   return 8;

    default:    return -1;
    }
}

int main() {

    long n;
    cout << "Vitajte v interaktivnej kalkulacke v poliach F2^n." << endl;
    cout << "Zadajte n." << endl; //stupen polynomu
    cin >> n; 
    
    GF2X modul;
    BuildIrred(modul, n);
    cout << "Polynom na faktorizaciu F2^" << n << " je: " << modul << endl;
    GF2E::init(modul);


    //   A,B,C... = [0 1 2 3]  
    //   a,b,c... = 5
    // two operands OPS: +-*/ ^e    
    // one operand  OPS: {i inverse, s square, t trace}
    //   A+B+C
    //   A-B*C  
    //   A-(B+C)*E
    //   A^a       ==  Aea 
    // all I want to say is:
    // [0 0 1]e2+[1 1 1]*[3]s*([1 0]+[2])i


    //NOT TESTED ALL EDGE CASES  or (supposed) crashed when line doesn't make sense

   

    
    while (1) {
        string l;
        getline(cin, l); // read whole line
        if (!l.empty()) {
            cout << l << endl;
            trim(l);  // cut white spaces from ends
            cout << evaluate(l) <<endl;
            char control;
            cout << "Pre ukoncenie stlacte Q. Ak chcete pokracovat stlacte lubovolnu klavesu" << endl;
            control = getchar();
            if (control == 'q' || control == 'Q') {
                exit(0);
            }
        }
        else {
            cout << "Zadajte rovnicu na pocitanie" << endl;
        }
       
    }
    return 0;
}

//well.. 
GF2E evaluate(string& s) {
    stack<GF2E> vals;
    stack<char> ops;
    GF2E val;
    long vali = 0;
    int pos = 0;
    while (pos < s.length()) {
        char spot = s[pos];
        if (spot == '[') { // if ( isdigit() )
            istringstream ss(s.substr(pos)); //if only there would be better way //conv<GF2E>(s); doesnt provide lenth
            ss >> val;
            if (ss.tellg() == -1)
                throw string("Error while parsing polynomial "+ ss.str());
            pos += (int)ss.tellg(); // used chars from string
            pos--;
        }
        else if (isdigit(spot)) {
            istringstream ss(s.substr(pos)); //gets a number
            ss >> vali;
            int left = ss.tellg();
            pos += (ss.tellg() == -1 ? 0 :left); // used chars from string
            pos--;
        }
        else if (singleOp.find(spot) != string::npos) {
            val = calculate(val, spot);
        }
        else if (operiations.find(spot) != string::npos) {
            if (spot == '(') {
                int end = subParanth(s,pos);
                string sub = s.substr(pos+1, end-pos-1 );
                val = evaluate(sub); 
                pos = end+1;
                continue;
            }
            else if (vals.empty()) {
                vals.push(val);
                ops.push(spot);
                val = 0;
            }
            else {
                char prev = ops.top();
                if (prio(spot) > prio(prev)) {
                    vals.push(val);
                    ops.push(spot);
                    val = 0;
                }
                else {
                    //collapse 
                    while (!ops.empty()) {
                        GF2E prev = vals.top(); 
                        char op = ops.top();
                        if (prio(spot) > prio(op))
                            break;
                        vals.pop(); ops.pop();
                        if (op == '^' || op == 'e') {
                            cout << "calc: " << prev << '^' << vali<<" = ";
                            val = power(prev, vali);
                            cout << val << endl;
                            vali = 0;
                        }
                        else 
                            val = calculate(prev, val, op);
                    }
                    vals.push(val);
                    ops.push(spot);
                    val = 0;
                }
            }
        }
        pos++;
    }
    
    while (!ops.empty()) {
        GF2E prev = vals.top(); vals.pop();
        char spot = ops.top(); ops.pop();
        if (spot == '^' || spot == 'e') {
            cout << "calc: " << prev << '^' << vali << " = ";
            val = power(prev, vali);
            cout << val<<endl;
            vali = 0;
        }
        else
            val = calculate(prev, val, spot);
    }
    return val;

}




GF2E calculate(const GF2E& g1, const GF2E &g2, char op) {
    cout << "calc: " << g1 << op << g2 << " = ";
    GF2E out;
    switch (op) {
        case '+': out = g1 + g2; break;
        case '*': out = g1 * g2; break;
        case '-': out = g1 - g2; break;
        case '/': out = g1 / g2; break;
        case 'e':  // calculates in evaluate()
        case '^': break; // calculates in evaluate()
        default: throw new invalid_argument(string("no supported double operand operation '" + op) + "'");
    }
    cout << out << endl;
    return out;
}

GF2E calculate(GF2E& g1, char op) {
    cout << "calc: " << g1 << op << endl;
    switch (op) {
        case 'i': 
        case '\'': return inv(g1);
        case 's': return sqr(g1);
        case 't': return GF2E(trace(g1));
    }
    throw new invalid_argument(string("no supported single operand operation '" + op) + "'");
}

GF2E fpow(GF2E g1, int left) {
    if (left == 1) return g1;
    return fpow(g1, left - 1) * g1;
}
