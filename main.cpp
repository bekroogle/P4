/*
 * Changelog:
 *
 * April 08, 2013 - Corrected missing code in the switch
 *		statement, under the case for ERF. It previously
 *		did not do anything, except break after an error
 *		state.
 *
 * This update needs to be merged with the new work I've
 *		done on program 4 already.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "typedefs.h"

using namespace std;

void getToken(Token& tok, ifstream& ifp);
void sendResults(ostream& dest, Token& tok);

int main()
{
    ifstream ifp;					// Input file
    ofstream ofp;					// Output/log file
    string if_name;					// Input file name
    Token currentToken;
    State_Name state = START;

    cout << "Please enter the name of the input file: ";
    cin >> if_name;

    ifp.open(if_name.c_str());

    if (ifp.fail()) {
        cerr << "Unable to open file :" << if_name;
        exit(EXIT_FAILURE);
    }

    ofp.open("log.txt");

    if (ofp.fail()) {
        cerr << "Unable to open log file. Results echoed to standard output only.";
        exit(EXIT_FAILURE);
    }
    while (!ifp.eof()) {
        getToken(currentToken, ifp);

        if (ifp.fail()) {
			break;

		}
		sendResults(cout, currentToken);
		sendResults(ofp, currentToken);
 if (currentToken.type == OPEN_TAG) {
              tokenStack.push(currentToken);
        }
        if (currentToken.type == CLOSE_TAG) {
            if (tokenStack.top().lexeme == currentToken.lexeme) {
                tokenStack.pop();
            } else {
                cout << endl << "Error: Improperly nested tag at line " <<
                        currentToken.line_number << ", position " <<
                        currentToken.char_pos << "." << endl << endl <<
                        "(Begin tag is of type " <<
                        tokenStack.top().lexeme <<
                        ", but end tag is of type " <<
                        currentToken.lexeme << ".)";
                break;
            }
        }

    }



    return EXIT_SUCCESS;
}

using namespace std;

void getToken(Token& tok, ifstream& ifp)
{
    tok.lexeme = "";
    tok.char_pos = 0;
    tok.type = ERR_TOKEN;
    tok.line_number = 0;
    char c;
    State_Name state = START;
    State_Name prevState = START;
    Char_Type charType;
    static long lineNumber = 1;
    static int charPos = 0;

    while(!ifp.eof()) {
        c = ifp.get();
        if (ifp.fail()) {
            break;
        }

        charPos++;

        if (state == START) {
            tok.char_pos = charPos;
            tok.line_number = lineNumber;
        }
        charType = char_classes[c];
        state = state_trans[state][charType];

        switch (state) {
            case OT1:
                break;
            case OT2:
                tok.lexeme += c;
                tok.type = OPEN_TAG;
                break;
            case OT3:
                tok.lexeme += c;
                break;
            case CT1:
                tok.type = CLOSE_TAG;
                break;
            case CT2:
                tok.lexeme += c;
                break;
            case CT3:
                tok.lexeme += c;
                return;
            case ET1:
            	break;
            case SP1:
                tok.lexeme += c;
                tok.type = SPACE_STR;
                break;
            case ETF:
                tok.type = EMPTY_TAG;
                return;
            case ERF:
            	tok.type = ERR_TOKEN;
            	ifp.unget();
            	return;
            case NLF:
                tok.lexeme = "\\n";
                tok.type = NL_TOKEN;
                lineNumber++;
                charPos = 0;
                return;
            case SPF:
                ifp.unget();
                return;
            case OTF:
                return;
            case CTF:
                return;
            case W1:
                tok.lexeme += c;
                break;
            case WF:
                tok.type = WORD_TOKEN;
                ifp.unget();
                return;

        }
    }
}

void sendResults(ostream& dest, Token& currentToken)
{
	dest << left;
	dest << "token=" << setw(14) << human_readable[currentToken.type] <<
			" type=" << currentToken.type <<
			" lexeme=" << setw(6) << currentToken.lexeme <<
			" on line #" << currentToken.line_number <<
			" at charpos=" << currentToken.char_pos << endl;
}
