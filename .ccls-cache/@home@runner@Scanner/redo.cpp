#include<iostream>
#include<fstream>
#include<string>
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
// RE:   ** (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+

bool word (string s)
{

  int state = 0;
  int charpos = 0;
  // replace the following todo the word dfa  **
  while (s[charpos] != '\0') 
    { 
      if (state == 0) { // if state 0  (start of state 1)
        if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E') { //q0 --> q0q1 //mised out on
          state = 3;// goes to state 3
        } else if (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' ||  s[charpos] == 'p' ||  s[charpos] == 'r') { // Q0 -> qy
          state = 1; // goes to state 1
        } else if (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j') { // Q0 -> qsa
          state = 2; // goes to state 2
        } else if (s[charpos] == 't') { //q0 -> qt
          state = 5; // goes to state 5
        } else if (s[charpos] == 's') { //q0 -> qs
          state  = 6; // goes to state 6
        } else if (s[charpos] == 'c') { //q0 -> qc
          state = 7; //goes to state 7
        } else {
          return false; // return false (nothing found)
        } 
        // end of state 1
      } else if (state == 1) { // Starting state 1: qy -> qsa
        if (s[charpos] == 'y') {
          state = 2;
        } else if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E') {
          state = 3;
        } else {
          return false;  // return false (nothing found)
        }
      } else if (state == 2) { // Starting State 2: qsa -> q0q1
        if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E') {
          state = 3;
        } else {
          return false;  // return false (nothing found)
        } 
      } else if (state == 3) {    //q0q1 = state 3
        if (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'p' ||  s[charpos] == 'r') {//bghkmpr to qy {
          state = 1; // go to qy
        } else if (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j') {
          state = 2; // go to state qsa
        } else if (s[charpos] == 't') { // if t
          state = 5;  // go to state qt
        } else if (s[charpos] == 's') { // if s
          state = 6; //state qs
        } else if (s[charpos] == 'c') { //if c
          state = 7; // state qc
        } else if (s[charpos] == 'n') { // if n 
          state = 9; // state q0qy
        } else if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E') { // if V
          state = 3; // go to state q0q1
        } else {
          return false;  // return false (nothing found)
        }
      } else if (state == 4) { // q1 empty
        if (s[charpos] == 'n') {
          state = 0; // go to q0
        } else {
          return false;  // return false (nothing found)
        }
      } else if (state == 5) { // State 5: qt
        if (s[charpos] == 's') { // qt -> qsa
          state = 2; // state 2
        } else if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E') { // if V
          state = 3;
        } else {
          return false;  // return false (nothing found)
        }// end of qt
      } else if (state == 6) { //qs
        if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E') { //V to q0q1
          state = 3;
        } else if (s[charpos] == 'h') { //h to qsa
          state = 2;
          // end qs
        } else {
          return false;  // return false (nothing found)
        }
      } else if (state == 7) { //qc
        if (s[charpos] == 'h') { //h to q0q1
          state = 2;
        } else {
          return false;  // return false (nothing found)
        }
      } else if (state == 9) { //q0qy
        if (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' ||  s[charpos] == 'p' ||  s[charpos] == 'r') {//bghkmpr to qy {
          state = 1; // go to qy
        } else if (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j') { //dwzyj to qsa
          state = 2; // go to qsa
        } else if (s[charpos] == 'n') { // if n 
          state = 1; // go to qy
        } else if (s[charpos] == 'c') { // if c
          state = 7; // go to qc
        } else if (s[charpos] == 's') { // if s
          state = 6; // go to qs
        } else if (s[charpos] == 't') { // if t
          state = 5; // go to qt
        } else if (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E') { // if V
          state = 3; // go to q0q1
        } else {
          return false;  // return false (nothing found)
        } 
        //end of state 9
      } else {
        cout << "I am stuck in state: " << state << endl;
        cout << "I am stuck in char: " << s[charpos] << endl;
        return false; //  return false 
      }
      
      charpos++; // update char pos
    }//end of while
    
  // where did I end up????
  if (state == 0 || state == 3 || state == 9) return(true);  // end in a final state
   else return(false);
}

