#include "ladder.h"

int main(int argc, char* argv[])
{
    set<string> dictionaty;
    load_words(dictionaty, "word.txt");
    string s1, s2;
    cout << "Enter: ";
    cin >> s1;
    cout << "Enter : ";
    cin >> s2;

    auto ladder = generate_word_ladder(s1,s2,dictionaty);

    if(ladder.empty()) error(s1,s2,"empty");
    else print_word_ladder(ladder);

    

    return 0;
}