#include <fstream>
#include <iostream>
#include <string>
#include <iostream>

void show_sentence(char sentence[][14], int len)
{
    int j;
    for (int i = 0; i < len; i++)
    {
        j = 0;
        while (sentence[i][j] != NULL)
        {
            std::cout << sentence[i][j];
            j += 1;
        }
        std::cout << ' ';
    }
    std::cout << '\n';
}

void delete_sentence(char sentence[][14], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            sentence[i][j] = NULL;
        }
    }
}

void show_sentence_from_last_elem(char sentence[][14], int len)
{
    int j;
    for (int i = len - 1; i > -1; i--)
    {
        j = 0;
        while (sentence[i][j] != NULL)
        {
            std::cout << sentence[i][j];
            j += 1;
        }
        std::cout << ' ';
    }
    std::cout << '\n';
}

void check_elem_sign(char* word, int len_word)
{
    int cnt = 0;
    int i = 0;
    while (word[i] != NULL)
    {
        if (!(((((int)(word[i]) > 64) and (int)(word[i]) < 91)) or (((int)(word[i]) > 96) and ((int)(word[i]) < 123)))) cnt += 1;
        else cnt = 0;
        if ((cnt == 2 and word[i + 1] != '.') or (cnt > 3)) word[i] = NULL;
        i += 1;
    }
}

void check_elem_letter(char* word, int len_word)
{
    for (int i = 1; i < len_word; i++)
    {
        if (((int)(word[i]) > 64) and ((int)(word[i]) < 91))
        {
            word[i] = (char)((int)(word[i]) + 32);
        }
    }
}

void check_first_letters(char sentence[][14], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (((int)(sentence[i][0]) > 64) and ((int)(sentence[i][0]) < 91))
        {
            sentence[i][0] = (char)((int)(sentence[i][0]) + 32);
        }
    }

    show_sentence(sentence, len);
}

int fill_string(char sentence[][14])
{
    bool check = 1;
    std::string temp;
    int len = 0;
    int check_cnt = 0;
    while (check and len < 49)
    {
        std::cin >> temp;
        if (temp.size() < 14)
        {
            for (int i = 0; i < temp.size(); i++)
            {
                sentence[len - check_cnt][i] = temp[i];
            }
        }
        else check_cnt += 1;
        if (temp[temp.size() - 1] == '.') check = 0;
        check_elem_letter(sentence[len], temp.size());
        check_elem_sign(sentence[len], temp.size());
        len += 1;
    }
    if (check_cnt)
    {
        std::cout << "\nWas " << check_cnt << " wrong words\n";
    }
    return len;
}

int fill_string_from_file(char sentence[][14])
{
    int len = 0;
    std::ifstream fin("fin.txt");
    if (fin.is_open())
    {
        bool check = 1;
        std::string temp;
        int check_cnt = 0;
        while (check and len < 49)
        {
            fin >> temp;
            if (temp.size() < 14)
            {
                for (int i = 0; i < temp.size(); i++)
                {
                    sentence[len - check_cnt][i] = temp[i];
                }
            }
            else check_cnt += 1;
            if (temp[temp.size() - 1] == '.') check = 0;
            check_elem_letter(sentence[len], temp.size());
            check_elem_sign(sentence[len], temp.size());
            len += 1;
        }
        if (check_cnt)
        {
            std::cout << "\nWas " << check_cnt << " wrong words\n";
        }
        fin.close();
    }
    else 
    {
        std::cout << "\nWas file fin.txt opened?\n";
    }
    return len;
}

void linear_search(char sentence[][14], int len, std::string x)
{
    int check = 0;
    int i = 0;
    int j, save_i;
    while (check < x.size() and i < len)
    {
        j = 0;
        check = 0;
        while (check < x.size() and sentence[i][j] != NULL)
        {
            if (sentence[i][j] == x[check]) check++;
            else check = 0;
            j++;
        }
        i++;
    }
    if (check < x.size()) std::cout << "String you write wasn't in the main string\n";
    else std::cout << "String was found\n";
}

int find_index(char letter, std::string x)
{
    int i = x.size() - 1;
    while ((x[i] != letter) and (i > 1)) i--;
    return i;
}

int find_len(char word[])
{
    int len = 1;
    while (word[len] != NULL) len++;
    return len;
}

bool boyer_mur_word(char word[], int i, std::string x)
{
    int check = 0;
    int save;
    bool check_not_el = 1;
    int len = find_len(word);
    int index;
    while (check < (x.size() - 1) and i < len)
    {
        check = 0;
        save = i;
        index = find_index(word[i], x);
        while ((check < index) and (word[save] == x[index - check]))
        {
            save--;
            check++;
        }
        save = i + 1;
        while ((save < (len - 1)) and (word[save] == x[check + 1]))
        {
            save++;
            check++;
        }
        if (check < (x.size() - 1)) i += x.size();
        else check_not_el = 0;
    }
    return check_not_el;
}

void boyer_mur(char sentence[][14], int len, std::string x)
{
    int i = 0;
    int j = 0;
    bool check = 1;
    while (check and i < len)
    {
        while ((i < len) and (x.size() > find_len(sentence[i]))) i++;
        if (i < len) check = boyer_mur_word(sentence[i], x.size() - 1, x);
        i++;
    }
    if (!check) std::cout << "String was found\n";
    else std::cout << "String you write wasn't in the main string\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Hi!\n";
    std::string x;
    char sentence[50][14];
    int len = 50;
    bool change = 1;
    try
    {
        while (change != 0)
        {
            delete_sentence(sentence, len);
            len = 0;
            std::cout << "\nIf you want to use file, write 0. If you want to write from console, write 1: ";
            std::cin >> change;
            if (!std::cin) throw("ex");
            std::cout << "\nWrite sentence of words. After the last word write dot\n";
            if (change) len = fill_string(sentence);
            else len = fill_string_from_file(sentence);
            if (len)
            {
                std::cout << "\nSentence after correcting:\n";
                show_sentence(sentence, len);
                std::cout << "\nSentence in reverse order:\n";
                show_sentence_from_last_elem(sentence, len);
                std::cout << "\nSentence after making first letters small:\n";
                check_first_letters(sentence, len);
                std::cout << "\nWrite word for search:\n";
                std::cin >> x;
                if (!std::cin) throw("ex");
                if (x.size() < 14)
                {
                    std::cout << "\nLinear search:\n";
                    linear_search(sentence, len, x);
                    std::cout << "\nBoyer–Moore string-search algorithm:\n";
                    boyer_mur(sentence, len, x);
                }
                else std::cout << "String you write wasn't in the main string\n";
            }
            std::cout << "\nIf you want to continue, write 1. If you want to exit, write 0: ";
            std::cin >> change;
            if (!std::cin) throw("ex");
        }
    }
    catch (...)
    {
        std::cout << "\nWrong data!\n";
    }
}