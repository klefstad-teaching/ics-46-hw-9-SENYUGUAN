#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << "error: " << msg << " " << word1 << " " << word2;
}


bool partCheck(const string & s1, const string & s2)
{
    int diff = 0;
    for(int i = 0; i < s1.size(); ++i)
        if(s1[i] != s2[i] && ++diff > 1) return false;
            
    return diff == 1;
}

bool insertDelete(const string & longStr, const string & shortStr)
{
    int longLen = longStr.size();
    int shortLen = shortStr.size();
    int i = 0, j = 0;
    bool found = false;

    while(i < longLen && j < shortLen)
    {
        if(longStr[i] != shortStr[j])
        {
            if(found) return false;
            found = true;
            ++i;
        }
        else
        {
            ++i; 
            ++j;
        }
    }
    return true;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d)
{
    int length1 = str1.size();
    int length2 = str2.size();
    int count = 0;
    if(abs(length1 - length2) > d) return false;

    if(length1 == length2)
        return partCheck(str1, str2);
    else
    {
        const auto& [longStr, shortStr] = length1 > length2 ? pair{str1, str2} : pair{str2, str1};
        return insertDelete(longStr, shortStr);
    }

}

bool is_adjacent(const string &word1, const string &word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list)
{
    if(begin_word == end_word) return{ };

    queue<vector<string>> ladderQ;
    set<string> visited;
    ladderQ.push({begin_word});
    visited.insert(begin_word);

    while(!ladderQ.empty())
    {
        auto curr = ladderQ.front();
        ladderQ.pop();
    
        string end_word2 = curr.back();

        for(const auto &word : word_list)
        {
            if(!visited.count(word) && is_adjacent(end_word2, word))
            {
                auto newLadder = curr;
                newLadder.push_back(word);
                visited.insert(word);

                if(word == end_word2)
                return newLadder;

                ladderQ.push(newLadder);
            }

        }


       
    }

    return { };
}

void load_words(set<string> &word_list, const string &file_name)
{
    ifstream in(file_name);
    string s;
    if(!in.is_open()) return;

    while(true)
    {
        if(!getline(in, s)) break;

        if(!s.empty()) word_list.insert(s);
    }

    in.close();

}

void print_word_ladder(const vector<string> &ladder)
{
    if(ladder.empty())
    {
        cerr << "empty\n";
        return;
    }
    
    for(auto e : ladder)
        cout << e << "\n";


}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "word.txt");

    auto my_assert = [&](bool result, const char* expr){
        cout << expr << (result ? " passed" : " failed") << endl;
    };
    auto ladder = generate_word_ladder("cat", "dog", word_list);
    my_assert(ladder.size() == 4, "Ladder cat->dog has size 4");
    
}