// PERIOD DFA 
// Done by: ** Gerald Cordero 
bool period (string s)
{  // complete this **
  int state = 0; // inital current state set to 0
  int charpos = 0; // current character position set to 0
  while (s[charpos] != '\0') { // start of while

    if (state == 0 && s[charpos] == '.') { // if state 0 and character is '.'
      state = 1; // go to state 1
    } else {
      return false; // return false
    }

    charpos++;  // incriment charpos to get to next character
  } // end of while

  if (state == 1) { // if state is at 1 after while loop
    return true; // return true
  } else {
    return false; // else false
  }

}

// ------ Three  Tables -------------------------------------

// TABLES Done by: ** Gerald, Chris, Brian

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM}; //update tt

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM" }; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
struct R
{
  string word; // for word
  tokentype token_type; // for tt
};

// array for all rules
R arr[] = {{"masu", VERB}, {"masen", VERBNEG}, {"mashita", VERBPAST}, {"masendeshita", VERBPASTNEG}, {"desu", IS}, {"deshita", WAS}, {"o", OBJECT}, {"wa", SUBJECT}, {"ni", DESTINATION}, {"watashi", PRONOUN}, {"anata", PRONOUN}, {"kare", PRONOUN}, {"kanojo", PRONOUN}, {"sore", PRONOUN}, {"mata", CONNECTOR}, {"soshite", CONNECTOR}, {"shikashi", CONNECTOR}, {"dakara", CONNECTOR}, {"eofm", EOFM}};

