#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 16
//=====================================================

// --------- Two DFAs ---------------------------------

/*
Q0 => 0 (final state)
qy -> 1
qsa = 2
q0q1 = 3 (final state)
q1 = 4
qt = 5
qs = 6
qc = 7
q0qy = 9 (final state)
*/

// WORD DFA
// Done by: ** Gerald, Chris, Brian
// RE:   ** (vowel | vowel n | consonant vowel | consonant vowel n |
// consonant-pair vowel | consonant-pair vowel n)^+

bool word(string s) {

  int state = 0;
  int charpos = 0;
  // replace the following todo the word dfa  **
  while (s[charpos] != '\0') {
    if (state == 0) { // if state 0  (start of state 1)
      if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' ||
          s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' ||
          s[charpos] == 'E') { // q0 --> q0q1 //mised out on
        state = 3;             // goes to state 3
      } else if (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' ||
                 s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' ||
                 s[charpos] == 'p' || s[charpos] == 'r') { // Q0 -> qy
        state = 1;                                         // goes to state 1
      } else if (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' ||
                 s[charpos] == 'y' || s[charpos] == 'j') { // Q0 -> qsa
        state = 2;                                         // goes to state 2
      } else if (s[charpos] == 't') {                      // q0 -> qt
        state = 5;                                         // goes to state 5
      } else if (s[charpos] == 's') {                      // q0 -> qs
        state = 6;                                         // goes to state 6
      } else if (s[charpos] == 'c') {                      // q0 -> qc
        state = 7;                                         // goes to state 7
      } else {
        return false; // return false (nothing found)
      }
      // end of state 1
    } else if (state == 1) { // Starting state 1: qy -> qsa
      if (s[charpos] == 'y') {
        state = 2;
      } else if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' ||
                 s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' ||
                 s[charpos] == 'E') {
        state = 3;
      } else {
        return false; // return false (nothing found)
      }
    } else if (state == 2) { // Starting State 2: qsa -> q0q1
      if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' ||
          s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' ||
          s[charpos] == 'E') {
        state = 3;
      } else {
        return false; // return false (nothing found)
      }
    } else if (state == 3) { // q0q1 = state 3
      if (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' ||
          s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'p' ||
          s[charpos] == 'r') { // bghkmpr to qy {
        state = 1;             // go to qy
      } else if (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' ||
                 s[charpos] == 'y' || s[charpos] == 'j') {
        state = 2;                    // go to state qsa
      } else if (s[charpos] == 't') { // if t
        state = 5;                    // go to state qt
      } else if (s[charpos] == 's') { // if s
        state = 6;                    // state qs
      } else if (s[charpos] == 'c') { // if c
        state = 7;                    // state qc
      } else if (s[charpos] == 'n') { // if n
        state = 9;                    // state q0qy
      } else if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' ||
                 s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' ||
                 s[charpos] == 'E') { // if V
        state = 3;                    // go to state q0q1
      } else {
        return false; // return false (nothing found)
      }
    } else if (state == 4) { // q1 empty
      if (s[charpos] == 'n') {
        state = 0; // go to q0
      } else {
        return false; // return false (nothing found)
      }
    } else if (state == 5) {   // State 5: qt
      if (s[charpos] == 's') { // qt -> qsa
        state = 2;             // state 2
      } else if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' ||
                 s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' ||
                 s[charpos] == 'E') { // if V
        state = 3;
      } else {
        return false;        // return false (nothing found)
      }                      // end of qt
    } else if (state == 6) { // qs
      if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' ||
          s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' ||
          s[charpos] == 'E') { // V to q0q1
        state = 3;
      } else if (s[charpos] == 'h') { // h to qsa
        state = 2;
        // end qs
      } else {
        return false; // return false (nothing found)
      }
    } else if (state == 7) {   // qc
      if (s[charpos] == 'h') { // h to q0q1
        state = 2;
      } else {
        return false; // return false (nothing found)
      }
    } else if (state == 9) { // q0qy
      if (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' ||
          s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' ||
          s[charpos] == 'p' || s[charpos] == 'r') { // bghkmpr to qy {
        state = 1;                                  // go to qy
      } else if (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' ||
                 s[charpos] == 'y' || s[charpos] == 'j') { // dwzyj to qsa
        state = 2;                                         // go to qsa
      } else if (s[charpos] == 'n') {                      // if n
        state = 1;                                         // go to qy
      } else if (s[charpos] == 'c') {                      // if c
        state = 7;                                         // go to qc
      } else if (s[charpos] == 's') {                      // if s
        state = 6;                                         // go to qs
      } else if (s[charpos] == 't') {                      // if t
        state = 5;                                         // go to qt
      } else if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' ||
                 s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' ||
                 s[charpos] == 'E') { // if V
        state = 3;                    // go to q0q1
      } else {
        return false; // return false (nothing found)
      }
      // end of state 9
    } else {
      cout << "I am stuck in state: " << state << endl;
      cout << "I am stuck in char: " << s[charpos] << endl;
      return false; //  return false
    }

    charpos++; // update char pos
  }            // end of while

  // where did I end up????
  if (state == 0 || state == 3 || state == 9)
    return (true); // end in a final state
  else
    return (false);
}

