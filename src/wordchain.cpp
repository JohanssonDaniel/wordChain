#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <set>
using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";


void createDict(set<string>& allWords) {
    string filename = "dictionary.txt";
    ifstream input;
    input.open(filename.c_str());
    while(true) {
        string word;
        input >> word;
        if (input.fail()) {
            break;
        }
        allWords.insert(word);
    }
}

void printSuccessMessage(stack<string> printStack, string w1, string w2){
    cout << "Chain from " << w1 << " back to " << w2 << ": " << endl;
    int size = printStack.size();
    for(int i = 0; i < size; i++){
        cout << printStack.top() << " ";
        printStack.pop();
    }
    cout << "\nHave a nice day." << endl;
}

void wordChain(string w1, string w2, set<string> allWords) {
    const int lengthofAlphabet = 26;
    queue<stack<string>> words;     //create an empty queue of stacks

    stack<string> word;             //create/add a stack containing {w1} to the queue
    word.push(w1);
    words.push(word);

    set<string> usedWords;         //Keeps track of used words
    usedWords.insert(w1);

    int word1Length = w1.length();

    string alphabet = "abcdefghijklmnopqrstuwxyz";


    while (!words.empty()) {
        stack<string> topStack = words.front();                                        //dequeue the partial-chain stack from the front of the queue
        words.pop();


        if (topStack.top() == w2) {                                                    //if the word at the top of the stack is the destinaction word
            printSuccessMessage(topStack, w1, w2);
        }
        else {
            for (int i = 0; i < word1Length; i++) {
                string tempWord = topStack.top();
                for (int j = 0; j < lengthofAlphabet; j++) {
                    tempWord[i] = alphabet[j];                                         //Change letter in the word
                    int isInDict = allWords.count(tempWord);                         //returns 1 if in dictionary 0 if not
                    int alreadyUsed = usedWords.count(tempWord);                     //returns 1 if in usedWords 0 if not
                    if (isInDict == 1 && alreadyUsed == 0) {
                        stack<string> temp_stack = topStack;                           //create a copy of the current chain stack
                        temp_stack.push(tempWord);                                     //put the neighbour word at the top of the copy stack
                        words.push(temp_stack);                                         //add the copy to the end of the queue
                        usedWords.insert(tempWord);
                    }
                }
            }
        }

    }
}
int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    string input, first, second;
    getline(cin, input);
    istringstream ss(input);
    ss >> first;
    ss >> second;

    set<string> allWords;
    createDict(allWords);
    wordChain(first, second, allWords);

    return 0;
}