int n = 19; //gloabl index of array of reserved words/token_type

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Gerald Chris, Brian
int scanner(tokentype& tt, string& w)
{
 
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   
    fin >> w;
    // cout << "input is " << w << endl;
    if (w == "eofm" || w == "EOFM") { // if eofm return
      return 0; // return 0
    }

  /*  **
  2. Call the token functions (word and period)
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
  */
  bool period_found = false;  //variable for period 
  bool error_found = false;  //variable for error
  if (word(w) == false && period(w) == false) {  // if not a word or a period then error
    cout << "Lexical error: string is not a valid token" << endl;
    tt = ERROR; // else error
    error_found = true;  //error found make variable true
  } else if (period(w) == true) { // if period true
    tt = PERIOD; // token type '.'
    period_found = true;  //period found make variable true
  }

  /*
  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.
  */
  bool reserved_word = false;
  if (word(w) == true) { //if word then find token type
    //cout << w << " IS WORD" << endl;
    for (int i = 0; i < n; i++) { // iterate through array size 
      if (w == arr[i].word) { //if word is a word in array
        tt = arr[i].token_type; // assign tt to the token type
        reserved_word = true; // set to true
      }
    }
  }
  if (reserved_word == false && period_found == false && error_found == false) { //if not a word find last letter and set to WORD1 or WORD2
    if (w[w.length()-1] == 'a' || w[w.length()-1] == 'e'  || w[w.length()-1] == 'i'  || w[w.length()-1] == 'o' || w[w.length()-1] == 'u' || w[w.length()-1] == 'n') {
      tt = WORD1; //set to WRD1
    } else if (w[w.length()-1] == 'I' || w[w.length()-1] == 'E') {
      tt = WORD2; //set to WRD2
    }
  }
  /*
  4. Return the token type & string  (pass by reference)
  */
  return 0;
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis 

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

//global variables
bool token_available = false;
tokentype saved_token;
string saved_lexeme;

// Type of error: **
// Done by: ** 
void syntaxerror1(  ) {
    cout << "SYNTAX ERROR: expected " << tokenName[saved_token] << " but found " << saved_lexeme << endl;
    exit(1);
}
// Type of error: **
// Done by: ** 
void syntaxerror2(  ) {
    cout << "SYNTAX ERROR: unexpected " << saved_lexeme << " found in " << tokenName[saved_token] << endl;
    exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme


// Purpose: **
// Done by: **
tokentype next_token(void) {
    if(!token_available) {
        scanner(saved_token, saved_lexeme);
        cout << "Scanner called using word: " << saved_lexeme << endl;
        token_available = true;

        if (saved_token == ERROR) {
            syntaxerror1();
        }
    }
    return saved_token;
}

// Purpose: **
// Done by: **
bool match(tokentype expected) {
    if(next_token() != expected) {
        syntaxerror2();
        return false;
    } else {
        cout << "Matched: " << tokenName[saved_token] << endl;
        token_available = false;
        return true;
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: ** <noun> word1|pronoun
// Done by: **

void noun() {
    cout << "Processing <noun>" << endl;
    switch(next_token()) {
        case WORD1:
            match(WORD1);
            break;
        case PRONOUN:
            match(PRONOUN);
            break;
        default:
            syntaxerror2();
    }
}

// Grammar: ** <verb> ::= word2
// Done by: **

void verb() {
    cout << "Processing <verb>" << endl;
    match(WORD2);
}

// Grammar: ** <be> is | was
// Done by: **

void be() {
    cout << "Processing <be>" << endl;
    switch(next_token()) {
        case IS:
            match(IS);
            break;
        case WAS:
            match(WAS);
            break;
        default:
            syntaxerror2();
    }
}
// Grammar: **<tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
// Done by: **

void tense() {
    cout << "Processing <tense>" << endl;
    switch(next_token()) {
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
            match(VERBNEG);
            break;
        default:
            syntaxerror2();
    }
}

// Grammar: ** <after object> ::= <verb> <tense> PERIOD|<noun> DESTINIATION <verb> <tense> PERIOD            
// Done by: **

void afterObject() {
    cout << "Processing <afterObject>" << endl;
    switch(next_token()) {
        case VERB:
            verb();
            tense();
            match(PERIOD);
            break;
        case WORD1:
            noun();
            match(DESTINATION);
            verb();
            tense();
            match(PERIOD);
            break;
        case PRONOUN:
            noun();
            match(DESTINATION);
            verb();
            tense();
            match(PERIOD);
            break;
        case WORD2:
            verb();
            tense();
            match(PERIOD);
            break;
        default:
            syntaxerror2();
    }
}

// Grammar: ** afterNoun ::= <be> PERIOD| DESTINATION <verb> <tense> PERIOD| OBJECT <after object>   
// Done by: **

void afterNoun() {
    cout << "Processing <afterNoun>" << endl;
    switch(next_token()) {
        case IS:
            be();
            match(PERIOD);
            break;
        case WAS:
            be();
            match(PERIOD);
            break;
        case DESTINATION:
            match(DESTINATION);
            verb();
            tense();
            match(PERIOD);
            break;
        case OBJECT:
            match(OBJECT);
            afterObject();
            break;
        default:
            syntaxerror2();
    }
}

// Grammar: ** <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: **

void afterSubject() {
    cout << "Processing <afterSubject>" << endl;
    switch(next_token()) {
        case VERB:
            verb();
            tense();
            match(PERIOD);
            break;
        case WORD1:
            noun();
            afterNoun();
            break;
        case PRONOUN:
            noun();
            afterNoun();
            break;
        case WORD2:
            verb();
            tense();
            match(PERIOD);
            break;
        default:
            syntaxerror2();
    }
}


// Grammar: ** <s> ::= [CONNECTOR] <noun> SUBJECT <after noun>
// Done by: **

void s() {
    cout << "Processing <s> " << endl;
    if (next_token() == CONNECTOR) {
        match(CONNECTOR);
    }
    noun();
    match(SUBJECT);
    afterSubject();
}

// Grammar: ** 1 <story> ::= <s> { <s> } stay in the loop as long as a possible start 
// of <s> is the next_token  (note it can be CONNECTOR or WORD1 or PRONOUN)
// Done by: **

void story() {
    cout << "Processing <story>\n" << endl;

    s();
    while (true) {
        switch(next_token()) {
            case CONNECTOR:
            case WORD1:
            case PRONOUN:
                s();
                break;
            default:
                return;
        }
    }
}

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  cout << "\nSuccessfully parsered <story>." << endl;
  //** closes the input file 
  fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