// PERIOD DFA
// Done by: ** Gerald Cordero
bool period(string s) {        // complete this **
  int state = 0;               // inital current state set to 0
  int charpos = 0;             // current character position set to 0
  while (s[charpos] != '\0') { // start of while

    if (state == 0 && s[charpos] == '.') { // if state 0 and character is '.'
      state = 1;                           // go to state 1
    } else {
      return false; // return false
    }

    charpos++; // incriment charpos to get to next character
  }            // end of while

  if (state == 1) { // if state is at 1 after while loop
    return true;    // return true
  } else {
    return false; // else false
  }
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: ** Gerald, Chris, Brian

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {
  ERROR,
  WORD1,
  WORD2,
  PERIOD,
  VERB,
  VERBNEG,
  VERBPAST,
  VERBPASTNEG,
  IS,
  WAS,
  OBJECT,
  SUBJECT,
  DESTINATION,
  PRONOUN,
  CONNECTOR,
  EOFM
}; // update tt

// ** For the display names of tokens - must be in the same order as the
// tokentype.
string tokenName[30] = {"ERROR",       "WORD1",   "WORD2",     "PERIOD",
                        "VERB",        "VERBNEG", "VERBPAST",  "VERBPASTNEG",
                        "IS",          "WAS",     "OBJECT",    "SUBJECT",
                        "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
struct R {
  string word;          // for word
  tokentype token_type; // for tt
};

// array for all rules
R arr[] = {{"masu", VERB}, {"masen", VERBNEG},
          {"mashita", VERBPAST},
          {"masendeshita", VERBPASTNEG},
          {"desu", IS},
          {"deshita", WAS},
          {"o", OBJECT},
          {"wa", SUBJECT},
          {"ni", DESTINATION},
          {"watashi", PRONOUN},
          {"anata", PRONOUN},
          {"kare", PRONOUN},
          {"kanojo", PRONOUN},
          {"sore", PRONOUN},
          {"mata", CONNECTOR},
          {"soshite", CONNECTOR},
          {"shikashi", CONNECTOR},
          {"dakara", CONNECTOR},
          {"eofm", EOFM}};

int n = 19; // gloabl index of array of reserved words/token_type

// ------------ Scanner and Driver -----------------------

ifstream fin; // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Gerald Chris, Brian
int scanner(tokentype &tt, string &w) {

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.
  fin >> w;
  // cout << "input is " << w << endl;
  if (w == "eofm" || w == "EOFM") { // if eofm return
    return 0;                       // return 0
  }

  /*  **
  2. Call the token functions (word and period)
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
  */
  bool period_found = false; // variable for period
  bool error_found = false;  // variable for error
  if (word(w) == false &&
      period(w) == false) { // if not a word or a period then error
    cout << "Lexical error: string is not a valid token" << endl;
    tt = ERROR;                   // else error
    error_found = true;           // error found make variable true
  } else if (period(w) == true) { // if period true
    tt = PERIOD;                  // token type '.'
    period_found = true;          // period found make variable true
  }

  /*
  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.
  */
  bool reserved_word = false;
  if (word(w) == true) { // if word then find token type
    // cout << w << " IS WORD" << endl;
    for (int i = 0; i < n; i++) { // iterate through array size
      if (w == arr[i].word) {     // if word is a word in array
        tt = arr[i].token_type;   // assign tt to the token type
        reserved_word = true;     // set to true
      }
    }
  }
  if (reserved_word == false && period_found == false &&
      error_found ==
          false) { // if not a word find last letter and set to WORD1 or WORD2
    if (w[w.length() - 1] == 'a' || w[w.length() - 1] == 'e' ||
        w[w.length() - 1] == 'i' || w[w.length() - 1] == 'o' ||
        w[w.length() - 1] == 'u' || w[w.length() - 1] == 'n') {
      tt = WORD1; // set to WRD1
    } else if (w[w.length() - 1] == 'I' || w[w.length() - 1] == 'E') {
      tt = WORD2; // set to WRD2
    }
  }
  /*
  4. Return the token type & string  (pass by reference)
  */
  return 0;
} // the end of scanner

// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Gerald, Brian, Chris

//----------------------------------------------------------------------------------------------------------------
/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .
       and then append the two files into one:
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: ** 16
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

bool token_available = false; // global flag indicating whether we have saved a token to eat up or not

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

// Type of error: ** match fails => call syntax_error1
// Done by: ** Gerald, Chris, Brian
void syntaxerror1(tokentype token, string lexeme) {
  cout << "SYNTAX ERROR: expected: " << tokenName[token] << " but found "
       << lexeme << endl;
  exit(1);
}
// Type of error: ** switch default in a parser function => call syntax_error2
// Done by: ** Gerald, Chris, Brian
void syntaxerror2(string lexeme, tokentype token) { // come back later try string if wrong
  cout << "SYNTAX ERROR: unexpected " << lexeme << " found in "
       << tokenName[token] << endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

void getEword();
//void gen();
void gen(string line_type);
tokentype saved_token; // global buffer for the token the scanner returned
string saved_lexeme;   // gloabally accessible

// to implement the look ahead of the nect token global variables

// Purpose: ** Checks next token with scanner
// Done by: ** Gerald, Chris, Brian
tokentype next_token(void) {
  // string saved_lexeme;
  if (!token_available) { // if token_avalianle is not
    // call scanner to grab a new token
    // saved_token is the token type and
    // saved_lexeme is the word that is read in

    scanner(saved_token, saved_lexeme); // this is pass by reference
    cout << "Scanner called using word: " << saved_lexeme << endl;

    token_available = true; // mark that fact that you have saved it

    if (saved_token == ERROR) { // if saved_token is error call syntax error2
      // syntaxerror1(saved_token, saved_lexeme);
      syntaxerror2(saved_lexeme, saved_token);
    }
  }
  // cout << tokenName[saved_token] << endl;
  return saved_token; // return the saved token
}

// Purpose: ** Check for match of token in list
// Done by: ** Gerald, Chris, Brian
bool match(tokentype expected) {
  // cout << "Starting Match Function..." << endl;
  if (next_token() != expected) { // mismatch has occurred with the next token
    // calls a syntax error function here to generate a syntax error message
    // here and do recovery syntaxerror2(saved_lexeme, saved_token);
    syntaxerror1(expected, saved_lexeme);

    return false; // no match error

  } else { // match has occured
    cout << "Match " << tokenName[expected] << endl;
    token_available = false; // eat up the token
    return true;             // say there was a match
  }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **  WORD1 | PRONOUN
// Done by: ** Gerald, Chris, Brian
void noun() {
  cout << "Processing <noun>" << endl;
  switch (next_token()) { // next_token is look ahead  if word 1, pronoun
  case WORD1:
    match(WORD1);
    break;
  case PRONOUN:
    match(PRONOUN);
    break;
  default: // else call syntax error2
    // cout << "made 1" << endl;
    syntaxerror2(saved_lexeme, saved_token);
  }
}

// Grammar: ** WORD2
// Done by: ** Gerald, Chris, Brian
void verb() {
  cout << "Processing <verb>" << endl;
  match(WORD2); // just match
}

// Grammar: ** IS | WAS
// Done by: ** Gerald, Chris, Brian
void be() {
  cout << "Processing <be>" << endl;
  switch (next_token()) { // if is, was, else call ysntaxerror2
  case IS:
    match(IS);
    break;
  case WAS:
    match(WAS);
    break;
  default:
    syntaxerror2(saved_lexeme, saved_token); // error handling on defualt
  }
}

// Grammar: ** VERBPAST  | VERBPASTNEG | VERB | VERBNEG
// Done by: ** Gerald, Chris, Brian
void tense() {
  cout << "Processing <tense>" << endl;
  switch (next_token()) { // verbpast, verbpasteng, verb, verbneg, else call syntax error 2
  case VERBPAST:
    match(VERBPAST);
    break;
  case VERBPASTNEG:
    match(VERBPASTNEG);
    break;
  case VERB:
    match(VERB);
    break;

  case VERBNEG:
    match(VERB);
    break;

  default:
    syntaxerror2(saved_lexeme, saved_token); // error handling on defualt
  }
}

// Grammar: ** <verb> <getEword> <gen> <tense> <gen> PERIOD|<noun> <getEword>
// DESTINIATION <gen> <verb> <getEword> <gen> <tense> <gen> PERIOD Done by: **
// Gerald, Chris, Brian
void afterObject() {
  cout << "Processing <afterObject>" << endl;
  switch (next_token()) { // if verb, word1, word2, pronoun, else call syntax error 2
  case VERB:
    verb();
    getEword();
    gen("ACTION"); 
    tense();
    gen("TENSE"); 
    match(PERIOD);
    break;
  // noun
  case WORD1:
    noun();
    getEword();
    match(DESTINATION);
    gen("TO"); 
    verb();
    getEword();
    gen("ACTION"); 
    tense();
    gen("TENSE"); 
    match(PERIOD);
    break;
  case WORD2:
    verb();
    getEword();
    gen("ACTION"); 
    tense();
    gen("TENSE"); 
    match(PERIOD);
    break;
  case PRONOUN:
    noun();
    getEword();
    match(DESTINATION);
    gen("TO"); 
    verb();
    getEword();
    gen("ACTION"); 
    tense();
    gen("TENSE"); 
    match(PERIOD);
    break;
  default:
    syntaxerror2(saved_lexeme, saved_token);
  }
}

// Grammar: ** <be> <gen> PERIOD| DESTINATION <gen> <verb> <getEword> <gen>
// <tense> <gen> PERIOD| OBJECT <afterobject> Done by: ** Gerald, Chris, Brian
void afterNoun() {
  cout << "Processing <afterNoun>" << endl;
  switch (next_token()) { // switch call next_token
  case IS:                // if csase is
    be();                 // call be function
    gen("DESCRIPTION");
    gen("TENSE");       
    match(PERIOD); // match period
    break;         // break
  case WAS:        // if case was
    be();          // call be function
    gen("DESCRIPTION"); 
    gen("TENSE");     
    match(PERIOD);      // match period
    break;              // break
  case DESTINATION:     // if case destination
    match(DESTINATION); // match destination
    gen("TO"); 
    verb(); // call verb function
    getEword();
    gen("ACTION"); 
    tense(); // call tense function
    gen("TENSE"); 
    match(PERIOD); // match period
    break;
  case OBJECT: // if  object ,  mathc object, call after object
    match(OBJECT);
    gen("OBJECT"); 
    afterObject();
    break;
  default: // else syntax error
    syntaxerror2(saved_lexeme, saved_token);
  }
}

// Grammar: ** <verb> <getEword> <gen> <tense> PERIOD | <noun> <getEword> <after
// noun> Done by: ** Gerald, Chris, Brian
void afterSubject() {
  cout << "Processing <afterSubject>" << endl;
  switch (next_token()) { // switch calling next token
  case VERB:              // if case verb
    verb();               // call verb
    getEword();
    gen("ACTION"); 
    tense();       // call tense
    gen("TENSE");     
    match(PERIOD); // match period
    break;         // break
  case WORD2:      // if case word2
    verb();        // call verb
    getEword();
    gen("ACTION");  
    tense(); // call  tense
    gen("TENSE"); 
    match(PERIOD); // match peroid
    break;         // break
  // noun
  case WORD1:    // if case word1
    noun();      // call noun
    getEword();  
    afterNoun(); // call after noun
    break;       // break
  case PRONOUN:  // if case pronoun
    noun();      // call noun
    getEword();
    afterNoun(); // call afterNoun
    break;       // break
  default:       // else call syntax error2
    syntaxerror2(saved_lexeme, saved_token);
  }
}

void s() {
  cout << "Processing <s>" << endl;
  if (next_token() == CONNECTOR) { // if next_token equals CONNECTOR
    match(CONNECTOR);              // match connector
    getEword();
    gen("CONNECTOR"); 
  }

  noun(); // call noun
  getEword();
  match(SUBJECT); //  match subject
  gen("ACTOR"); 
  afterSubject(); // call after subject
}

// Grammar: ** <s> {<s>}
// Done by: ** Gerald, Chris, Brian
void story() {
  cout << "Processing <story>\n" << endl;
  // cout << "Processing <s>" << endl;
  s();
  while (true) {            //&& saved_lexeme != "eofm" // whike true
    switch (next_token()) { // switch , calling next_token
    case CONNECTOR:         // check case for connector
    case WORD1:             // check case for WORD1
    case PRONOUN:           // check case for PRONOUN
      s();                  // call s()
      break;
    default:
      return;
    }
  }
}

string filename;

//---------------------------translator.cpp section--------------

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: ** 16
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of
// lexicon.txt Make sure it is easy and fast to look up the translation. Do not
// change the format or content of lexicon.txt
//  Done by: **Chris, Brian, Gerald

string saved_E_word;

struct words {
  string japanese;
  string english;
};

vector<words> dictionary;

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result
//                 in saved_E_word
void getEword() {
  // cout << "Starting getEword..." << endl;
  bool found_japanese =
      false; // bool variable used if japanese word not found in dictionary
  // iterating through dictionary to find saved_lexeme else save_E_word =
  // saved_lexeme
  for (vector<words>::iterator i = dictionary.begin(); i != dictionary.end();
       i++) {
    if (saved_lexeme == i->japanese) { // found japanese match
      saved_E_word = i->english;       // saved the english word
      found_japanese = true;           // update bool
      break;                           // break out of for loop
    }
  }

  if (found_japanese ==
      false) { // saved_lexeme not found make saved_E_word = saved_lexeme
    saved_E_word = saved_lexeme;
  }

  return;
}
//  Done by: ** Chris, Brian, Gerald
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** Chris, Brian, Gerald

ofstream outputfile("translated.txt"); // opening translated.txt file to write on

void gen(string line_type) {
  // cout << "Starting gen" << endl;
  // Find token and output correct output to file
  if(line_type == "CONNECTOR") {
    outputfile << line_type << ": " << saved_E_word << endl;
  } else if(line_type == "ACTOR") {
    outputfile << line_type << ": " << saved_E_word << endl;
  } else if(line_type == "OBJECT") {
    outputfile << line_type << ": " << saved_E_word << endl;
  } else if(line_type == "DESCRIPTION") { //"IS"
    outputfile << line_type << ": " << saved_E_word << endl;
  } else if (line_type == "TENSE") {
    outputfile << line_type << ": " << tokenName[saved_token] << endl << endl; // Use array of tokens to output the correct token name.
  } else if(line_type == "ACTION") {
    outputfile << line_type << ": " << saved_E_word << endl;
  } else if(line_type == "TO") {
    outputfile << line_type << ": " << saved_E_word << endl;
  } else if(line_type == "TENSE") { 
    outputfile << line_type << ": " << tokenName[saved_token] << endl << endl;
  } else {
    return;
  }
  
}
// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar
//    rule with semantic routine calls
//    above each non-terminal function

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  ** Gerald, Chris, Brian
int main() {
  //** opens the lexicon.txt file and reads it into Lexicon
  fin.open("lexicon.txt");           // open lexicon.txt file directly
  for (int i = 0; !fin.eof(); i++) { // till end of file read in words
    string read_japanese = "";    
    string read_english = "";

    fin >> read_japanese; // read in japanese word
    fin >> read_english;  // read in english word

    words translation = {read_japanese, read_english}; // make struct to save read in words
    dictionary.push_back(translation); // push the struct to our vector dictionary
  }
  //** closes lexicon.txt
  fin.close();

  //** opens the output file translated.txt

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  cout << "\nSuccessfully parsed <story>." << endl;

  //** closes the input file
  fin.close();
  //** closes traslated.txt
  outputfile.close();

} // end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions


